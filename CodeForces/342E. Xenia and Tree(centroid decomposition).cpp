/*E. Xenia and Tree
https://codeforces.com/contest/342/problem/E

time limit per test
5 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Xenia the programmer has a tree consisting of n nodes. We will consider the tree nodes indexed from 1 to n. We will also consider the first node to be initially painted red, and the other nodes — to be painted blue.

The distance between two tree nodes v and u is the number of edges in the shortest path between v and u.

Xenia needs to learn how to quickly execute queries of two types:

    paint a specified blue node in red;
    calculate which red node is the closest to the given one and print the shortest distance to the closest red node. 

Your task is to write a program which will execute the described queries.
Input

The first line contains two integers n and m (2 ≤ n ≤ 105, 1 ≤ m ≤ 105) — the number of nodes in the tree and the number of queries. Next n - 1 lines contain the tree edges, the i-th line contains a pair of integers ai, bi (1 ≤ ai, bi ≤ n, ai ≠ bi) — an edge of the tree.

Next m lines contain queries. Each query is specified as a pair of integers ti, vi (1 ≤ ti ≤ 2, 1 ≤ vi ≤ n). If ti = 1, then as a reply to the query we need to paint a blue node vi in red. If ti = 2, then we should reply to the query by printing the shortest distance from some red node to node vi.

It is guaranteed that the given graph is a tree and that all queries are correct.
Output

For each second type query print the reply in a single line.
Examples
Input
Copy

5 4
1 2
2 3
2 4
4 5
2 1
2 5
1 2
2 5

Output
Copy

0
3
2*/

#include <bits/stdc++.h>

#define MAXN 100001
#define MAXLOGN 20

std::vector<std::vector<int>> adj;           // Tree Adjacency List
std::vector<std::vector<int>> centroid_tree; // Centroid Tree Adjacency List

int subsizes[MAXN];    // For calculating subsizes during the decomposition
bool removed[MAXN];    // Marks removed nodes during the decomposition
int cent_parent[MAXN]; // parents on the decomposed tree
int level[MAXN];       // level of node on the original tree
int dp[MAXLOGN][MAXN]; // Used to calculate LCA on the original tree
int ans[MAXN];         // Used to map distance from centroid[i] to a red node

/* This function computes the sizes of subtrees starting from node */
int DFS_sizes(int node, int par = -1)
{
    subsizes[node] = 1;
    
    for (auto& elem: adj[node])
        if (!removed[elem] && elem != par)
            subsizes[node] += DFS_sizes(elem, node);
        
    return subsizes[node];
}

/*After sizes of subtrees are calculated, we can find the centroid */
int get_centroid(int node, int total_sz, int par = -1)
{
    for (auto& elem : adj[node])
        if (!removed[elem] && elem != par)
            if (subsizes[elem] > total_sz / 2)
                return get_centroid(elem, total_sz, node);
            
    return node;
}

/* Performs Centroid decomposition of a tree */
int cent_decompose(int node, int par = -1)
{
    int total_sz = DFS_sizes(node, -1);
    
    int centroid = get_centroid(node, total_sz, -1);
    removed[centroid] = true;
    cent_parent[centroid] = par;
        
    // Populate centroid tree
    for (auto& elem : adj[centroid])
        if (!removed[elem])
            centroid_tree[centroid].push_back(cent_decompose(elem, centroid));
        
    return centroid;

}

void DFS_levels(int node, int par, int lev)
{
    level[node] = lev;
    dp[0][node] = par;
    
    
    for (auto& child : adj[node])
        if (child != par)
            DFS_levels(child, node, lev + 1);
}

void preprocess_lca(int n)
{
    for(int j = 1; j < MAXLOGN; j++)
        for(int i = 0; i < n; i++)
            if(dp[j-1][i] != -1)
                dp[j][i] = dp[j-1][dp[j-1][i]];
}

/* LCA on the original tree */
int lca(int u, int v)
{
    if (level[u] > level[v])
        std::swap(u,v);

    int diff = level[v] - level[u];

    for(int j = 0; j < MAXLOGN; j++) 
        if((diff >> j) & 1) 
            v = dp[j][v];

    if(u == v) 
        return u;
    else
    {
        for(int j= MAXLOGN-1; j >= 0; j--)
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

inline int dist(int u, int v)
{
    if (u == v)
        return 0;
    
    int l = lca(u, v);

    return level[u] + level[v] - (2*level[l]);
}

inline void cleanup(int n)
{
    adj.resize(n);
    centroid_tree.resize(n);
    
    std::fill(removed, removed + n, false);
    std::fill(ans, ans + n, MAXN*2);
    
    for (int i = 0; i < MAXLOGN; ++i)
        std::fill(dp[i], dp[i] + MAXN, -1);
}

void update(int u) 
{
    int a = u;

    // Update all ancestors in decomposed tree.
    while (a != -1)
    {
        ans[a] = std::min(ans[a], dist(u, a));
        a = cent_parent[a];
    }
}

int query(int u) 
{
    int a = u;
    int closest = std::numeric_limits<int>::max();

    // Query all ancestors in decomposed tree.
    while (a != -1)
    {
        closest = std::min(closest, dist(u, a) + ans[a]);
        a = cent_parent[a];
    }

    return closest;
}


int main()
{
    int n, m;
    std::cin >> n >> m;
    
    cleanup(n);
    
    // Input
    for (int i = 1; i < n; ++i)
    {
        int l, r;
        std::cin >> l >> r;
        l--; r--;
        
        adj[l].push_back(r);
        adj[r].push_back(l);
    }
    
    int root = cent_decompose(0, -1);
    DFS_levels(root, -1, 0);
    preprocess_lca(n);
    
    update(0); // First node is already painted
    
    while (m--)
    {
        int a, b;
        std::cin >> a >> b;
        --b;
        
        if (a == 1)
        {
            update(b);
        }
        else
        {
            std::cout << query(b) << std::endl;
        }
    }
    
    return 0;
}
