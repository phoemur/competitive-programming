/*LARSUBP - Large subsequence Problem
#tree #binary-search

Given a string S which contains only digit-characters. How many subsequences can be obtained from S such that every digit is strictly greater than all previous digits in that subsequence.
As for example if S=7598 then there are 8 subsequences which follow the above constraint. These are 7,5,9,8,79,78,59,58. Notice that 7598 is not a required subsequence because 7>5 and 9>8.

Note: A subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements.
Input

Input starts with an integer T (≤ 1000), denoting the number of test cases. Each case contains a string S. The length of S does not exceed 10000. S does not contain any leading zeros.
Output

For each case, print the a string(without quotes) "Case i: " follwed by number of subsequences where "i" is test case number. Answer may be very large, so output it modulo 10^9+7.
Example

Input:

2
4
7598

Output:
Case 1: 1
Case 2: 8

For small constraints: www.spoj.com/problems/SUBP/

*/

#include <iostream>
#include <string>
#include <vector>

#define MOD 1000000007

long solve(const std::string& s)
{
    const int n = s.size();
    
    std::vector<int> dp (10);
    
    for (int i = 0; i < n; ++i)
    {
        long tmp = s[i] - '0';
        
        for (int j = 0; j < tmp; ++j)
        {
            dp[tmp] = (dp[tmp] + dp[j]) % MOD;
        }
        
        ++dp[tmp];
    }
    
    long res = 0;
    for (auto& n: dp)
        res = (res + n) % MOD;
    
    return res;
}

int main()
{
    int tests;
    std::cin >> tests;
    
    for (int cas = 1; cas <= tests; ++cas)
    {
        std::string input;
        std::cin >> input;
    
        int res = solve(input) % MOD;
        
        std::cout << "Case " << cas << ": " << res << std::endl;
    }
    
    
    
    return 0;
}
