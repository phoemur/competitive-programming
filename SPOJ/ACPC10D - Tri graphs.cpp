/*ACPC10D - Tri graphs
no tags 

Here’s a simple graph problem: Find the shortest path from the top-middle vertex to the bottom-middle vertex in a given tri-graph. A tri-graph is an acyclic graph of (N ≥ 2) rows and exactly 3 columns. Unlike regular graphs, the costs in a tri-graph are associated with the vertices rather than the edges.

a

So, considering the example with N = 4, the cost of going straight down from the top to bottom along the middle vertices is 7 + 13 + 3 + 6 = 29. The layout of the directional edges in the graph are always the same as illustrated in the figure.
Input

Your program will be tested on one or more test cases.
Each test case is specified using N + 1 lines where the first line specifies a single integer (2 ≤ N ≤ 100, 000) denoting the number of rows in the graph. N lines follow, each specifying three integers representing the cost of the vertices on the ith row from left to right. The square of each cost value is less than 1,000,000.
The last case is followed by a line with a single zero.
Output

For each test case, print the following line:
k. n
Where k is the test case number (starting at one,) and n is the least cost to go from the top-middle vertex to the bottom-middle vertex.
Example

Input:
4
13 7 5
7 13 6
14 3 12
15 6 16
0

Output:
1. 22

*/

#include <cstdio>
#include <cstring>
#include <vector>

static const int INF = 1 << 30;

long memo[100001][3];

template<typename T>
T minimum(T t1, T t2)
{
    return t1 < t2 ? t1: t2;
}

template<typename T, typename... Args>
T minimum(T t1, Args... args)
{
    return minimum(t1, minimum(args...));
}

long solve(const std::vector<std::vector<int>>& graph, int i, int j)
{
    if (i >= graph.size())
        return INF;
    else if (memo[i][j] != 0)
        return memo[i][j];
    else if (i == graph.size() - 1 && j == 1)
        memo[i][j] = graph[i][j];
    else if (j == 0)
        memo[i][j] = graph[i][j] + minimum(solve(graph,   i, j+1), 
                                           solve(graph, i+1,   j), 
                                           solve(graph, i+1, j+1));
    else if (j == 1)
        memo[i][j] = graph[i][j] + minimum(solve(graph, i+1, j-1), 
                                           solve(graph, i+1,   j), 
                                           solve(graph, i+1, j+1),
                                           solve(graph,   i, j+1));
    else // j == 2
        memo[i][j] = graph[i][j] + minimum(solve(graph, i+1, j),
                                           solve(graph, i+1, j-1));
        
    return memo[i][j];
}

int main()
{
    int n;
    int cas = 1;
    
    while (std::scanf("%d", &n) != EOF && n != 0)
    {
        std::vector<std::vector<int>> graph (n, std::vector<int>(3, 0));
        std::memset(memo, 0, sizeof(long) * 100001 * 3);
        
        for (auto& row: graph)
            for (auto& elem: row)
                std::scanf("%d", &elem);
            

        std::printf("%d. %ld\n", cas++, solve(graph, 0, 1));
    }
    
    return 0;
}
