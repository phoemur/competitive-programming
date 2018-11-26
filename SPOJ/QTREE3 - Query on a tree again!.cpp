/*QTREE3 - Query on a tree again!
#tree

English 	Vietnamese

You are given a tree (an acyclic undirected connected graph) with N nodes. The tree nodes are numbered from 1 to N. In the start, the color of any node in the tree is white.

We will ask you to perfrom some instructions of the following form:

    0 i : change the color of the i-th node (from white to black, or from black to white);
    or
    1 v : ask for the id of the first black node on the path from node 1 to node v. if it doesn't exist, you may return -1 as its result. 

Input

In the first line there are two integers N and Q.

In the next N-1 lines describe the edges in the tree: a line with two integers a b denotes an edge between a and b.

The next Q lines contain instructions "0 i" or "1 v" (1 ≤ i, v ≤ N).
Output

For each "1 v" operation, write one integer representing its result.
Example

Input:
9 8
1 2
1 3
2 4
2 9
5 9
7 9
8 9
6 8
1 3
0 8
1 6
1 7
0 2
1 9
0 2
1 9 

Output:
-1
8
-1
2
-1

Constraints & Limits

There are 12 real input files.

For 1/3 of the test cases, N=5000, Q=400000.

For 1/3 of the test cases, N=10000, Q=300000.

For 1/3 of the test cases, N=100000, Q=100000.
*/

#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>

#define N 100001

int      heavy[N]; // Stores the next node for the same heavy chain
int  chainHead[N]; // Stores the head of its heavy chain, for any node
int     height[N]; // height of the node
int        par[N]; // parent of the node
int target_set[N]; // map node to a set representing the chain

// Custom comparator for the sets below
struct compare {
    bool operator()(int lhs, int rhs)
    {   // In the same chain, nodes with less height comes first
        return height[lhs] < height[rhs];
    }
};
    
std::set<int, compare> sets[N];    // each set represents a chain in the decomposition
std::vector<std::vector<int>> adj; // Adjacency List

int cur = 0;


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
    if (target_set[chainHead[node]] == -1)
        target_set[chainHead[node]] = cur++;
    
    // Recurrence
    if (heavy[node] != -1)
        hl_decompose(heavy[node], h);
    
    for (int c : adj[node])
        if (c != par[node] && c != heavy[node])
            hl_decompose(c, c);
}

// Init data structures
inline void init(int n)
{
    adj.resize(n);
    std::fill(chainHead, chainHead+n+1, -1);
    std::fill(par, par+n, -1);
    std::fill(height, height+n, 0);
    std::fill(heavy, heavy+n, -1);
    std::fill(target_set, target_set+n, -1);
}

inline void update(int node)
{
    // Find the set for this chain
    auto& s = sets[target_set[chainHead[node]]];
            
    // Insert or delete node if needed;
    if (s.find(node) == s.end())
        s.insert(node);
    else
        s.erase(node);
}

inline int query(int node)
{
    int ans = -1;
        
    while (chainHead[0] != chainHead[node])
    {
        auto& s = sets[target_set[chainHead[node]]];
                
        // Find the closer black node if it exists
        if (!s.empty())
        {
            auto it = std::begin(s);
            if (height[*it] <= height[node])
                ans = *it;
        }
        
        // Switch chains
        node = chainHead[node];
        node = par[node];
    }
    
    // Again, now nodes are in the same chain
    auto& s = sets[target_set[chainHead[node]]];
    if (!s.empty())
    {
        auto it = std::begin(s);
        if (height[*it] <= height[node])
            ans = *it;
    }
            
    if (ans != -1) // Correct for 1 indexing
        ++ans;
    
    return ans;
}

int main()
{
    int n, q;
    std::scanf("%d %d", &n, &q);
    
    init(n);
    
    // Input
    for (int i = 1; i < n; ++i)
    {
        int l, r;
        std::scanf("%d %d", &l, &r);
        l--; r--;
        
        adj[l].push_back(r);
        adj[r].push_back(l);
    }
    
    // Decompose the tree
    dfs(0);
    hl_decompose(0,0);

    // Process queries
    while (q--)
    {
        int a, b;
        std::scanf("%d %d", &a, &b);
        b--;
        
        if (a == 0)
            update(b);
        else
            std::printf("%d\n", query(b));
    }
    
    return 0;
}
