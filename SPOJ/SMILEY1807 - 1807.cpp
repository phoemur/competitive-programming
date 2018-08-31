/*SMILEY1807 - 1807
#dynamic-programming

There is a SmileyLand of angels. The queen of all angels Smiley1807 loves the number 1807. She is so much obsessed with 1807 that she asked her programmer friend to write a program to find the length of the largest sub sequence having digits 1,8,0 and 7 in order. For example if given sequence is 1800777700088888000777 then one of the largest sub sequence satisfying the above condition is 1800000000777 (there is one more possibility of 1888888000777)and hence the length of largest sub sequence is 13.
Input

The input contains only one test case.

The test case consist of only one sequence which may be as long as 10^6. There are only 1,8,0 or 7 present in the input sequence.
Output

Output contains only one line containing the length of the largest sub-sequence.
Example

Input:
1800777700088888000777

Output:
13

Explanation
1800000000777 is the largest sub-sequence

Note

Only C, C++, C#, Haskell, Java, Lisp, Python and Scala are allowed! 
 

*/

#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

// Won't work -> O(n^2)
inline int LIS_modified(const std::string& input)
{
    /*static std::map<char,char> order {{'1', 0},
                                      {'8', 1},
                                      {'0', 2},
                                      {'7', 3}};*/
                                      
    static const int order[] = {2, 0, 9, 9, 9, 9, 9, 3, 1, 9};    
    const int n = input.size();
    if (n < 4) return 0;
    
    int result = 0;
    std::vector<int> dp (n, 1);
    
    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (order[input[i] - '0'] >= order[input[j] - '0'] && dp[i] < dp[j] + 1)
            {
                dp[i] = dp[j] + 1;
                result = std::max(result, dp[i]);
            }
        }
    }
    
    return result;
}

// This works -> O(n)
inline int solve(const std::string& input)
{
    if (input.size() < 4) return 0;
    
    std::array<int, 4> dp {0};
      
    for (char c: input)
    {
        switch(c)
        {
            case '1':
                ++dp[0];
                break;
            case '8':
                if(dp[0] > 0 || dp[1] > 0)
                    dp[1] = std::max(dp[0] , dp[1]) + 1;
                
                break;
            case '0':
                if(dp[1] > 0 || dp[2] > 0)
                    dp[2] = std::max(dp[1] , dp[2]) + 1;

                break;
            case '7':
                if(dp[2] > 0 || dp[3] > 0)
                    dp[3] = std::max(dp[2] , dp[3]) + 1;

                break;
            default:
                break;
        }
    }
    
    return dp.back();
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    std::string input;
    
    if (std::getline(std::cin, input))
        std::cout << solve(input) << std::endl;
    
    return 0;
}
