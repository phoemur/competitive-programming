/*DIEHARD - DIE HARD
#dynamic-programming

Problem Statement:

The game is simple. You initially have ‘H’ amount of health and ‘A’ amount of armor. At any instant you can live in any of the three places - fire, water and air. After every unit time, you have to change your place of living. For example if you are currently living at fire, you can either step into water or air.

If you step into air, your health increases by 3 and your armor increases by 2

If you step into water, your health decreases by 5 and your armor decreases by 10

If you step into fire, your health decreases by 20 and your armor increases by 5

If your health or armor becomes <=0, you will die instantly

Find the maximum time you can survive.

Input:

The first line consists of an integer t, the number of test cases. For each test case there will be two positive integers representing the initial health H and initial armor A.


Output:

For each test case find the maximum time you can survive.

 

Note: You can choose any of the 3 places during your first move.

 

Input Constraints:

1 <= t <= 10
1 <= H, A <= 1000

Example:

Sample Input:

3
2 10
4 4
20 8

Sample Output:

1
1
5

*/

#include <algorithm>
#include <iostream>
#include <vector>

int solve_recursive(int h, int a, std::vector<std::vector<int>>& dp)
{
    if (a <= 0 || h <= 0)
        return 0;
    else if (dp[h][a] != -1)
        return dp[h][a];
    else
    {
        dp[h][a] = 2 + std::max(solve_recursive(h-17, a+7, dp), 
                                solve_recursive(h-2 , a-8, dp));
        
        return dp[h][a];
    }
}

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int h, a;
        std::cin >> h >> a;
        
        std::vector<std::vector<int>> dp (2000, std::vector<int>(2000, -1));
        
        std::cout << solve_recursive(h, a, dp) - 1 << std::endl;
    }
    
    return 0;
}
