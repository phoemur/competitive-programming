/*
MISERMAN - Wise And Miser
#dynamic-programming

Jack is a wise and miser man. Always tries to save his money.

One day, he wants to go from city A to city B. Between A and B, there are N number of cities(including B and excluding A) and in each city there are M buses numbered from 1 to M. And the fare of each bus is different. Means for all N*M busses, fare (K) may be different or same. Now Jack has to go from city A to city B following these conditions:

    At every city, he has to change the bus.
    And he can switch to only those buses which have number either equal or 1 less or 1 greater to the previous.

You are to help Jack to go from A to B by spending the minimum amount of money.

N, M, K <= 100.
Input

Line 1:    N M
Line 2-:    NxM Grid

Each row lists the fares the M busses to go form the current city to the next city.
Output

Single Line containing the minimum amount of fare that Jack has to give.
Example

Input:
5 5
1  3  1  2  6
10 2  5  4  15
10 9  6  7  1
2  7  1  5  3
8  2  6  1  9

Output:
10

Explanation

1 -> 4 -> 1 -> 3 -> 1: 10
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

int solve(const std::vector<std::vector<int>>& grid)
{
    std::vector<std::vector<int>> dp (grid.size(), 
                                      std::vector<int>(grid[0].size(), 
                                                       std::numeric_limits<int>::max()));
    
    int res = std::numeric_limits<int>::max();
    
    for (int j=0; j<grid[0].size(); ++j)
        dp[0][j] = grid[0][j];
    
    for (int i=1; i<grid.size(); ++i) {
        for (int j=0; j<grid[i].size(); ++j) {
            
            if (j-1 >= 0) 
                dp[i][j] = std::min(dp[i][j], grid[i][j] + dp[i-1][j-1]);
            
            dp[i][j] = std::min(dp[i][j], grid[i][j] + dp[i-1][j]);
            
            if (j+1 < grid[i-1].size()) 
                dp[i][j] = std::min(dp[i][j], grid[i][j] + dp[i-1][j+1]);
            
          
            if (i == grid.size() - 1)
                res = std::min(res, dp[i][j]);
        }
    }
    
    return res;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int rows, cols;
    std::cin >> rows >> cols;
        
    std::vector<std::vector<int>> grid (rows, std::vector<int>(cols, 0));
       
    for (auto& line: grid)
        std::copy_n(std::istream_iterator<int>(std::cin), cols, std::begin(line));
        
    std::cout << solve(grid) << std::endl;
    
    return 0;
}
