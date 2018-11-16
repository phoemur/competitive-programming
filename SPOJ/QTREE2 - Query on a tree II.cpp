/*QTREE2 - Query on a tree II
#graph-theory #tree

You are given a tree (an undirected acyclic connected graph) with N nodes, and edges numbered 1, 2, 3...N-1. Each edge has an integer value assigned to it, representing its length.

We will ask you to perfrom some instructions of the following form:

    DIST a b : ask for the distance between node a and node b
    or
    KTH a b k : ask for the k-th node on the path from node a to node b 

Example:
N = 6
1 2 1 // edge connects node 1 and node 2 has cost 1
2 4 1
2 5 2
1 3 1
3 6 2

Path from node 4 to node 6 is 4 -> 2 -> 1 -> 3 -> 6
DIST 4 6 : answer is 5 (1 + 1 + 1 + 2 = 5)
KTH 4 6 4 : answer is 3 (the 4-th node on the path from node 4 to node 6 is 3)
Input

The first line of input contains an integer t, the number of test cases (t <= 25). t test cases follow.

For each test case:

    In the first line there is an integer N (N <= 10000)
    In the next N-1 lines, the i-th line describes the i-th edge: a line with three integers a b c denotes an edge between a, b of cost c (c <= 100000)
    The next lines contain instructions "DIST a b" or "KTH a b k"
    The end of each test case is signified by the string "DONE". 

There is one blank line between successive tests.
Output

For each "DIST" or "KTH" operation, write one integer representing its result.

Print one blank line after each test.
Example

Input:
1

6
1 2 1
2 4 1
2 5 2
1 3 1
3 6 2
DIST 4 6
KTH 4 6 4
DONE

Output:
5
3

*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

#define N 10010
#define LN 14

std::vector<std::pair<long,long>> adj[N]; // pair [dest, cost]
int parent[N];
int height[N];
long distance[N]; // Distance from source
int dp[LN][N];


void cleanup(int n)
{
    for (int i = 0; i <= n; ++i) 
        adj[i].clear();
    
    std::fill(parent, parent + n + 1, -1);
    std::fill(height, height + n + 1,  0);
    std::fill(distance, distance + n + 1, 0);
    
    for (int i = 0; i < LN; ++i)
        std::fill(dp[i], dp[i] + N, -1);
}

void DFS(int node, int par, int curr_height, long curr_dist)
{
    // Update
    parent[node] = par;
    height[node] = curr_height;
    distance[node] = curr_dist;
    
    // Recurr
    for (const auto& p: adj[node])
        if (p.first != parent[node])
            DFS(p.first, node, curr_height + 1, curr_dist + p.second);
}

void preprocess_lca(int n)
{
    for(int i = 0; i <= n; i++)
        dp[0][i] = parent[i];

    for(int j = 1; j < LN; j++)
        for(int i = 0; i <= n; i++)
            if(dp[j-1][i] != -1)
                dp[j][i] = dp[j-1][dp[j-1][i]];
}

int lca(int u, int v)
{
    if (height[u] > height[v])
        std::swap(u,v);

    int diff = height[v] - height[u];

    for(int j = 0; j < LN; j++) 
        if((diff >> j) & 1) 
            v = dp[j][v];

    if(u == v) 
        return u;
    else
    {
        for(int j= LN-1; j >= 0; j--)
        {
            if(dp[j][u] != dp[j][v])
            {
                u = dp[j][u];
                v = dp[j][v];
            }
        }
    }
    
    return dp[0][v];
}

inline long dist_query(int u, int v)
{
    int l = lca(u, v);

    return distance[u] + distance[v] - (2*distance[l]);
}

inline int kth_query_util(int p, int t)
{
    int log;
    for(log=1;(1<<log)<=height[p];log++);
    log--;
    
    for (int i = log; i >= 0; --i)
        if (height[p] - (1<<i) >= t)
            p = dp[i][p];
        
    return p;
}

int kth_query(int p, int q, int k)
{
    int l = lca(p, q);

    if (height[p] - height[l] + 1 >= k) 
        // Result on the first leg
        return kth_query_util(p, height[p]-k+1);
    else
        // Result on the second leg
        return kth_query_util(q, 2*height[l]-height[p]+k-1);
}

int main()
{
    int tests;
    std::scanf("%d", &tests);
    
    while (tests--)
    {
        int n;
        std::scanf("%d", &n);
        
        cleanup(n);
        
        for (int i = 0; i < n-1; ++i)
        {
            long node, dest, cost;
            std::scanf("%ld %ld %ld", &node, &dest, &cost);
            
            adj[node].emplace_back(dest, cost);
            adj[dest].emplace_back(node, cost);
        }
        
        DFS(1, -1, 0, 0);
        preprocess_lca(n);
        
        char str[30];
        int a, b, c;
        
        while (true)
        {        
            std::scanf("%s", str);
            
            if (str[0] == 'K') // KTH query type
            {
                std::scanf("%d %d %d", &a, &b, &c);
                std::printf("%d\n", kth_query(a, b, c));
                
            }
            else if (str[1] == 'I') // DIST query type
            {
                std::scanf("%d %d", &a, &b);
                std::printf("%ld\n", dist_query(a, b));
            }
            else // DONE
            {
                std::printf("\n");
                break;
            }
        }
    }
    
    return 0;
}
