32 line,每行容纳 8 个int 

32x32 矩阵 8x8 分块 -> 256 miss

```
>./test-trans -M 32 -N 32

Function 0 (2 total)
Step 1: Validating and generating memory traces
Step 2: Evaluating performance (s=5, E=1, b=5)
func 0 (Transpose submission): hits:1709, misses:344, evictions:312
```

>*理论与实际不符 -> 冲突不命中*

低效率版本的参考中 给了提示：
```
tmp = A[i][j];
B[j][i] = tmp;

又提示了不超过 12 个本地变量
```
阅读test-trans.c 理解测试方式: 
>./csim-ref -s 5 -E 1 -b 5 -t trace.f1  
查看运行细节 分析 优化



参考如下：
<https://zhuanlan.zhihu.com/p/456858668>



```
> ./driver.py
Part A: Testing cache simulator
Running ./test-csim
                        Your simulator     Reference simulator
Points (s,E,b)    Hits  Misses  Evicts    Hits  Misses  Evicts
     3 (1,1,1)       9       8       6       9       8       6  traces/yi2.trace
     3 (4,2,4)       4       5       2       4       5       2  traces/yi.trace
     3 (2,1,4)       2       3       1       2       3       1  traces/dave.trace
     3 (2,1,3)     167      71      67     167      71      67  traces/trans.trace
     3 (2,2,3)     201      37      29     201      37      29  traces/trans.trace
     3 (2,4,3)     212      26      10     212      26      10  traces/trans.trace
     3 (5,1,5)     231       7       0     231       7       0  traces/trans.trace
     6 (5,1,5)  265189   21775   21743  265189   21775   21743  traces/long.trace
    27


Part B: Testing transpose function
Running ./test-trans -M 32 -N 32
Running ./test-trans -M 64 -N 64
Running ./test-trans -M 61 -N 67

Cache Lab summary:
                        Points   Max pts      Misses
Csim correctness          27.0        27
Trans perf 32x32           6.8         8         344
Trans perf 64x64           1.2         8        1892
Trans perf 61x67          10.0        10        1951
          Total points    45.0        53

```

