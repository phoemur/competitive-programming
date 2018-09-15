/*PT07Z - Longest path in a tree
#dfs

You are given an unweighted, undirected tree. Write a program to output the length of the longest path (from one node to another) in that tree. The length of a path in this case is number of edges we traverse from source to destination.
Input

The first line of the input file contains one integer N --- number of nodes in the tree (0 < N <= 10000). Next N-1 lines contain N-1 edges of that tree --- Each line contains a pair (u, v) means there is an edge between node u and node v (1 <= u, v <= N).
Output

Print the length of the longest path on one line.
Example

Input:
3
1 2
2 3

Output:
2

*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <stack>
#include <vector>

// Solve problem using 2 DFS
long DFS_solve(const std::vector<std::vector<int>>& graph)
{   
    std::stack<int> st;
    std::vector<long> distances (graph.size(), std::numeric_limits<int>::min());
    
    // First DFS find the furthest node
    st.push(0);
    distances[0] = 0;
    
    while (!st.empty())
    {
        auto curr = st.top();
        st.pop();
        
        for (int node: graph[curr])
        {
            if (distances[node] == std::numeric_limits<int>::min()) // Not visited
            {
                st.push(node);
                distances[node] = 1 + distances[curr];
            }
        }
    }
    
    // Find leaf
    auto it = std::max_element(std::begin(distances), std::end(distances));
    int leaf = std::distance(std::begin(distances), it);
    
    // Clean up
    std::fill(std::begin(distances), std::end(distances), std::numeric_limits<int>::min());
    
    // Second DFS start from leaf and find result
    st.push(leaf);
    distances[leaf] = 0;
    
    while (!st.empty())
    {
        auto curr = st.top();
        st.pop();
        
        for (int node: graph[curr])
        {
            if (distances[node] == std::numeric_limits<int>::min()) // Not visited
            {
                st.push(node);
                distances[node] = 1 + distances[curr];
            }
        }
    }
    
    return *std::max_element(std::begin(distances), std::end(distances));
}

int main()
{
    int nodes;
    std::cin >> nodes;
    
    // Adjacency List
    std::vector<std::vector<int>> graph (nodes);
    
    for (int i = 1; i < nodes; ++i)
    {
        int source, dest;
        std::cin >> source >> dest;
        
        graph[source - 1].push_back(dest - 1);
        graph[dest - 1].push_back(source - 1);
    }
    
    std::cout << DFS_solve(graph) << std::endl;
    
    return 0;
}
