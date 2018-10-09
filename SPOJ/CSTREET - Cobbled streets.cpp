/*CSTREET - Cobbled streets
#mst

The municipal chronicals of an unbelievable lordly major town in a land far, far away tell the following story:
Once upon a time the new crowned king Günther decided to visit all towns in his kingdom. The people of the unbelievable lordly major town expected that king Günther would like to see some of the most famous buildings in their town. For the lordly citizens it seemed neccessary that all streets in the town that the king would have to use had to be cobbled with stone. Unfortunately the unbelievable lordly major town had not much money at that time as they used most of their savings to erect the highest cathedral the world had ever seen.
Roumours were afloat that the real reason for their thriftiness was not that the town treasury was empty but that many people believed that king Günther came to the throne by deceiving his father king Erwin and that in his youth he made a pact with the devil. But anyway, the citizens of the unbelievable lordly major town decided to pave only as much streets as were absolutely necessary to reach every major building.
Can you help the citizens of the unbelievable lordly major town to find out which streets should be paved?
It might be usefull to know that all major buildings are either at the end of a street or at an intersection. In addition to that you can assume that all buildings are connected by the given streets.
Input

t [number of testcases (1 <= t <= 100)]
p [price to pave one furlong of street (positive integer)]
n [number of main buildings in the town (1 <= n <= 1000)]
m [number of streets in the town (1 <= m <= 300000)]
a b c [street from building a to building b with length c (lengths are given in furlong and the buildings are numbered from 1 to n)]
Output

For each testcase output the price of the cheapest possibility to reach all main buildings in the city on paved streets. You can assume that the result will be smaller than 2^32.
Example

Input:
1
2
5
7
1 2 1
2 3 2
2 4 6
5 2 1
5 1 3
4 5 2
3 4 3

Output:
12

*/

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

class UnionFind {
    std::size_t sz;
    std::vector<std::size_t> rank;
    std::vector<std::size_t> parent;

public:
    explicit UnionFind(std::size_t s)
        : sz{s}, rank(s, 0), parent(s, 0)
    {
        for (std::size_t i=0; i<sz; ++i) {
            parent[i] = i;
        }
    }
    
    UnionFind() : UnionFind(0) {} //default constructor
    
    template<typename T>
    UnionFind(const std::vector<T>& a)
        : sz{a.size()}, rank(a.size(), 0), parent(a.size(), 0)
    {
        for (std::size_t i=0; i<sz; ++i) {
            parent[i] = i;
        }
    }
    
    // A utility function to find set of an element i
    // (uses path compression technique)
    std::size_t find(std::size_t i)
    {
        // find root and make root as parent of i 
        // (path compression)
        if (parent[i] != i) {
            parent[i] = find(parent[i]);
        }
        
        return parent[i];
    }
    
    // A function that does union of two sets of x and y
    // (uses union by rank)
    void merge(std::size_t x, std::size_t y)
    {
        auto xroot = find(x);
        auto yroot = find(y);
        
        // Attach smaller rank tree under root of high 
        // rank tree (Union by Rank)
        if (rank[xroot] < rank[yroot]) {
            parent[xroot] = yroot;
        }
        else if (rank[xroot] > rank[yroot]) {
            parent[yroot] = xroot;
        }
        
        // If ranks are same, then make one as root and 
        // increment its rank by one
        else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }
    
    bool is_same_set(std::size_t x, std::size_t y)
    {
        return find(x) == find(y);
    }
    
    std::size_t sets_count() const noexcept
    {
        std::set<std::size_t> st (begin(parent), end(parent));
        return st.size();
    }
    
}; // class UnionFind

struct Edge {
    int source;
    int dest;
    int weight;
    
    Edge(int a, int b, int c)
        : source{a}, dest{b}, weight{c} {}
        
    Edge() : Edge(0, 0, 0) {}
};

std::vector<Edge> kruskal(std::vector<Edge>& edgeList, const unsigned vertices)
{
    // Sort edges in non decreasing order by weight
    std::sort(std::begin(edgeList), std::end(edgeList), [](auto& a, auto& b){
        return a.weight < b.weight;
    });
    
    UnionFind u (edgeList);
    
    std::vector<Edge> result {};
    
    // Number of edges to be taken is equal to V-1
    int i = 0; //index
    while (result.size() <  vertices - 1) {
        Edge next_edge = edgeList[i++];
        
        int x = u.find(next_edge.source);
        int y = u.find(next_edge.dest);
        
        // If including this edge does't cause cycle, include it in result
        if (x != y)
        {
            result.push_back(next_edge);
            u.merge(x, y);
        }
        // Else discard the next_edge   
    }
    return result;
}

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int price_unit, vertices, edges;
        std::cin >> price_unit >> vertices >> edges;
        
        std::vector<Edge> edgeList;
        edgeList.reserve(edges * 2);
        
        for (int i = 0; i < edges; ++i)
        {
            int v1, v2, w;
            std::cin >> v1 >> v2 >> w;
            edgeList.emplace_back(v1, v2, w);
            edgeList.emplace_back(v2, v1, w); // add both ways
        }
        
        auto MST = kruskal(edgeList, vertices);
        
        int res = std::accumulate(std::begin(MST), 
                                  std::end(MST), 
                                  0, 
                                  [price_unit](int a, Edge& b) 
                                  {
                                      return a + (b.weight * price_unit);
                                  });
        
        std::cout <<  res << std::endl;
    }
    
    return 0;
}
