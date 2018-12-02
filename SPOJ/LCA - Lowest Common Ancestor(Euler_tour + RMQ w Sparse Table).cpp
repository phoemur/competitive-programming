#include <algorithm>
#include <iostream>
#include <vector>

#define K 25
#define MAXN 100001

std::vector<int> euler_tour;
std::vector<int> level_tour;

int indexx[MAXN]; // Store index of first occurence on the euler tour
int st[MAXN][K + 1]; // sparse table for RMQ queries
int log2table[MAXN+1]; // stores log array

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

inline void preprocess_log()
{
    log2table[1] = 0;

    for (int i = 2; i <= MAXN; i++)
        log2table[i] = log2table[i/2] + 1;
}

void preprocess_st(int n)
{
    for (int i = 0; i < n; ++i)
        st[i][0] = euler_tour[i];
    
    for (int j = 1; j <= K; j++)
        for (int i = 0; i + (1 << j) <= n; i++)
            if (level_tour[indexx[st[i][j-1]]] < level_tour[indexx[st[i + (1 << (j - 1))][j - 1]]])
                st[i][j] = st[i][j-1];
            else
                st[i][j] = st[i + (1 << (j - 1))][j - 1];
}

inline int LCA(int u, int v)
{
    int l_index = indexx[u];
    int r_index = indexx[v];
            
    if (l_index > r_index)
        std::swap(l_index, r_index);
    
    int j = log2table[r_index - l_index + 1];
    
    if (level_tour[indexx[st[l_index][j]]] < level_tour[indexx[st[r_index - (1 << j) + 1][j]]])
        return st[l_index][j];
    else
        return st[r_index - (1 << j) + 1][j];
}

int main()
{
    preprocess_log();
    
    int tests;
    std::cin >> tests;
    
    for (int cas = 1; cas <= tests; ++cas)
    {
        // Clean up
        euler_tour.clear();
        level_tour.clear();
        std::fill(indexx, indexx+MAXN, -1);
        
        // Input
        int nodes;
        std::cin >> nodes;
        
        std::vector<std::vector<int>> adj (nodes); // Adjacency List
        
        for (int i = 0; i < nodes; ++i)
        {
            int n;
            std::cin >> n;
            
            while (n--)
            {
                int dest;
                std::cin >> dest;

                adj[i].push_back(dest-1);
            }
        }
        
        // DFS and fill datastructures
        DFS(0, 1, adj);
        preprocess_st(euler_tour.size());
        
        /* 
        std::cout << "Euler Tour:\n";
        for (auto& num: euler_tour) std::cout << num << " ";
        std::cout << std::endl;
         
        std::cout << "Level Tour:\n";
        for (auto& num: level_tour) std::cout << num << " ";
        std::cout << std::endl;
         
        std::cout << "Indexes of first ocurrence:\n";
        for (int i = 0; i < nodes; ++i) std::cout << indexx[i] << " ";
        std::cout << std::endl;
         */
        
        int queries;
        std::cin >> queries;
        
        std::cout << "Case " << cas << ":\n";
        while (queries--)
        {
            int l, r;
            std::cin >> l >> r;
                       
            std::cout << LCA(l-1, r-1) + 1 << std::endl;
        }
    }
    
    return 0;
}
