/*MAXLN - THE MAX LINES
no tags 

In this problem you will be given a half-circle. The half-circle’s radius is r. You can take any point A on the half-circle and draw 2 lines from the point to the two sides of the diameter(AB and AC). Let the sum of square of one line’s length and the other line’s length is s

Like in the figure s = AB2 + AC. And BC = 2r.

Now given r you have to find the maximum value of s. That is you have to find point A such that AB2 + AC is maximum.
Input

First line of the test case will be the number of test case T (1 <= T <= 1000). Then T lines follows. On each line you will find a integer number r (1 <= r <= 1000000); each representing the radius of the half-circle.
Output
For each input line, print a line containing "Case I: ", where I is the test case number and the maximum value of s. Print 2 digit after decimal (Errors should be less then .01).

Example

Sample Input:
1
1

Sample Output:
Case 1: 4.25

*/

#include <iostream>
#include <iomanip>

int main()
{
    int tests;
    std::cin >> tests;
    
    for (int cas = 1; cas <= tests; ++cas)
    {
        double r;
        std::cin >> r;
        
        std::cout << "Case " << cas << ": " 
                  << std::setprecision(2) << std::fixed 
                  << 4*r*r + 0.25 << std::endl;
    }
    
    return 0;
}
