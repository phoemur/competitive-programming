/*Zonal Computing Olympiad 2014, 30 Nov 2013

In ICO School, all students have to participate regularly in SUPW. There is a different SUPW activity each day, and each activity has its own duration. The SUPW schedule for the next term has been announced, including information about the number of minutes taken by each activity.

Nikhil has been designated SUPW coordinator. His task is to assign SUPW duties to students, including himself. The school's rules say that no student can go three days in a row without any SUPW duty.

Nikhil wants to find an assignment of SUPW duty for himself that minimizes the number of minutes he spends overall on SUPW.

Input format

Line 1: A single integer N, the number of days in the future for which SUPW data is available.

Line 2: N non-negative integers, where the integer in position i represents the number of minutes required for SUPW work on day i.

Output format

The output consists of a single non-negative integer, the minimum number of minutes that Nikhil needs to spend on SUPW duties this term

Sample Input 1

10
3 2 1 1 2 3 1 3 2 1


Sample Output 1

4


(Explanation: 1+1+1+1)

Sample Input 2

8
3 2 3 2 3 5 1 3


Sample Output 2

5


(Explanation: 2+2+1)

Test data

There is only one subtask worth 100 marks. In all inputs:

• 1 ≤ N ≤ 2×105

• The number of minutes of SUPW each day is between 0 and 104, inclusive.*/

#include <algorithm>
#include <iostream>
#include <vector>

constexpr static int INF = 1 << 30;

// Just to ilustrate recurrence relation
int solve_recursive(const std::vector<int>& vec, int pos, int days_left)
{
    if (days_left == 0) // Screwed it up
        return INF;
    else if (pos == 0) // All done ;)
        return 0;
    else if (days_left == 1) // Must work today :-(
        return vec[pos-1] + solve_recursive(vec, pos-1, 3);
    else // Should I work or not ¯\_(ツ)_/¯
        return std::min(vec[pos-1] + solve_recursive(vec, pos-1, 3), 
                        solve_recursive(vec, pos-1, days_left-1));
}

// Dynamic programming bottom-up approach
int solve(const std::vector<int>& vec)
{
    const int n = vec.size();
    
    std::vector<std::vector<int>> dp (n+1, std::vector<int>(4));
    
    // Fill table according to recurrence relation expressed above
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= 3; ++j)
        {
            if (j == 0)
                dp[i][j] = INF;
            else if (i == 0)
                dp[i][j] = 0;
            else if (j == 1)
                dp[i][j] = vec[i-1] + dp[i-1][3];
            else
                dp[i][j] = std::min(vec[i-1] + dp[i-1][3], dp[i-1][j-1]);
        }
    }
    
    return dp[n][3];
}

// Solve like before but with less memory use
int solve_optimized(const std::vector<int>& vec)
{
    const int n = vec.size();
    
    std::vector<std::vector<int>> dp (2, std::vector<int>(4, 0));
    dp[0][0] = INF;
    
    for (int i = 1; i <= n; ++i)
    {
        dp[1][0] = INF;
        dp[1][1] = vec[i-1] + dp[0][3];
        dp[1][2] = std::min(vec[i-1] + dp[0][3], dp[0][1]);
        dp[1][3] = std::min(vec[i-1] + dp[0][3], dp[0][2]);
        
        std::iter_swap(&dp[0], &dp[1]);
    }
    
    return dp[0][3];
}

int main()
{
    int n;
    std::cin >> n;
    
    std::vector<int> vec (n);
    for (auto& elem: vec) std::cin >> elem;
    
    // std::cout << solve_recursive(vec, n, 3) << std::endl;
    // std::cout << solve(vec) << std::endl;
    std::cout << solve_optimized(vec) << std::endl;
    
    return 0;
}
