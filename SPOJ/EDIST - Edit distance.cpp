/*EDIST - Edit distance
#dynamic-programming

You are given two strings, A and B. Answer, what is the smallest number of operations you need to
transform A to B?

Operations are:

    Delete one letter from one of strings
    Insert one letter into one of strings
    Replace one of letters from one of strings with another letter

Input

T - number of test cases

For each test case:

    String A
    String B

Both strings will contain only uppercase characters and they won't be longer than 2000 characters. 

There will be 10 test cases in data set.
Output

For each test case, one line, minimum number of operations.
Example

Input:
1
FOOD
MONEY

Output:
4

*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Recurrence relation
int solve_recursive(const std::string& str1, int pos1, const std::string& str2, int pos2)
{
    if (pos1 == 0) return pos2;
    else if (pos2 == 0) return pos1;
    else if (str1[pos1-1] == str2[pos2-1]) return solve_recursive(str1, pos1-1, str2, pos2-1);
    else
    {
        return 1 + std::min(solve_recursive(str1, pos1, str2, pos2-1), // Insert 
                            std::min(solve_recursive(str1, pos1-1, str2, pos2), // Remove
                                     solve_recursive(str1, pos1-1, str2, pos2-1))); // Replace
    }
}

// Dynamic programming bottom-up approach
int solve(const std::string& str1, const std::string& str2)
{
    const int sz1 = str1.size(), sz2 = str2.size();
    
    std::vector<std::vector<int>> dp (sz1+1, std::vector<int>(sz2+1));
    
    // Fill table according to recurrence relation expressed above
    for (int i = 0; i <= sz1; ++i)
    {
        for (int j = 0; j <= sz2; ++j)
        {
            if (i == 0)
                dp[i][j] = j;
            else if (j == 0)
                dp[i][j] = i;
            else if (str1[i-1] == str2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + std::min(dp[i][j-1], std::min(dp[i-1][j], dp[i-1][j-1]));
        }
    }
    
    return dp[sz1][sz2];
}

// Dynamic programming bottom-up approach optimized for less memory use
int solve_optimized(const std::string& str1, const std::string& str2)
{
    const int sz1 = str1.size(), sz2 = str2.size();
    
    std::vector<std::vector<int>> dp (2, std::vector<int>(sz2+1));
    
    // Fill table according to recurrence relation expressed above
    for (int i = 0; i <= sz1; ++i)
    {
        for (int j = 0; j <= sz2; ++j)
        {
            if (i == 0)
                dp[1][j] = j;
            else if (j == 0)
                dp[1][j] = i;
            else if (str1[i-1] == str2[j-1])
                dp[1][j] = dp[0][j-1];
            else
                dp[1][j] = 1 + std::min(dp[1][j-1], std::min(dp[0][j], dp[0][j-1]));
        }
        
        std::iter_swap(&dp[0], &dp[1]);
    }
    
    return dp[0][sz2];
}


int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        std::string a, b;
        std::cin >> a >> b;
        
        //std::cout << solve_recursive(a, a.size(), b, b.size()) << std::endl;
        //std::cout << solve(a, b) << std::endl;
        std::cout << solve_optimized(a, b) << std::endl;
    }
    
    
    return 0;
}
