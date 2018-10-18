/*DQUERY - D-query
#sorting #tree

English 	Vietnamese

Given a sequence of n numbers a1, a2, ..., an and a number of d-queries. A d-query is a pair (i, j) (1 ≤ i ≤ j ≤ n). For each d-query (i, j), you have to return the number of distinct elements in the subsequence ai, ai+1, ..., aj.
Input

    Line 1: n (1 ≤ n ≤ 30000).
    Line 2: n numbers a1, a2, ..., an (1 ≤ ai ≤ 106).
    Line 3: q (1 ≤ q ≤ 200000), the number of d-queries.
    In the next q lines, each line contains 2 numbers i, j representing a d-query (1 ≤ i ≤ j ≤ n).

Output

    For each d-query (i, j), print the number of distinct elements in the subsequence ai, ai+1, ..., aj in a single line.

Example

Input
5
1 1 2 1 3
3
1 5
2 4
3 5

Output
3
2
3 

*/

#include <algorithm>
#include <cstdio>

#define N 300304
#define A 1000001
#define BLOCK 548 // sqrt(N)

struct Query {
    int L;
    int R;
    int index;
};

int arr[N];
int cnt[A];
int ans[N];
Query q[N];
int answer = 0;

inline void add(const int position)
{
    cnt[arr[position]]++;
    
    if (cnt[arr[position]] == 1)
        ++answer;
}

inline void remove(const int position)
{
    cnt[arr[position]]--;
    
    if (cnt[arr[position]] == 0)
        --answer;
}

inline void solve(const int queries)
{
    int currentL = 0, currentR = 0;
    
    for (int i = 0; i < queries; ++i)
    {
        while (currentL < q[i].L)
        {
            remove(currentL);
            ++currentL;
        }
        
        while (currentL > q[i].L)
        {
            add(currentL - 1);
            --currentL;
        }
        
        while (currentR <= q[i].R)
        {
            add(currentR);
            ++currentR;
        }
        
        while (currentR > q[i].R + 1)
        {
            remove(currentR - 1);
            --currentR;
        }
        
        ans[q[i].index] = answer;
    }
    
    for (int i = 0; i < queries; ++i)
        std::printf("%d\n", ans[i]);
}

bool compare(const Query& lhs, const Query& rhs)
{
    if(lhs.L/BLOCK != rhs.L/BLOCK) // different blocks, so sort by block.
        return lhs.L/BLOCK < rhs.L/BLOCK;
    else // same block, so sort by R value
        return lhs.R < rhs.R;
}

int main()
{
    // Input
    int n;
    std::scanf("%d", &n);
    
    for (int i = 0; i < n; ++i)
        std::scanf("%d", &arr[i]);
    
    int m;
    std::scanf("%d", &m);
    
    for (int i = 0; i < m; ++i)
    {
        std::scanf("%d%d", &q[i].L, &q[i].R);
        --q[i].L; --q[i].R;
        q[i].index = i;
    }
    
    // Sort queries
    std::sort(q, q + m, compare);
    
    // Solve
    solve(m);
    
    return 0;
}
