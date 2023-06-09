#include "list.h"

/*************************/
/* Contracts */
/*************************/

bool is_linked(list l)
{
    REQUIRES(l != NULL && l->start != NULL && l->end != NULL);

    node p = l->start->next;
    while (p != l->end)
    {
        if (p == NULL)
        {
            printf("NULL");
            return false;
        }
        if (p->next == NULL)
        {
            printf("NULL1");
            return false;
        }
        if (p->next->prev != p)
            return false;
        p = p->next;
    }
    p = l->end->prev;
    while (p != l->start)
    {
        if (p == NULL)
            return false;
        if (p->prev == NULL)
            return false;
        if (p->prev->next != p)
            return false;
        p = p->prev;
    }
    return true;
}

int count_nodes(list l)
{
    int size = 0;
    node p = l->start->next;
    while (p != l->end)
    {
        size++;
        p = p->next;
    }
    return size;
}

bool is_linked_list(list l)
{
    if (l == NULL)
        return false;
    if (l->start == NULL || l->end == NULL)
        return false;
    if (!is_linked(l))
        return false;
    if (l->size != count_nodes(l))
        return false;
    return true;
}

/*************************/
/* Implementation */
/*************************/
list new_list(elem_free data_free, print_elem print_data, are_equal data_equals)
{

    /* TODO: Finish this function */
    list l = xmalloc(sizeof(struct linked_list));
    l->size = 0;

    l->start = xmalloc(sizeof(struct linked_list));
    l->end = xmalloc(sizeof(struct linked_list));

    l->start->next = l->end;
    l->end->prev = l->start;

    l->data_equals = data_equals;
    l->data_free = data_free;
    l->print_data = print_data;
    // so gcc doesn't yell at us
    // (void)l;
    // (void)data_free;
    // (void)print_data;
    // (void)data_equals;
    ENSURES(is_linked_list(l));
    return l;
}

void append_node(elem e, list l)
{
    REQUIRES(e != NULL);
    REQUIRES(is_linked_list(l));

    /* TODO: Finish this function */
    node n = xmalloc(sizeof(struct list_node));
    n->data = e;

    // (void)n;
    n->prev = l->end->prev;
    n->next = l->end;
    l->end->prev->next = n;
    l->end->prev = n;
    l->size++;
    ENSURES(is_linked_list(l));
}

void prepend_node(elem e, list l)
{
    REQUIRES(e != NULL);
    REQUIRES(is_linked_list(l));

    node n = xmalloc(sizeof(struct list_node));
    n->data = e;
    // add at front
    n->prev = l->start;
    n->next = l->start->next;
    l->start->next->prev = n;
    l->start->next = n;
    l->size++;

    ENSURES(is_linked_list(l));
}

void delete_node(node p, list l)
{
    node prev = p->prev;
    node next = p->next;
    prev->next = next;
    next->prev = prev;

    // free the node/contents
    if (l->data_free)
    { // use client-function to free
        printf("free  e\n");
        (*(l->data_free))(p->data);
    }
    free(p);
    l->size--;
    printf("free node e\n");
    return;
}

elem delete_nodes(elem e, list l)
{
    REQUIRES(e != NULL);
    REQUIRES(is_linked_list(l));

    /* TODO: Finish this function */
    elem found_elem = NULL;
    node p = l->start->next;
    while (p != l->end)
    {
        if ((*(l->data_equals))(e, p->data))
        {
            found_elem = p->data;
            node n = p->next;
            delete_node(p, l);
            p = n;
            continue;
        }
        p = p->next;
    }

    ENSURES(is_linked_list(l));
    return found_elem;
}

void map(list l, map_fn fn)
{
    REQUIRES(is_linked_list(l));

    /* TODO: Finish this function */
    // (void)fn;
    node p = l->start->next;
    while (p != l->end)
    {
        (*fn)(p->data);
        p = p->next;
    }

    ENSURES(is_linked_list(l));
}

int list_size(list l)
{
    REQUIRES(is_linked_list(l));
    return l->size;
}

void print_list(list l)
{
    REQUIRES(is_linked_list(l));

    /* TODO: Finish this function */
    node p = l->start->next;
    while (p != l->end)
    {
        (*(l->print_data))(p->data);
        p = p->next;
    }
    printf("\n");

    ENSURES(is_linked_list(l));
}

void free_list(list l)
{
    REQUIRES(is_linked_list(l));

    /* TODO: Finish this function */

    node p = l->start->next;
    node q;
    while (p != l->end)
    {
        q = p;
        p = q->next;
        if (l->data_free)
        {
            (*(l->data_free))(q->data);
            printf("free data e\n");
        }
        free(q);
        printf("free node\n");
    }
    free(l->start);
    free(l->end);
    free(l);
}
