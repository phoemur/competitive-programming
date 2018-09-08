/*DSUBSEQ - Distinct Subsequences
#dynamic-programming

Given a string, count the number of distinct subsequences of it ( including empty subsequence ). For the uninformed, A subsequence of a string is a new string which is formed from the original string by deleting some of the characters without disturbing the relative positions of the remaining characters.
For example, "AGH" is a subsequence of "ABCDEFGH" while "AHG" is not.
Input

First line of input contains an integer T which is equal to the number of test cases. You are required to process all test cases. Each of next T lines contains a string s.
Output

Output consists of T lines. Ith line in the output corresponds to the number of distinct subsequences of ith input string. Since, this number could be very large, you need to output ans%1000000007 where ans is the number of distinct subsequences.
Example

Input:
3
AAA
ABCDEFG
CODECRAFT


Output:
4
128
496

Constraints and Limits

T ≤ 100, length(S) ≤ 100000
All input strings shall contain only uppercase letters. */

#include <iostream>
#include <string>
#include <vector>

int main()
{
    int tests;
    std::cin >> tests;
    long mod = 1000000007;
    
    while (tests--)
    {
        std::string s;
        std::cin >> s;
        
        std::vector<long> sum (26, 0);
        
        sum[s[0]-'A'] = 1;
        long ret = 2;
        
        for(int i = 1; i < s.size(); ++i)
        {
            int index = s[i] - 'A';
            long tmp = (ret - sum[index] + mod) % mod;
            
            ret = (ret + tmp) % mod;
            sum[index] = (sum[index] + tmp) % mod;
        }
        
        std::cout << ret << std::endl;
    }
    
    return 0;
}
