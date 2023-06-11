#include <stdio.h>

#include "csapp.h"
#include "sbuf.h"
#include "cache.h"

/* You won't lose style points for including this long line in your code */
static char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";
static char *connection = "Connection: close\r\n";
static char *proxy_connection = "Proxy-Connection: close\r\n";

#define NTHREADS 32
#define SBUFSIZE 64

sbuf_t sbuf;
queue q;

void *proxy(void *vargp);
void clienterror(int fd, char *cause, char *errnum,
                 char *shortmsg, char *longmsg);
void sigpipe_handler(int sig);

/* $begin Part I: Implementing a sequential web proxy */
int main(int argc, char **argv)
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    /* Check command line args */
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    Signal(SIGPIPE, sigpipe_handler);

    listenfd = Open_listenfd(argv[1]);
    q = init_queue();

    sbuf_init(&sbuf, SBUFSIZE);
    pthread_t tid;
    for (size_t i = 0; i < NTHREADS; i++)
    {
        Pthread_create(&tid, NULL, proxy, NULL);
    }

    while (1)
    {
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        sbuf_insert(&sbuf, connfd);
    }
}
/* $end Part I: Implementing a sequential web proxy */

/*
 * proxy - 代理浏览器发送请求，并把响应回传给浏览器
 */
/* $begin proxy */
void *proxy(void *vargp)
{
    Pthread_detach(Pthread_self());
    int clientfd = sbuf_remove(&sbuf); /* add */

    /* 解析浏览器GET请求 start */
    rio_t rio_client;
    Rio_readinitb(&rio_client, clientfd);

    char buf_client[MAXLINE];
    Rio_readlineb(&rio_client, buf_client, MAXLINE);

    char method[MAXLINE], serverUrl[MAXLINE], version[MAXLINE];
    sscanf(buf_client, "%s %s %s", method, serverUrl, version);

    /* 查询缓存 start */
    if (cache_find(q, serverUrl))
    {
        line node = q->start->next;
        Rio_writen(clientfd, node->response, node->size);
        return (void *)0;
    }
    /* 查询缓存 end */

    /* 只处理GET请求 start */
    if (strcasecmp(method, "GET"))
    {
        clienterror(clientfd, method, "501", "Not Implemented",
                    "Tiny does not implement this method");
        return (void *)0;
    }
    /* 只处理GET请求 end */

    /* 提取服务器uri start */
    char hostname[MAXLINE], port[MAXLINE], uri[MAXLINE];
    char *ptr = index(serverUrl, '/');
    strcpy(hostname, ptr + 2);
    ptr = index(hostname, ':');
    if (ptr)
    {
        strcpy(port, ptr + 1);
        *ptr = '\0';
        ptr = index(port, '/');
        strcpy(uri, ptr);
        *ptr = '\0';
    }
    else
    {
        strcpy(port, "80");
        ptr = index(hostname, '/');
        strcpy(uri, ptr);
        *ptr = '\0';
    }
    /* 提取服务器uri end */

    /* 解析浏览器GET请求 end */

    /* 建立服务器连接 start */
    int serverfd = Open_clientfd(hostname, port);
    /* 建立服务器连接 end */

    /* 构造代理请求头,向服务器发送 start */
    char requesthd[MAXLINE];
    sprintf(requesthd, "GET %s HTTP/1.0\r\n", uri);
    Rio_writen(serverfd, requesthd, strlen(requesthd));
    Rio_writen(serverfd, user_agent_hdr, strlen(user_agent_hdr));
    Rio_writen(serverfd, connection, strlen(connection));
    Rio_writen(serverfd, proxy_connection, strlen(proxy_connection));

    Rio_readlineb(&rio_client, buf_client, MAXLINE);
    char *separator = "\r\n";
    while (strcmp(buf_client, separator))
    {
        if (strstr(buf_client, "User-Agent") || strstr(buf_client, "Connection") || strstr(buf_client, "Proxy-Connection"))
        {
            ; /* 这些请求头已经被替换 */
        }
        else
        {
            Rio_writen(serverfd, buf_client, strlen(buf_client));
        }
        Rio_readlineb(&rio_client, buf_client, MAXLINE);
    }
    Rio_writen(serverfd, separator, strlen(separator));

    /* 构造代理请求头,向服务器发送 end */

    /* 接收服务器响应,回传给浏览器 start */
    rio_t rio_server;
    Rio_readinitb(&rio_server, serverfd);
    char response[MAX_OBJECT_SIZE];
    unsigned int size = 0;
    char buf_server[MAXLINE];
    size_t n;
    while ((n = Rio_readlineb(&rio_server, buf_server, MAXLINE)) != 0)
    {
        // printf("n %d", n);

        size += n;
        sprintf(response, "%s%s", response, buf_server);
        Rio_writen(clientfd, buf_server, n);
    }
    // printf("size %d", size);
    /* 接收服务器响应,回传给浏览器 end */

    /* 缓存服务器响应 start */
    new_node(q, serverUrl, response, size);
    /* 缓存服务器响应 end */

    Close(serverfd);
    Close(clientfd); /* add */
    return (void *)0;
} /* $end proxy */

/*
 * clienterror - returns an error message to the client
 */
/* $begin clienterror */
void clienterror(int fd, char *cause, char *errnum,
                 char *shortmsg, char *longmsg)
{
    char buf[MAXLINE];

    /* Print the HTTP response headers */
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n\r\n");
    Rio_writen(fd, buf, strlen(buf));

    /* Print the HTTP response body */
    sprintf(buf, "<html><title>Tiny Error</title>");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "<body bgcolor="
                 "ffffff"
                 ">\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "%s: %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "<p>%s: %s\r\n", longmsg, cause);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "<hr><em>The Tiny Web server</em>\r\n");
    Rio_writen(fd, buf, strlen(buf));
}
/* $end clienterror */

/* 处理SIGPIPE信号 */
void sigpipe_handler(int sig)
{
    return;
}