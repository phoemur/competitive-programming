/*BLINNET - Bytelandian Blingors Network
#kruskal-s-algorithm #mst

We have discovered the fastest communication medium Bytelandian scientists announced, and they called it blingors. The blingors are incomparably better than other media known before. Many companies in Byteland started to build blingors networks, so the information society in the kingdom of Bytes is fact! The priority is to build the core of the blingors network, joinig main cities in the country. Assume there is some number of cities that will be connected at the beginning. The cost of building blingors connection between two cities depends on many elements, but it has been successfully estimated. Your task is to design the blingors network connections between some cities in this way that between any pair of cities is a communication route. The cost of this network should be as small as possible.

Remarks

    The name of the city is a string of at most 10 letters from a,...,z.
    The cost of the connection between two cities is a positive integer.
    The sum of all connections is not greater than 232-1.
    The number of cities is not greater than 10 000. 

Input



s [number of test cases <= 10]
n [number of cities <= 10 000]
NAME [city name]
p [number of neigbouring cities to the city NAME]
neigh cost 
     [neigh - the unique number of  city from the main list
      cost - the cost of building the blingors connection from NAME to neigh]
[empty line between test cases]

Output

[separate lines] cost [the minimum cost of building the blingors network]
Example

Input:
2

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

3
ixowo
2
2 1
3 3
iyekowo
2
1 1
3 7
zetowo
2
1 3 
2 7


Output:
3
4

Warning: large Input/Output data, be careful with certain languages
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
    std::ios_base::sync_with_stdio(false);
    
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int vertices;
        std::cin >> vertices;
        
        std::vector<Edge> edgeList;
        
        for (int city = 0; city < vertices; ++city)
        {
            std::string name;
            int num;
            
            std::cin >> name >> num;
            
            while (num--)
            {
                int dest, cost;
                std::cin >> dest >> cost;
                edgeList.emplace_back(city, dest-1, cost);
                edgeList.emplace_back(dest-1, city, cost);
            }
        }
        
        auto MST = kruskal(edgeList, vertices);
        
        int res = std::accumulate(std::begin(MST), 
                                  std::end(MST), 
                                  0, 
                                  [](int a, Edge& b) 
                                  {
                                      return a + b.weight;
                                  });
        
        std::cout <<  res << std::endl;
    }
    
    return 0;
}
