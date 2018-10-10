/*MTOTALF - Total Flow
#max-flow

English 	Vietnamese

Farmer John always wants his cows to have enough water and thus has
made a map of the N (1 <= N <= 700) water pipes on the farm that
connect the well to the barn. He was surprised to find a wild mess
of different size pipes connected in an apparently haphazard way.
He wants to calculate the flow through the pipes.

Two pipes connected in a row allow water flow that is the minimum
of the values of the two pipe's flow values. The example of a pipe
with flow capacity 5 connecting to a pipe of flow capacity 3 can
be reduced logically to a single pipe of flow capacity 3:

  +---5---+---3---+    ->    +---3---+

Similarly, pipes in parallel let through water that is the sum of
their flow capacities:

    +---5---+
 ---+       +---    ->    +---8---+
    +---3---+

Finally, a pipe that connects to nothing else can be removed; it
contributes no flow to the final overall capacity:

    +---5---+
 ---+               ->    +---3---+
    +---3---+--

All the pipes in the many mazes of plumbing can be reduced using
these ideas into a single total flow capacity.

Given a map of the pipes, determine the flow capacity between the
well (A) and the barn (Z).

Consider this example where node names are labeled with letters:

                 +-----------6-----------+
        A+---3---+B                      +Z
                 +---3---+---5---+---4---+
                         C       D

Pipe BC and CD can be combined:

                 +-----------6-----------+
        A+---3---+B                      +Z
                 +-----3-----+-----4-----+
                             D

Then BD and DZ can be combined:

                 +-----------6-----------+
        A+---3---+B                      +Z
                 +-----------3-----------+

Then two legs of BZ can be combined:

                 B
        A+---3---+---9---+Z

Then AB and BZ can be combined to yield a net capacity of 3:

        A+---3---+Z

Write a program to read in a set of pipes described as two endpoints
and then calculate the net flow capacity from 'A' to 'Z'. All
networks in the test data can be reduced using the rules here.

Pipe i connects two different nodes a_i and b_i (a_i in range
'A-Za-z'; b_i in range 'A-Za-z') and has flow F_i (1 <= F_i <=
1,000). Note that lower- and upper-case node names are intended
to be treated as different.


INPUT

* Line 1: A single integer: N

* Lines 2..N + 1: Line i+1 describes pipe i with two letters and an
        integer, all space-separated: a_i, b_i, and F_i

SAMPLE INPUT  

5
A B 3
B C 3
C D 5
D Z 4
B Z 6

OUTPUT

* Line 1: A single integer that the maximum flow from the well ('A')
        to the barn ('Z')

SAMPLE OUTPUT  

3

*/

#include <algorithm>
#include <cstring>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

/* Returns true if there is a path from source dest.
 * Also fills parent to store the path */
template<std::size_t SIZE>
bool bfs(int graph[SIZE][SIZE],
         int source,
         int dest,
         int parent[SIZE])
{
    
    bool visited[SIZE] = {false};
    
    std::queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;
    
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        
        for (unsigned v = 0; v < SIZE; ++v) {
            if (graph[curr][v] > 0) { //there is an unvisited edge between curr and v
                if (!visited[v]) { 
                    q.push(v);
                    parent[v] = curr;
                    visited[v] = true;
                }
            }
        }
    }
    
    return visited[dest]; //true if there is a path, false otherwise
}

// Returns the maximum flow from source to dest in the given graph
template<std::size_t SIZE>
int ford_fulkerson(int graph[SIZE][SIZE],
                   int source,
                   int dest)
{
    // copy
    int residual[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            residual[i][j] = graph[i][j];
    
    
    int parent[SIZE]; // This array is filled by BFS and to store path
    int max_flow = 0; // There is no flow initially
    
    // Augment the flow while tere is path from source to sink
    while (bfs(residual, source, dest, parent)) {
        // Find minimum residual capacity of the edges along the
        // path filled by BFS. Or we can say find the maximum flow
        // through the path found.
        int path_flow = std::numeric_limits<int>::max();
        for (int v = dest; v != source; v = parent[v]) {
            int u = parent[v];
            path_flow = std::min(path_flow, residual[u][v]);
        }
        
        // update residual capacities of the edges and reverse edges
        // along the path
        for (int v = dest; v != source; v = parent[v]) {
            int u = parent[v];
            residual[u][v] -= path_flow;
            residual[v][u] += path_flow;
        }
        
        // Add path flow to overall flow
        max_flow += path_flow;
    }
    
    return max_flow;
}

int main()
{
    static const int SIZE = 'z' - 'A' + 1;
    
    int n;
    std::cin >> n;
    
    int graph[SIZE][SIZE];
    std::memset(graph, 0, sizeof(int) * SIZE * SIZE);
    
    while (n--)
    {
        char source, dest;
        int flow;
        std::cin >> source >> dest >> flow;
               
        graph[source - 'A'][dest - 'A'] += flow;
    }
    
    std::cout << ford_fulkerson(graph, 0, 'Z' - 'A') << std::endl;
    
    return 0;
}
