/*BEENUMS - Beehive Numbers
no tags 

A beehive is an enclosed structure in which some honey bee species live and raise their
young. In this problem we consider a two-dimensional sketch of the beehives. Each
beehive is composed of a certain number of cells, where each cell is a regular hexagon.
Each cell may have some neighbors, which are other cells that share a side with that cell.
A cell with exactly 6 neighbors is an internal cell, while a cell with fewer neighbors is an
external one. Notice that an external cell can always be changed to internal by adding
some neighbor cells.


We are interested in a particular class of beehives. This class of valid beehives is defined
recursively as follows: a) a single cell is a valid beehive; and b) given a valid beehive B,
if we add the minimum number of cells such that each external cell of B becomes an
internal cell, the result is a valid beehive.

The number of cells in a valid beehive is called a beehive number. Given an integer N ,
you must decide whether it is a beehive number.
Input

Each test case is described using a single line. The line contains an integer N (1 ≤ N ≤
109 ). The end of input is indicated with a line containing a single −1.
Output

For each test case, output a single line containing an uppercase “Y” if N is a beehive
number, or an uppercase “N” otherwise.
Example

Input:
43
1
7
19
15
-1

Output:
N
Y
Y
Y
N

*/

#include <cmath>
#include <iostream>

int main()
{
    for (long n; std::cin >> n && n != -1;)
    {
        if ((n - 1) % 6 == 0)
        {
            double a = (std::sqrt(1 + 4 * ((n - 1) / 3)) - 1) / 2;
            
            if (static_cast<int>(a) - a == 0)
                std::cout << "Y\n";
            else
                std::cout << "N\n";
        }
        else
            std::cout << "N\n";
    }
    
    return 0;
}
