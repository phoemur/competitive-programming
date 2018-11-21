/*BAT2 - BATMAN2
#dynamic-programming

 
" Alfred: I'll get this to Mr. Fox, but no more. I've sewn you up, I've set your bones, but I won't bury you. I've buried enough members of the Wayne family.  "

 

" Alfred: I'll get this to Mr. Fox, but no more. I've sewn you up, I've set your bones, but I won't bury you. I've buried enough members of the Wayne family.  "
After being promised the software to erase her criminal record, Catwoman agrees to take Batman to Bane. They manage to defeat all of BANE's men but ended up heading into a MAZE trap . BANE would call this maze as the LIS MAZE . He would hide himself in one of the rooms .Each of these rooms have a number(tag) associated with it. The speciality of the maze is that once you enter any room it will only lead you to rooms with a higher tag in the direction you move . BATMAN and Catwoman decide to move in opposite directions trying their luck to maximize the number of rooms they search . (They can start with any room , need not be the same)

" Catwoman : Never steal from someone you can't outrun, kid. " 

 
Input

 

t , number of testcases
n , number of rooms
n integers  giving the tag associated with the rooms

 
Output

 

The maximum number of rooms searched.

 

Constraints : 

1 < = n  < = 100

 

 
Example

Input:

1
6
5 3 4 6 1 2


Output:

5


*/

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

int dp[105][105][105];

// DP top-down
int solve_recursive(const std::vector<int>& vec, 
                    int idx,
                    int batman, // Decreasing
                    int woman)  // Increasing
{
    if (idx <= 0)
        return 0;
    else if (idx == 1)
    {
        if (vec[idx] > vec[batman] || vec[idx] < vec[woman])
            return 1;
        else
            return 0;
    }
    else if (dp[idx][batman][woman] != 0)
        return dp[idx][batman][woman];
    else
    {
        dp[idx][batman][woman] = solve_recursive(vec, idx-1, batman, woman); // Do not include this element
        
        if (batman == 0 || vec[idx] > vec[batman])
            dp[idx][batman][woman] = std::max(dp[idx][batman][woman], 1 + solve_recursive(vec, idx-1, idx, woman));
        
        if (woman == 0 || vec[idx] < vec[woman])
            dp[idx][batman][woman] = std::max(dp[idx][batman][woman], 1 + solve_recursive(vec, idx-1, batman, idx));
        
        return dp[idx][batman][woman];
    }
}


// DP bottom-up
int solve(const std::vector<int>& vec)
{
    const int n = vec.size() - 1;
        
    for (int i = 0; i <= n; ++i)
    {
        for (int x = n; x >= 0; --x)
        {
            for (int y = n; y >= 0; --y)
            {
                if (i == 0)
                    dp[i][x][y] = 0;
                else if (i == 1)
                {
                    if (x <= n && vec[i] > vec[x])
                        dp[i][x][y] = 1;
                    else if (y <= n && vec[i] < vec[y])
                        dp[i][x][y] = 1;
                    else
                        dp[i][x][y] = 0;
                }
                else
                {
                    dp[i][x][y] = dp[i-1][x][y];
                    
                    if (x == 0 || vec[i] > vec[x])
                        dp[i][x][y] = std::max(dp[i][x][y], 1 + dp[i-1][i][y]);
                    
                    if (y == 0 || vec[i] < vec[y])
                        dp[i][x][y] = std::max(dp[i][x][y], 1 + dp[i-1][x][i]);
                }
            }
        }
    }
    
    return dp[n][0][0];
}
  
int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        std::memset(dp, 0, sizeof(int) * 105 * 105 * 105);
        
        int n;
        std::cin >> n;
        
        std::vector<int> vec (n+1);
        for (int i = 1; i <= n; ++i) std::cin >> vec[i];
        
        //std::cout << solve_recursive(vec, n, 0, 0) << std::endl;
        std::cout << solve(vec) << std::endl;
    }
    
    return 0;
}
