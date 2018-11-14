/*QTREE - Query on a tree
#tree

You are given a tree (an acyclic undirected connected graph) with N nodes, and edges numbered 1, 2, 3...N-1.

We will ask you to perfrom some instructions of the following form:

    CHANGE i ti : change the cost of the i-th edge to ti
    or
    QUERY a b : ask for the maximum edge cost on the path from node a to node b 

Input

The first line of input contains an integer t, the number of test cases (t <= 20). t test cases follow.

For each test case:

    In the first line there is an integer N (N <= 10000),
    In the next N-1 lines, the i-th line describes the i-th edge: a line with three integers a b c denotes an edge between a, b of cost c (c <= 1000000),
    The next lines contain instructions "CHANGE i ti" or "QUERY a b",
    The end of each test case is signified by the string "DONE". 

There is one blank line between successive tests.
Output

For each "QUERY" operation, write one integer representing its result.
Example

Input:
1

3
1 2 1
2 3 2
QUERY 1 2
CHANGE 1 3
QUERY 1 2
DONE

Output:
1
3

*/

#include <algorithm>
#include <cstdio>
#include <climits>
#include <vector>
#include <utility>

#define N 10100
#define LN 14

int heavy[N]; // Stores the next node for the same heavy chain
int chainHead[N]; // Stores the head of its heavy chain, for any node
int height[N]; // height of the node
int par[N];    // parent of the node
int baseArr[N]; // Array used to build the segment tree
int posInBase[N]; // Position of the node on the segtree
int segtree[6*N]; // Segment tree
int p[20][N]; // Dynamic Programming LCA array

int pos = 0;

std::vector<std::pair<int,int>> edge; // Maps edge numbers to node numbers -> pair [source, dest]
std::vector<int> adj[N];  // Adjacency List
std::vector<int> cost[N]; // Cost of the edges, with same coord. from adjlist 

template<typename T>
constexpr T maximum(T t1, T t2)
{
    return t1 > t2 ? t1: t2;
}

int lca(int u, int v)
{
    if (height[u] > height[v])
        std::swap(u,v);

    int diff = height[v] - height[u];

    for(int j = 0; j < LN; j++) 
        if((diff >> j) & 1) 
            v = p[j][v];

    if(u == v) 
        return u;
    else
    {
        for(int j= LN-1; j >= 0; j--)
        {
            if(p[j][u] != p[j][v])
            {
                u = p[j][u];
                v = p[j][v];
            }
        }
    }
    
    return p[0][v];
}

// DFS traversal of the tree. Fills parent, height and finds the heavy child
int dfs(int node)
{
    int size = 1;
    int max_c_size = 0;
    
    for (int nx_node: adj[node])
    {
        if (nx_node != par[node])
        {
            par[nx_node] = node;
            height[nx_node] = height[node] + 1;
            
            int c_size = dfs(nx_node);
            
            size += c_size;
            
            if (c_size > max_c_size)
            {
                max_c_size = c_size;
                heavy[node] = nx_node;
            }
        }
    }
    
    return size;
}

// Heavy-light decomposition of the tree
void hl_decompose(int node, int h)
{
    chainHead[node] = h;
    posInBase[node] = pos;
    
    int cst = 0;
    if (par[node] != -1)
        for (int i = 0; i < adj[par[node]].size(); ++i)
            if (adj[par[node]][i] == node)
            {
                cst = cost[par[node]][i];
                break;
            }
            
    baseArr[pos++] = cst;
    
    // Recurrence
    if (heavy[node] != -1)
        hl_decompose(heavy[node], h);
    
    for (int c : adj[node])
        if (c != par[node] && c != heavy[node])
            hl_decompose(c, c);
}

// Build Segtree
void build_segtree(int node, int lo, int hi)
{
    if (lo > hi)
        return;
    else if (lo == hi)
        segtree[node] = baseArr[lo];
    else
    {
        int mid = (lo + hi) / 2;
        
        build_segtree(node*2, lo, mid);
        build_segtree(node*2+1, mid+1, hi);
        
        segtree[node] = maximum(segtree[node*2], segtree[node*2+1]);
    }
}

// Range query
int query_segtree(int node, int lo, int hi, int i, int j)
{
    if (lo > hi || lo > j || hi < i)
        return 0;
    else if (lo >= i && hi <= j)
        return segtree[node];
    else
    {
        int mid = (lo + hi) / 2;
        int q1 = query_segtree(node*2, lo, mid, i, j);
        int q2 = query_segtree(node*2+1, mid+1, hi, i, j);
        
        return maximum(q1, q2);
    }
}

// Point update
void update_segtree(int node, int lo, int hi, int idx, int val)
{
    if (lo > hi || lo > idx || hi < idx)
        return;
    else if (lo == hi)
        segtree[node] = val;
    else
    {
        int mid = (lo + hi) / 2;
        
        if (idx <= mid)
            update_segtree(node*2,      lo, mid, idx, val);
        else
            update_segtree(node*2+1, mid+1,  hi, idx, val);
        
        segtree[node] = maximum(segtree[node*2], segtree[node*2+1]);
    }
}

// Query Tree using HLD
int query(int u, int v)
{
    int l = lca(u,v);
    int ans = INT_MIN;

    while(chainHead[l] != chainHead[u])
    {
        ans = maximum(ans, query_segtree(1, 0, pos-1, posInBase[chainHead[u]],posInBase[u]));
        u = chainHead[u];
        u = par[u];
    }

    ans = maximum(ans, query_segtree(1, 0, pos-1, posInBase[l]+1,posInBase[u]));
    u = v;
                
    while(chainHead[l] != chainHead[u])
    {
        ans = maximum(ans, query_segtree(1, 0, pos-1, posInBase[chainHead[u]],posInBase[u]));
        u = chainHead[u];
        u = par[u];
    }
    
    ans = maximum(ans, query_segtree(1, 0, pos-1, posInBase[l]+1,posInBase[u]));
    
    return ans;
}

void update(int a, int val)
{
    int u = edge[a].first;
    int v = edge[a].second;
    
    if(par[u] == v) 
        std::swap(u,v);

    update_segtree(1, 0, pos-1, posInBase[v], val);
}

// Reset datastructures for a new testcase
void cleanup(int n)
{
    for(int i=0;i<n+2;i++)
    {
        adj[i].clear();
        cost[i].clear();
    }
    
    edge.clear();
    
    std::fill(chainHead, chainHead+n+2, -1);
    std::fill(par, par+n, -1);
    std::fill(height, height+n, 0);
    std::fill(heavy, heavy+n, -1);
    std::fill(baseArr, baseArr+n, 0);
    std::fill(posInBase, posInBase+n, -1);
    std::fill(segtree, segtree+(n*6), 0);
       
    for (int i = 0; i < 20; ++i)
        std::fill(p[i], p[i]+n, -1);
    
    pos = 0;
}

int main()
{
    int n,t;
    int xx,yy,zz;
    std::scanf("%d",&t);
    
    while(t--)
    {
        std::scanf("%d",&n);
    
        cleanup(n);
        
        for(int i=0;i<n-1;i++)
        {
            std::scanf("%d %d %d", &xx, &yy, &zz);
            xx--;yy--;
            adj[xx].push_back(yy);
            adj[yy].push_back(xx);
            cost[xx].push_back(zz);
            cost[yy].push_back(zz);
            edge.push_back(std::make_pair(xx,yy));
        }

        dfs(0);
        hl_decompose(0,0);
        build_segtree(1, 0, pos-1);
        
        // Following is for LCA queries
        for(int i = 0; i < n; i++)
            p[0][i] = par[i];

        for(int j = 1; j < LN; j++)
            for(int i = 0; i < n; i++)
                if(p[j-1][i] != -1)
                    p[j][i] = p[j-1][p[j-1][i]];

        char s[30];
        int a, b;
        while(std::scanf("%s",s) != EOF && s[0] != 'D')
        {
            std::scanf("%d %d",&a,&b);

            if(s[0] == 'C')
            {
                update(a-1, b);
            }
            else if(s[0] == 'Q')
            {
                std::printf("%d\n", query(a-1, b-1));
            }
        }
    }

    return 0;
} 
