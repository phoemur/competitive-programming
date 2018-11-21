/*RMQSQ - Range Minimum Query
no tags 

You are given a list of N numbers and Q queries. Each query is specified by two numbers i and j; the answer to each query is the minimum number between the range [i, j] (inclusive).

Note: the query ranges are specified using 0-based indexing.
Input

The first line contains N, the number of integers in our list (N <= 100,000). The next line holds N numbers that are guaranteed to fit inside an integer. Following the list is a number Q (Q <= 10,000). The next Q lines each contain two numbers i and j which specify a query you must answer (0 <= i, j <= N-1).
Output

For each query, output the answer to that query on its own line in the order the queries were made.
Example

Input:
3
1 4 1
2
1 1
1 2

Output:
4
1

*/

#include <algorithm>
#include <iostream>

#define K 25
#define MAXN 100001

int arr[MAXN]; // Input array (not really necessary)
int st[MAXN][K + 1]; // sparse table for RMQ queries
int log2table[MAXN+1]; // stores log array

void preprocess_st(int n)
{
    for (int i = 0; i < n; ++i)
        st[i][0] = arr[i];
    
    for (int j = 1; j <= K; j++)
        for (int i = 0; i + (1 << j) <= n; i++)
            st[i][j] = std::min(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
}

void preprocess_log()
{
    log2table[1] = 0;

    for (int i = 2; i <= MAXN; i++)
        log2table[i] = log2table[i/2] + 1;
}

inline int RMQ(int l, int r)
{
    int j = log2table[r - l + 1];
    return std::min(st[l][j], st[r - (1 << j) + 1][j]);
}

int main()
{
    int n;
    std::cin >> n;
    
    for (int i = 0; i < n; ++i)
        std::cin >> arr[i];
    
    preprocess_st(n);
    preprocess_log();
    
    int queries;
    std::cin >> queries;
    
    while (queries--)
    {
        int l, r;
        std::cin >> l >> r;
        std::cout << RMQ(l, r) << std::endl;
    }    
    
    return 0;
}
