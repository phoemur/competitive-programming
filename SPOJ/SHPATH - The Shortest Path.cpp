/*SHPATH - The Shortest Path
#shortest-path #dijkstra-s-algorithm

You are given a list of cities. Each direct connection between two cities has its transportation cost (an integer bigger than 0). The goal is to find the paths of minimum cost between pairs of cities. Assume that the cost of each path (which is the sum of costs of all direct connections belongning to this path) is at most 200000. The name of a city is a string containing characters a,...,z and is at most 10 characters long.
Input

 

s [the number of tests <= 10]
n [the number of cities <= 10000]
NAME [city name]
p [the number of neighbours of city NAME]
nr cost [nr - index of a city connected to NAME (the index of the first city is 1)]
           [cost - the transportation cost]
r [the number of paths to find <= 100]
NAME1 NAME2 [NAME1 - source, NAME2 - destination]
[empty line separating the tests]

 
Output

 

cost [the minimum transportation cost from city NAME1 to city NAME2 (one per line)]

 
Example

 

Input:
1
4
gdansk
2
2 1
3 3
bydgoszcz
3
1 1
3 1
4 4
torun
3
1 3
2 1
4 1
warszawa
2
2 4
3 1
2
gdansk warszawa
bydgoszcz warszawa

Output:
3
2

 

Warning: large Input/Output data, be careful with certain languages
*/

#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

std::int64_t dijkstra(const std::vector<std::vector<std::pair<int,int>>>& graph, 
                      int source, 
                      int dest)
{
    // Distances array
    std::vector<std::int64_t> distances (graph.size(), std::numeric_limits<int>::max());
    
    // Priority Queue (Min-Heap)
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
    std::ios_base::sync_with_stdio(false);
    
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int citynum;
        std::cin >> citynum;
        
        // Hash table name to index
        std::unordered_map<std::string, int> cities;
        
        // Adjacency List
        std::vector<std::vector<std::pair<int,int>>> graph (citynum); // pair <dest_index, cost>
        
        // Fill
        for (int i = 0; i < citynum; ++i)
        {
            std::string name;
            std::cin >> name;
            cities[name] = i;
            
            int edges;
            std::cin >> edges;
            graph[i].reserve(edges);
            
            while (edges--)
            {
                int dest, cost;
                std::cin >> dest >> cost;
                graph[i].emplace_back(dest-1, cost);
            }
        }
        
        // Queries
        int queries;
        std::cin >> queries;
        
        while (queries--)
        {
            std::string source, dest;
            std::cin >> source >> dest;
            std::cout << dijkstra(graph, cities[source], cities[dest]) << std::endl;
        }
    }
    
    return 0;
}
