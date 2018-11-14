/*LCA - Lowest Common Ancestor
no tags 

A tree is an undirected graph in which any two vertices are connected by exactly one simple path. In other words, any connected graph without cycles is a tree. - Wikipedia 

The lowest common ancestor (LCA) is a concept in graph theory and computer science. Let T be a rooted tree with N nodes. The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself). - Wikipedia

Your task in this problem is to find the LCA of any two given nodes v and w in a given tree T.

For example the LCA of nodes 9 and 12 in this tree is the node number 3.
Input

The first line of input will be the number of test cases. Each test case will start with a number N the number of nodes in the tree, 1 <= N <= 1,000. Nodes are numbered from 1 to N. The next N lines each one will start with a number M the number of child nodes of the Nth node, 0 <= M <= 999 followed by M numbers the child nodes of the Nth node. The next line will be a number Q the number of queries you have to answer for the given tree T, 1 <= Q <= 1000. The next Q lines each one will have two number v and w in which you have to find the LCA of v and w in T, 1 <= v, w <= 1,000.

Input will guarantee that there is only one root and no cycles.
Output

For each test case print Q + 1 lines, The first line will have “Case C:” without quotes where C is the case number starting with 1. The next Q lines should be the LCA of the given v and w respectively.
Example

Input:
1
7
3 2 3 4
0
3 5 6 7
0
0
0
0
2
5 7
2 7

Output:
Case 1:
3
1

*/

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

#define N 1010

int segtree[6*N];
int indexx[N]; // Store index of first occurence on the euler tour

std::vector<int> euler_tour;
std::vector<int> level_tour;


void DFS(int node, int curr_level, const std::vector<std::vector<int>>& adj)
{
    // Updates
    euler_tour.push_back(node); // preorder insert
    level_tour.push_back(curr_level);// preorder insert
    
    if (indexx[node] == -1)
        indexx[node] = euler_tour.size() - 1; // Index of first ocurrence on euler_tour
        
    
    for (int c : adj[node])
    {
        DFS(c, curr_level + 1, adj); // Recurrence
        euler_tour.push_back(node); // postorder insert
        level_tour.push_back(curr_level); // postorder insert
    }
}

void build_segtree(int node, int lo, int hi)
{
    if (lo > hi)
        return;
    else if (lo == hi)
        segtree[node] = lo; // Store indexes
    else
    {
        int mid = (lo + hi) / 2;
        
        build_segtree(node*2,      lo, mid);
        build_segtree(node*2+1, mid+1,  hi);
        
        if (level_tour[segtree[node*2+1]] > level_tour[segtree[node*2]])
            segtree[node] = segtree[node*2];
        else
            segtree[node] = segtree[node*2+1];
    }
}

int query_segtree(int node, int lo, int hi, int i, int j)
{
    if (lo > hi || lo > j || hi < i)
        return -1;
    else if (lo >= i && hi <= j)
        return segtree[node];
    else
    {
        int mid = (lo + hi) / 2;
        
        int q1 = query_segtree(node*2, lo, mid, i, j);
        int q2 = query_segtree(node*2+1, mid+1, hi, i, j);
        
        if (q1 == -1)
            return q2;
        else if (q2 == -1)
            return q1;
        else if (level_tour[q2] > level_tour[q1])
            return q1;
        else
            return q2;
    }
}

inline int LCA(int u, int v)
{
    int l_index = indexx[u];
    int r_index = indexx[v];
            
    if (l_index > r_index)
        std::swap(l_index, r_index);
            
    // Query the index from the lowest level between l and r
    int res = query_segtree(1, 0, level_tour.size()-1, l_index, r_index);
            
    return euler_tour[res];
}

int main()
{
    int tests;
    std::cin >> tests;
    
    for (int cas = 1; cas <= tests; ++cas)
    {
        // Clean up
        std::memset(segtree, 0, sizeof(int) * N * 3);
        euler_tour.clear();
        level_tour.clear();
        std::fill(indexx, indexx+N, -1);
        
        // Input
        int nodes;
        std::cin >> nodes;
        
        std::vector<std::vector<int>> adj (nodes+1); // Adjacency List
        
        for (int i = 1; i <= nodes; ++i)
        {
            int n;
            std::cin >> n;
            
            while (n--)
            {
                int dest;
                std::cin >> dest;

                adj[i].push_back(dest);
            }
        }
        
        // DFS and fill datastructures
        DFS(1, 1, adj);
        int sz = euler_tour.size();
        build_segtree(1, 0, sz-1);
        
        /* 
        std::cout << "Euler Tour:\n";
        for (auto& num: euler_tour) std::cout << num << " ";
        std::cout << std::endl;
         
        std::cout << "Level Tour:\n";
        for (auto& num: level_tour) std::cout << num << " ";
        std::cout << std::endl;
         
        std::cout << "Indexes of first ocurrence:\n";
        for (int i = 0; i <= nodes; ++i) std::cout << indexx[i] << " ";
        std::cout << std::endl;
         */
        
        int queries;
        std::cin >> queries;
        
        std::cout << "Case " << cas << ":\n";
        while (queries--)
        {
            int l, r;
            std::cin >> l >> r;
                       
            std::cout << LCA(l, r) << std::endl;
        }
    }
    
    return 0;
}
