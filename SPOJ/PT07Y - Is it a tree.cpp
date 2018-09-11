/*PT07Y - Is it a tree
#dfs

You are given an unweighted, undirected graph. Write a program to check if it's a tree topology.
Input

The first line of the input file contains two integers N and M --- number of nodes and number of edges in the graph (0 < N <= 10000, 0 <= M <= 20000). Next M lines contain M edges of that graph --- Each line contains a pair (u, v) means there is an edge between node u and node v (1 <= u,v <= N).
Output

Print YES if the given graph is a tree, otherwise print NO.
Example

Input:
3 2
1 2
2 3

Output:
YES
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

// Solve using iterative DFS
inline bool solve(const std::vector<std::vector<int>>& graph)
{
    const int sz = graph.size();
    std::vector<bool> visited (sz, false);
    std::stack<int> st;

    st.push(0);
    visited[0] = true;

    while (!st.empty())
    {
        int curr = st.top();
        st.pop();

        for (int node: graph[curr])
        {
            if (visited[node]) return false;
            else
            {
                st.push(node);
                visited[node] = true;
            }
        }
    }

    // Return if all nodes were visited
    return std::all_of(std::begin(visited), std::end(visited), [](bool a){return a == true;});   
}

int main()
{    
    std::ios_base::sync_with_stdio(false);

    int nodes, edges;
    std::cin >> nodes >> edges;

    if (nodes != edges + 1)
    {
        std::cout << "NO\n";
        return 0;
    }

    std::vector<std::vector<int>> graph (nodes);

    while (edges--)
    {
        int source, dest;
        std::cin >> source >> dest;
        graph[source-1].push_back(dest-1); 
    }

    if (solve(graph))
        std::cout << "YES\n";
    else
        std::cout << "NO\n";

    return 0;
}
