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

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

static const int INF = 1 << 30;

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

// Recurrence relation
long solve_recursive(const std::vector<std::vector<int>>& graph, int i, int j)
{
    if (i >= graph.size())
        return INF;
    else if (i == graph.size() - 1 && j == 1)
        return graph[i][j];
    else if (j == 0)
        return graph[i][j] + minimum(solve_recursive(graph,   i, j+1), 
                                     solve_recursive(graph, i+1,   j), 
                                     solve_recursive(graph, i+1, j+1));
    else if (j == 1)
        return graph[i][j] + minimum(solve_recursive(graph, i+1, j-1), 
                                     solve_recursive(graph, i+1,   j), 
                                     solve_recursive(graph, i+1, j+1),
                                     solve_recursive(graph,   i, j+1));
    else // j == 2
        return graph[i][j] + minimum(solve_recursive(graph, i+1, j),
                                     solve_recursive(graph, i+1, j-1));
}

// Dynamic Programming bottom up approach -> tabulation
long solve_bottom_up(const std::vector<std::vector<int>>& graph)
{
    const int n = graph.size();
    
    std::vector<std::vector<long>> dp (n, std::vector<long>(3, INF));
    
    // Base cases
    dp[n-1][1] = graph[n-1][1];
    dp[n-1][0] = dp[n-1][1] + graph[n-1][0];
    dp[n-1][2] = INF;
    
    // Fill table
    for (int i = n-2; i >= 0; --i)
    {
        for (int j = 2; j >= 0; --j)
        {
            if (j == 0)
                dp[i][j] = graph[i][j] + minimum(dp[i][j+1], dp[i+1][j], dp[i+1][j+1]);
            else if (j == 1)
                dp[i][j] = graph[i][j] + minimum(dp[i+1][j-1], dp[i+1][j], dp[i+1][j+1], dp[i][j+1]);
            else
                dp[i][j] = graph[i][j] + minimum(dp[i+1][j], dp[i+1][j-1]);
        }
    }
    
    return dp[0][1];
}

// Dynamic Programming bottom up approach -> less memory use
int solve_optimized(const std::vector<std::vector<int>>& graph)
{
    const int n = graph.size();
    
    std::vector<std::vector<int>> dp (2, std::vector<int>(3, INF));
    
    // Base cases
    dp[1][1] = graph[n-1][1];
    dp[1][0] = dp[1][1] + graph[n-1][0];
    dp[1][2] = INF;
    
    // Fill table
    for (int i = n-2; i >= 0; --i)
    {
        for (int j = 2; j >= 0; --j)
        {
            if (j == 0)
                dp[0][j] = graph[i][j] + minimum(dp[0][j+1], dp[1][j], dp[1][j+1]);
            else if (j == 1)
                dp[0][j] = graph[i][j] + minimum(dp[1][j-1], dp[1][j], dp[1][j+1], dp[0][j+1]);
            else
                dp[0][j] = graph[i][j] + minimum(dp[1][j], dp[1][j-1]);
        }
        
        std::iter_swap(&dp[0], &dp[1]);
    }
    
    return dp[1][1];
}

int main()
{
    int n;
    int cas = 1;
    
    while (std::scanf("%d", &n) != EOF && n != 0)
    {
        std::vector<std::vector<int>> graph (n, std::vector<int>(3, 0));
        
        for (auto& row: graph)
            for (auto& elem: row)
                std::scanf("%d", &elem);

        // std::printf("%d. %ld\n", cas++, solve_recursive(graph, 0, 1));
        // std::printf("%d. %ld\n", cas++, solve_bottom_up(graph));
        std::printf("%d. %d\n", cas++, solve_optimized(graph));
    }
    
    return 0;
}
