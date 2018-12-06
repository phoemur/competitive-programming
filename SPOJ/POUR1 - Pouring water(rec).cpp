/*POUR1 - Pouring water
#gcd #recursion

Given two vessels, one of which can accommodate a litres of water and the other - b litres of water, determine the number of steps required to obtain exactly c litres of water in one of the vessels.

At the beginning both vessels are empty. The following operations are counted as 'steps':

    emptying a vessel,
    filling a vessel,
    pouring water from one vessel to the other, without spilling, until one of the vessels is either full or empty.

 
Input

An integer t, 1<=t<=100, denoting the number of testcases, followed by t sets of input data, each consisting of three positive integers a, b, c, not larger than 40000, given in separate lines.
Output

For each set of input data, output the minimum number of steps required to obtain c litres, or -1 if this is impossible.
Example
Sample input:

2
5
2
3
2
3
4

 
Sample output:

2
-1

*/

#include <algorithm>
#include <iostream>


int DFS(int curra, int currb, int A, int B, int C)
{
    if (curra == C || currb == C)
        return 0;
    else if (curra == 0) // fill a
        return 1 + DFS(A, currb, A, B, C);
    else if (currb == B) // empty b
        return 1 + DFS(curra, 0, A, B, C);
    else
    {
        // transfer maximum possible from a to b without spilling
        int transfer = std::min(curra, B - currb);
        return 1 + DFS(curra - transfer, currb + transfer, A, B, C);
    }
}

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int a, b, c;
        std::cin >> a >> b >> c;
        
        if (c > a && c > b)
            std::cout << -1 << std::endl;
        else if (c % std::__gcd(a,b) != 0)
            std::cout << -1 << std::endl;
        else
            std::cout << std::min(DFS(0, 0, a, b, c), DFS(0, 0, b, a, c)) << std::endl;
    }
    
    return 0;
}
