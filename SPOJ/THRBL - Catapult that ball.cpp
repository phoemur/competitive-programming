/*THRBL - Catapult that ball
#tree #binary-search

Bob has unusual problem. In Byteland we can find a lot of hills and cities. King of Byteland ordered Bob to deliver magic balls from one city to another. Unfortunately, Bob has to deliver many magic balls, so walking with them would take too much time for him. Bob came up with great idea - catapulting them.

Byteland is divided into intervals. Each interval contains city and hill.

Bob can catapult magic ball accurately from city A to city B, if between them there isn't higher hill than A's hill.
Input

Every test case contains N and M (N<=50000) (M<=50000), number of intervals and number of balls.

In next line there's N numbers H(H<=10^9) separated by one space.

In next M lines numbers A and B (1<=A,B<=N), number of city from which we want to catapult the ball and number of city to which we want to catapult the ball.
Output

Write one number - number of magic balls that Bob can catapult successfully.
Example

Input:
7 3
2 3 5 4 2 1 6
3 5
2 5
4 6

Output:
2

Bob can catapult ball number 1 and 3. */

#include <algorithm>
#include <cstdio>

#define K 25
#define MAXN 50005

long st[MAXN][K + 1]; // sparse table for RMQ queries
int log2table[MAXN+1]; // stores log2 results

int main()
{
    int n, m;
    std::scanf("%d %d", &n, &m);
    
    // Precompute sparse table
    for (int i = 0; i < n; ++i)
        std::scanf("%ld", &st[i][0]);
    
    for (int j = 1; j <= K; j++)
        for (int i = 0; i + (1 << j) <= n; i++)
            st[i][j] = std::max(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
    
    // Precompute log2table
    log2table[1] = 0;
    for (int i = 2; i <= MAXN; i++)
        log2table[i] = log2table[i/2] + 1;
        
    // Queries
    long res = 0;
    while (m--)
    {
        int a, b;
        std::scanf("%d %d", &a, &b);
        --a; // Using 0 based idx
        --b;
        --b; // interval [a,b) -> b not included
        
        if (a > b) std::swap(a, b);
        
        int j = log2table[b - a + 1];
        long mx = std::max(st[a][j], st[b - (1 << j) + 1][j]);
        
        if (st[a][0] >= mx)
            ++res;
    }
    
    std::printf("%ld\n", res);
    
    return 0;
}
