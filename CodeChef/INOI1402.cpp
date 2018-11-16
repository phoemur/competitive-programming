/*Indian National Olympiad in Informatics 2014

Nikhil’s slogan has won the contest conducted by Drongo Airlines and he is entitled to a free ticket between any two destinations served by the airline. All cities served by Drongo Airlines can be reached from each other by some sequence of connecting flights. Nikhil is allowed to take as many connecting flights as needed, but he must take the cheapest route between his chosen destinations.

Each direct flight between two cities has a fixed price. All pairs of cities connected by direct flights have flights in both directions and the price is the same in either direction. The price for a sequence of connecting flights is the sum of the prices of the direct flights along the route.

Nikhil has information about the cost of each direct flight. He would like to maximize the value of his prize, so he would like to choose a pair of cities on the network for which the cost of the cheapest route is as high as possible.

For instance, suppose the network consists of four cities {1, 2, 3, 4}, connected as shown on the right.

In this case, Nikhil should choose to travel between 1 and 4, where the cheapest route has cost 19. You can check that for all other pairs of cities, the cheapest route has a smaller cost. For instance, notice that though the direct flight from 1 to 3 costs 24, there is a cheaper route of cost 12 from 1 to 2 to 3.
Input format

    Line 1 : Two space-separated integers, C and F . C is the number of cities on the network, numbered 1, 2, . . . , C. F is the number of pairs of cities connected by a direct flight.
    Lines 2 to F + 1 : Each line describes one direct flight between a pair of cities and consists of three integers, x, y and p, where x and y are the two cities connected by this flight and p is the price of this

 

For all direct flights, x ƒ= y and no pair of cities is connected by more than one direct flight. If there is a direct flight from x to y with price p, there is also a flight from y to x with price p and exactly one of these two will be listed.
Output format

The output consists of a single integer, the maximum cost among the cheapest routes between all pairs of cities across the airline’s network.
Test Data

The testdata is grouped into three subtasks. In all subtasks, 2 ≤ C ≤ 230 and 1 ≤ F ≤ 23665. In addition, each subtask has the following constraints on the inputs.

    Subtask 1 (20 marks) : F = C − 1 (that is, the airline network is a tree) and p = 1 for each direct flight.
    Subtask 2 (30 marks) : There is no constraint on the shape of the network, but for each direct flight, p = 1.
    Subtask 3 (50 marks) : There is no constraint on the shape of the network, but for each direct flight, 0 ≤ p ≤ 105.

Example

Here is the sample input and output corresponding to the example above:
Sample input

4 5
1 2 10
1 3 24
2 3 2
2 4 15
3 4 7

Sample output

19


Note: Your program should not print anything other than what is specified in the output format. Please remove all diagnostic print statements before making your final submission. A program with extraneous output will be treated as incorrect!
*/

#include <algorithm>
#include <cstdio>
#include <vector>

constexpr static int INF = 1 << 30;

int main()
{
    int c, f;
    std::scanf("%d %d", &c, &f);
    
    // Init adjacency Matrix
    std::vector<std::vector<long>> dist (c, std::vector<long>(c, INF));
    for (int i = 0; i < c; ++i)
        dist[i][i] = 0; // Distance to itself is zero
    
    while (f--)
    {
        int x, y, p;
        std::scanf("%d %d %d", &x, &y, &p);
        --x;
        --y;
        
        dist[x][y] = p;
        dist[y][x] = p;
    }
    
    // Floyd-Warshall Algorithm
    for (int k=0; k < c; ++k)
        for (int i=0; i < c; ++i)
            for (int j=0; j < c; ++j)
                if (dist[i][k] + dist[k][j] < dist[i][j]) 
                    dist[i][j] = dist[i][k] + dist[k][j];

    long res = -INF;
    for (auto& row: dist)
        for (auto& cell: row)
            if (cell != INF)
                res = std::max(res, cell);
            
    std::printf("%ld\n", res);
    
    return 0;
}
