/*QTREE5 - Query on a tree V
#tree

You are given a tree (an acyclic undirected connected graph) with N nodes. The tree nodes are numbered from 1 to N. We define dist(a, b) as the number of edges on the path from node a to node b.

Each node has a color, white or black. All the nodes are black initially.

We will ask you to perfrom some instructions of the following form:

    0 i : change the color of i-th node(from black to white, or from white to black).
    1 v : ask for the minimum dist(u, v), node u must be white(u can be equal to v). Obviously, as long as node v is white, the result will always be 0. 

Input

    In the first line there is an integer N (N <= 100000)
    In the next N-1 lines, the i-th line describes the i-th edge: a line with two integers a b denotes an edge between a and b.
    In the next line, there is an integer Q denotes the number of instructions (Q <= 100000)
    In the next Q lines, each line contains an instruction "0 i" or "1 v" 

Output

For each "1 v" operation, print one integer representing its result. If there is no white node in the tree, you should write "-1".
Example

Input:
10
1 2
1 3
2 4
1 5
1 6
4 7
7 8
5 9
1 10
10
0 6
0 6
0 6
1 3
0 1
0 1
1 3
1 10
1 4
1 6

Output:
2
2
2
3
0

*/

#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>

#define MAXN 100001
#define MAXLOGN 20

std::vector<int> adj[MAXN];           // Tree Adjacency List
std::vector<int> centroid_tree[MAXN]; // Centroid Tree Adjacency List
std::multiset<int> ans[MAXN];         // Used to map distances from centroid[i] to a white node

int    subsizes[MAXN]; // For calculating subsizes during the decomposition
bool    removed[MAXN]; // Marks removed nodes during the decomposition
int cent_parent[MAXN]; // parents on the decomposed tree
int       level[MAXN]; // level of node on the original tree
int dp[MAXLOGN][MAXN]; // Used to calculate LCA on the original tree
bool   is_white[MAXN]; // Used to check the color of a node

inline void init(int n)
{
    std::fill(removed, removed + n, false);
    std::fill(is_white, is_white + n, false);
}

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
    ans[centroid].insert(MAXN*10); // Distance to white node is INF at the beginning
        
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

inline void preprocess_lca(int n)
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

inline void update(int u) 
{
    int a = u;

    // Update all ancestors in decomposed tree.
    while (a != -1)
    {
        int d = dist(u, a);
        
        if (is_white[u]) // Remove this distance
        {
            auto it = ans[a].find(d);
            
            if (it != ans[a].end())
                ans[a].erase(it);
        }
        else // Insert this distance
        {
            ans[a].insert(d);
        }
        
        a = cent_parent[a];
    }
    
    is_white[u] = !is_white[u];
}

inline int query(int u) 
{
    int a = u;
    int closest = MAXN*10;

    // Query all ancestors in decomposed tree.
    while (a != -1)
    {
        closest = std::min(closest, dist(u, a) + *ans[a].begin());
        a = cent_parent[a];
    }

    return closest;
}

int main()
{
    int n;
    std::scanf("%d", &n);
    
    init(n);
    
    for (int i = 1; i < n; ++i)
    {
        int a, b;
        std::scanf("%d %d", &a, &b);
        --a; --b;
        
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    int root = cent_decompose(0, -1);
    DFS_levels(root, -1, 0);
    preprocess_lca(n);
    
    int queries;
    std::scanf("%d", &queries);
    
    while (queries--)
    {
        int a, b;
        std::scanf("%d %d", &a, &b);
        --b;
        
        if (a == 1)
        {
            int res = query(b);
            
            if (res >= MAXN*10)
                res = -1;
            
            std::printf("%d\n", res);
        }
        else // a == 0
        {
            update(b);
        }
    }
    
    return 0;
}
