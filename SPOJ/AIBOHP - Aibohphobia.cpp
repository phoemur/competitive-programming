/*AIBOHP - Aibohphobia
#dynamic-programming

BuggyD suffers from AIBOHPHOBIA - the fear of Palindromes. A palindrome is a string that reads the same forward and backward.

To cure him of this fatal disease, doctors from all over the world discussed his fear and decided to expose him to large number of palindromes. To do this, they decided to play a game with BuggyD. The rules of the game are as follows:

BuggyD has to supply a string S. The doctors have to add or insert characters to the string to make it a palindrome. Characters can be inserted anywhere in the string.

The doctors took this game very lightly and just appended the reverse of S to the end of S, thus making it a palindrome. For example, if S = "fft", the doctors change the string to "ffttff".

Nowadays, BuggyD is cured of the disease (having been exposed to a large number of palindromes), but he still wants to continue the game by his rules. He now asks the doctors to insert the minimum number of characters needed to make S a palindrome. Help the doctors accomplish this task.

For instance, if S = "fft", the doctors should change the string to "tfft", adding only 1 character.
Input

The first line of the input contains an integer t, the number of test cases. t test cases follow.

Each test case consists of one line, the string S. The length of S will be no more than 6100 characters, and S will contain no whitespace characters.
Output

For each test case output one line containing a single integer denoting the minimum number of characters that must be inserted into S to make it a palindrome.
Example

Input:
1
fft

Output:
1

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
