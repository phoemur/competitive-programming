/*EELCS - Easy Longest Common Subsequence
no tags 

A common subsequence between two strings A and B is defined as 2 sets { i0 , i1 , i2 , i3 , ... , ik } { j0 , j1 , j2 , j3 , ... , jk } such that 0 <= i0 < i1 < i2 < i3 < ... < A.length() and 0 <= j0 < j1 < j2 < j3 < ... < B.length() and A[ i0 ] = B[ j0 ], A[ i1 ] = B[ j1 ] , ... , A[ ik ] = B[ jk ]. Given two strings A and B print the length of the longest common subsequence between them.

i.e. "a", "d","cd" are common subsequence between the two strings "abcd" and "adcd" while "acd" is the longest common subsequence between them.
Input

First line contains a string A (1 <= A.lenth() <= 7).

Second line contains a string B (1 <= B.length() <= 7).

Each string is composed of lower case letters only ('a' -'z').
Output

Prints one line containing the length of the longest common subsequence.

 
Example

Input:

abcd

adcd

Output:
3

*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Recurrence relation
int solve_recursive(const std::string& str1, 
                    int sz1, 
                    const std::string& str2, 
                    int sz2)
{
    if (sz1 == 0 || sz2 == 0)
        return 0;
    else if (str1[sz1 - 1] == str2[sz2 - 1])
        return 1 + solve_recursive(str1, sz1 - 1, str2, sz2 - 1);
    else
        return std::max(solve_recursive(str1, sz1, str2, sz2 - 1), 
                        solve_recursive(str1, sz1 - 1, str2, sz2));
}

// Dynamic programming bottom-up approach
int solve(const std::string& str1, const std::string& str2)
{
    int sz1 = str1.size(), sz2 = str2.size();
    std::vector<std::vector<int>> dp (sz1 + 1, std::vector<int>(sz2 + 1));
    
    for (int i = 0; i <= sz1; ++i)
    {
        for (int j = 0; j <= sz2; ++j)
        {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            
            else if (str1[i-1] == str2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            
            else
                dp[i][j] = std::max(dp[i][j-1], dp[i-1][j]);
        }
    }
    
    return dp[sz1][sz2];
}

// Dynamic programming bottom-up approach optimized
int solve_optimized(const std::string& str1, 
                    int sz1, 
                    const std::string& str2, 
                    int sz2, 
                    int start = 0)
{
    if (start == sz1 || start == sz2) return 0;
    
    int max_size = std::max(sz1, sz2) - start + 1;
    std::vector<std::vector<int>> dp (2, std::vector<int>(max_size, 0));
      
    for (int i = start + 1; i <= sz1; ++i)
    {
        dp[1][0] = 0;
        
        for (int j = start + 1; j <= sz2; ++j)
        {
            if (str1[i-1] == str2[j-1])
                dp[1][j-start] = 1 + dp[0][j-1-start];
            else
                dp[1][j-start] = dp[1][j-1-start] > dp[0][j-start] ? dp[1][j-1-start] : dp[0][j-start];
        }
        
        std::iter_swap(&dp[0], &dp[1]);
    }
    
    /*for (auto& row: dp)
    {
        for (auto& n: row)
        {
            std::cout << n << " ";
        }
        std::cout << "\n";
    }*/
    
    return dp[0][sz2 - start];
}

int main()
{
    std::string str1, str2;
    
    if (std::cin >> str1 >> str2) 
    {
        //std::cout << solve(str1, str2) << std::endl;
        
        int sz1 = str1.size();
        int sz2 = str2.size();
        int start = 0, counter = 0;
        
        // Heuristics: Trim beggining and end if equal
        while (str1[start] == str2[start] && start < sz1 && start < sz2)
        {
            ++start;
            ++counter;
        }
        while (str1[sz1 - 1] == str2[sz2 - 1] && start < sz1 && start < sz2)
        {
            --sz1;
            --sz2;
            ++counter;
        }
        
        std::cout << counter + solve_optimized(str1, sz1, str2, sz2, start) << std::endl;
    }
        
    return 0;
}
