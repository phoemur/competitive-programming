/*HIGHWAYS - Highways
#shortest-path #graph #mst

A number of cities are connected by a network of highways. Each highway is bidirectional and connects two cities, with a given travel time. What is the shortest time to get from a given city to another given city?
Input

The first line of input contains the number of test cases.

Each test case starts with a line containing the number of cities n (2 ≤ n ≤ 100000), the number of highways m (1 ≤ m ≤ 100000), the starting city and the ending city. Cities are numbered from 1 to n.

Then m lines follow, each describing one highway. The description consists of the two distinct city numbers and the time in minutes to travel along the highway. The time will be between 1 and 1000.
Output

For each test case output a single line containing the minimum time it takes to get from the start to the destination. If no connection exists, output NONE.
Example

Input:
2
4 2 1 4
1 2 5
3 4 5
4 4 1 4
1 2 5
2 3 5
3 4 5
4 2 6

Output:
NONE
11

*/

#include <iostream>
#include <limits>
#include <queue>
#include <vector>
#include <utility>

int dijkstra(const std::vector<std::vector<std::pair<int,int>>>& graph, 
             const int source, 
             const int dest)
{
    // Distances array
    std::vector<int> distances (graph.size(), std::numeric_limits<int>::max());
    
    // Priority Queue
    auto comp = [&distances](int a, int b){return distances[a] >= distances[b];};
    std::priority_queue<int, std::vector<int>, decltype(comp)> pq (comp);
    
    // Setting distance to source to zero
    distances[source] = 0;
    pq.push(source);
    
    // Main loop
    while (!pq.empty()) {
        auto vertex = pq.top(); // Greedily process the nearest vertex
        pq.pop();
        
        for (auto& edge: graph[vertex])
        {
            // Check if relaxation is possible
            if (distances[vertex] < std::numeric_limits<int>::max())
            {
                if (distances[vertex] + edge.second < distances[edge.first])
                {
                    // We have discovered a new shortest route
                    distances[edge.first] = distances[vertex] + edge.second;
                    pq.push(edge.first);
                }
            }
        }
    }
    
    return distances[dest];
}

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {    
        int vertices, edges, start, finish;
        std::cin >> vertices >> edges >> start >> finish;
        
        std::vector<std::vector<std::pair<int,int>>> adjacencyList (vertices); // Pair (dest, weight)
        
        while (edges--)
        {
            int source, dest, weight;
            std::cin >> source >> dest >> weight;
            
            // Undirected graph
            adjacencyList[source-1].emplace_back(dest-1, weight);
            adjacencyList[dest-1].emplace_back(source-1, weight);
        }
        
        int res = dijkstra(adjacencyList, start-1, finish-1);
        
        if (res < std::numeric_limits<int>::max())
            std::cout << res << std::endl;
        else
            std::cout << "NONE" << std::endl;
    }
    
    return 0;
}
