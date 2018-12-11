/*SCAVHUNT - Scavenger Hunt
no tags 

Bill has been the greatest boy scout in America and has become quite a superstar because he always organized the most wonderful scavenger hunts (you know, where the kids have to find a certain route following certain hints). Bill has retired now, but a nationwide election quickly found a successor for him, a guy called George. He does a poor job, though, and wants to learn from Bill’s routes. Unfortunately Bill has left only a few notes for his successor. Bill never wrote his routes completely, he only left lots of little sheets on which he had written two consecutive steps of the routes. He then mixed these sheets and memorized his routes similarly to how some people learn for exams: practicing again and again, always reading the first step and trying to remember the following. This made much sense, since one step always required something from the previous step. George however would like to have a route written down as one long sequence of all the steps in the correct order. Please help him make the nation happy again by reconstructing the routes.
Input

The first line contains the number of scenarios. Each scenario describes one route and its first line tells you how many steps (3 ≤ S ≤ 333) the route has. The next S − 1 lines each contain one consecutive pair of the steps on the route separated by a single space. The name of each step is always a single string of letters.
Output

The output for every scenario begins with a line containing “Scenario #i:”, where i is the number of the scenario starting at 1. Then print S lines containing the steps of the route in correct order. Terminate the output for the scenario with a blank line.
Example

Input:
2
4
SwimmingPool OldTree
BirdsNest Garage
Garage SwimmingPool
3
Toilet Hospital
VideoGame Toilet


Output:
Scenario #1:
BirdsNest
Garage
SwimmingPool
OldTree

Scenario #2:
VideoGame
Toilet
Hospital

*/

#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<int> kahn_top_sort(const std::vector<std::vector<int>>& adj, 
                               std::vector<int>& indegree)
{
    std::queue<int> q;
    
    for (int i = 0; i < indegree.size(); ++i)
        if (indegree[i] == 0)
            q.push(i);
        
    std::vector<int> top_order;
    
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        top_order.push_back(u);
 
        for (auto& elem : adj[u])
        {
            --indegree[elem];
            
            if (indegree[elem] == 0)
                q.push(elem);
        }
    }
    
    return top_order;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int tests;
    std::cin >> tests;
    
    for (int cas = 1; cas <= tests; ++cas)
    {
        int s;
        std::cin >> s;
        
        std::unordered_map<std::string, int> table; // Maps name to node number
        std::vector<std::string> table2 (s);        // Maps node number to name
        
        std::vector<std::vector<int>> adj (s); // Adjacency List
        std::vector<int> indegree (s, 0);      // Indegree of each node
        int cur = 0;
        
        // Input Loop
        for (int i = 1; i < s; ++i)
        {
            std::string a, b;
            std::cin >> a >> b;
            
            int source, dest;
            
            if (table.find(a) != table.end())
                source = table[a];
            else
            {
                table[a] = cur;
                table2[cur] = a;
                
                source = cur;
                ++cur;
            }
            
            if (table.find(b) != table.end())
                dest = table[b];
            else
            {
                table[b] = cur;
                table2[cur] = b;
                
                dest = cur;
                ++cur;
            }
            
            adj[source].push_back(dest);
            indegree[dest]++;
        }
        
        auto res = kahn_top_sort(adj, indegree);
        
        std::cout << "Scenario #" << cas << ":\n";
        for (const auto& elem: res)
            std::cout << table2[elem] << "\n";
        
        std::cout << std::endl;
    }
    
    return 0;
}
