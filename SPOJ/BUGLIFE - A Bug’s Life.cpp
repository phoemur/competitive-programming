/*BUGLIFE - A Bug’s Life
#graph-theory #graph #dfs

Professor Hopper is researching the sexual behavior of a rare species of bugs. He assumes that they feature two different genders and that they only interact with bugs of the opposite gender. In his experiment, individual bugs and their interactions were easy to identify, because numbers were printed on their backs.

Given a list of bug interactions, decide whether the experiment supports his assumption of two genders with no homosexual bugs or if it contains some bug interactions that falsify it.
Input

The first line of the input contains the number of scenarios. Each scenario starts with one line giving the number of bugs (at least one, and up to 2000) and the number of interactions (up to 1000000) separated by a single space. In the following lines, each interaction is given in the form of two distinct bug numbers separated by a single space. Bugs are numbered consecutively starting from one.
Output

The output for every scenario is a line containing “Scenario #i:”, where i is the number of the scenario starting at 1, followed by one line saying either “No suspicious bugs found!” if the experiment is consistent with his assumption about the bugs’ sexual behavior, or “Suspicious bugs found!” if Professor Hopper’s assumption is definitely wrong.
Example

Input:
2
3 3
1 2
2 3
1 3
4 2
1 2
3 4

Output:
Scenario #1:
Suspicious bugs found!
Scenario #2:
No suspicious bugs found!

*/

#include <cstdio>
#include <vector>
#include <queue>

bool is_bipartite_util(const std::vector<std::vector<int>>& graph, 
                       int src, 
                       std::vector<int>& colors)
{
    colors[src] = 1;
    
    std::queue<int> q;
    q.push(src);
    
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        
        for (auto& v: graph[curr])
        {
            if (v == curr) return false; // Self-loop
            
            if (colors[v] == -1)
            {
                colors[v] = 1 - colors[curr];
                q.push(v);
            }
            else if (colors[v] == colors[curr])
                return false;
        }
    }
    
    return true;
}

bool is_bipartite(const std::vector<std::vector<int>>& graph)
{
    std::vector<int> colors  (graph.size(), -1);
    
    for (int i = 0; i < graph.size(); ++i)
        if (colors[i] == -1)
            if (!is_bipartite_util(graph, i, colors))
                return false;
            
    return true;
}

int main()
{
    int n;
    std::scanf("%d", &n);
    
    for (int scen = 1; scen <= n; ++scen)
    {
        int bugs, iter;
        std::scanf("%d %d", &bugs, &iter);
        
        std::vector<std::vector<int>> adjList (bugs);
        
        while (iter--)
        {
            int source, dest;
            std::scanf("%d %d", &source, &dest);
            
            adjList[source-1].push_back(dest-1);
            adjList[dest-1].push_back(source-1);
        }
        
        std::printf("Scenario #%d:\n", scen);
        
        if (is_bipartite(adjList))
            std::printf("No suspicious bugs found!\n");
        else
            std::printf("Suspicious bugs found!\n");
    }
    
    return 0;
}
