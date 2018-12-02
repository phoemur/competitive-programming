/*MICEMAZE - Mice and Maze
#shortest-path #bfs #dijkstra-s-algorithm

A set of laboratory mice is being trained to escape a maze. The maze is made up of cells, and each cell is connected to some other cells. However, there are obstacles in the passage between cells and therefore there is a time penalty to overcome the passage Also, some passages allow mice to go one-way, but not the other way round.

Suppose that all mice are now trained and, when placed in an arbitrary cell in the maze, take a path that leads them to the exit cell in minimum time.

We are going to conduct the following experiment: a mouse is placed in each cell of the maze and a count-down timer is started. When the timer stops we count the number of mice out of the maze.
Problem

Write a program that, given a description of the maze and the time limit, predicts the number of mice that will exit the maze. Assume that there are no bottlenecks is the maze, i.e. that all cells have room for an arbitrary number of mice.
Input

The maze cells are numbered $1, 2, \ldots, N$, where $N$ is the total number of cells. You can assume that $N \le 100$.

The first three input lines contain $N$, the number of cells in the maze, $E$, the number of the exit cell, and the starting value $T$ for the count-down timer (in some arbitrary time unit).

The fourth line contains the number $M$ of connections in the maze, and is followed by $M$ lines, each specifying a connection with three integer numbers: two cell numbers $a$ and $b$ (in the range $1, \ldots, N$) and the number of time units it takes to travel from $a$ to $b$.

Notice that each connection is one-way, i.e., the mice can't travel from $b$ to $a$ unless there is another line specifying that passage. Notice also that the time required to travel in each direction might be different.
Output

The output consists of a single line with the number of mice that reached the exit cell $E$ in at most $T$ time units.
Example

Input:
4 
2 
1
8
1 2 1
1 3 1
2 1 1
2 4 1
3 1 1
3 4 1
4 2 1
4 3 1

Output:
3

*/

#include <algorithm>
#include <iostream>
#include <vector>

#define INF 9999999

void floydWarshall(std::vector<std::vector<int>>& graph)
{
    for (std::size_t k = 0; k < graph.size(); ++k)
         for (std::size_t i = 0; i < graph.size(); ++i)
             for (std::size_t j = 0; j < graph.size(); ++j)
                 if (graph[i][k] + graph[k][j] < graph[i][j])
                    graph[i][j] = graph[i][k] + graph[k][j];
}

int main()
{
    int n, e, t, m;
    std::cin >> n >> e >> t >> m;
    e--;
    
    // Build Adjacency Matrix
    std::vector<std::vector<int>> graph (n, std::vector<int>(n, INF)); 
    for (int i = 0; i < n; ++i)
        graph[i][i] = 0; // Distance to itself
        
    while (m--)
    {
        int s, d, w;
        std::cin >> s >> d >> w;
        s--; d--;
        
        // We add reversed edges!
        if (graph[d][s] == INF)
            graph[d][s] = w; // Single edge
        else
            graph[d][s] += w; // Multiple edges
    }
    
    floydWarshall(graph);
    
    // Count cells reachable from the end in t time or less
    auto res = std::count_if(graph[e].begin(), 
                             graph[e].end(),
                             [t](int a){return a <= t;});
    
    std::cout << res << std::endl;
    
    return 0;
}
