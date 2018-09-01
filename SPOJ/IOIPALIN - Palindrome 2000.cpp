/*IOIPALIN - Palindrome 2000
#lcs #dynamic-programming

A palindrome is a symmetrical string, that is, a string read identically from left to right as well as from right to left. You are to write a program which, given a string, determines the minimal number of characters to be inserted into the string in order to obtain a palindrome. As an example, by inserting 2 characters, the string "Ab3bd" can be transformed into a palindrome ("dAb3bAd" or "Adb3bdA"). However, inserting fewer than 2 characters does not produce a palindrome.
Input

The first line contains one integer: the length of the input string N, 3≤N≤5000. The second line contains one string with length N. The string is formed from uppercase letters from ‘A’ to ‘Z’, lowercase letters from ‘a’ to ‘z’ and digits from ‘0’ to ‘9’. Uppercase and lowercase letters are to be considered distinct.
Output

The first line contains one integer, which is the desired minimal number.
Example

Input:
5
Ab3bd

Output:
2

*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

// Recurrence relation
int solve_recursive(const std::string& str, int l, int r)
{
    if (l == r) // Base case length 1
    {
        return 0;
    }
    else if (l == r - 1) // Base case length 2
    {
        if (str[l] == str[r]) return 0;
        else return 1;
    }
    else if (str[l] == str[r]) // Case begin == end
    {
        return solve_recursive(str, l+1, r-1);
    }
    else // Recurrence
    {
        return 1 + std::min(solve_recursive(str, l+1, r), 
                            solve_recursive(str, l, r-1));
    }
}

// Dynamic Programming Bottom up -> tabulation
inline int solve(const std::string& str)
{
    const int sz = str.size();
    std::vector<std::vector<int>> dp (sz, std::vector<int>(sz, std::numeric_limits<int>::max()));
    
    // Base case
    for (std::size_t i = 0; i < sz; ++i)
    {
        dp[i][i] = 0;
    }
    
    // Fill table
    for (int l = sz - 2; l >= 0; --l)
    {
        for (int r = l + 1; r < sz; ++r)
        {
            if (l == r - 1)
                if (str[l] == str[r]) dp[l][r] = 0;
                else dp[l][r] = 1;
            else if (str[l] == str[r])
                dp[l][r] = dp[l+1][r-1];
            else
                dp[l][r] = 1 + std::min(dp[l+1][r], dp[l][r-1]);
        }
    }
    
    return dp[0][str.size() - 1];
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int t;
    std::cin >> t;
    
    std::string input;
    
    while (t--)
    {
        if (std::cin >> input)
        {
            // std::cout << solve_recursive(input, 0, input.size()-1) << std::endl;
            std::cout << solve(input) << std::endl;
        }
    }
    
    return 0;
}
