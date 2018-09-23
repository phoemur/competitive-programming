/*ADVEDIST - Advanced Edit Distance
no tags 

The edit distance of two strings S and T is the minimum number of edit operations that need to be done to transform S into T . The valid edit operations are:
• Insert a single character at any position.
• Modify an existing character.
• Remove an existing character.
For example, the edit distance of “pantera” and “aorta” is 5, because the following chain of
edits is valid (and there is no shorter chain):
“pantera” >>> “antera” >>> “aotera” >>> “aoera” >>> “aora” >>> “aorta”.

We define the advanced edit distance in a similar way, but adding the swap of two adjacent characters as an extra valid operation. With this setting, the advanced edit distance of “pantera” and “aorta” is 4:
“pantera” >>> “antera” >>> “antra” >>> “aotra” >>> “aorta”.


You need to write a program that calculates the advanced edit distance of two given words.
Input

The input contains several test cases. Each test case is described in a single line that contains
two non-empty words, each of them of at most 1000 lowercase letters, separated by a single
space. The last line of the input contains two asterisks separated by a single space and should
not be processed as a test case.
Output

For each test case output a single line with an integer representing the advanced edit distance
of the two input words.
Example

Input:

pantera aorta
zero zero
* *

Output:

4
0

*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Minimum variadic template functions
template<typename T>
T minimum(T t1, T t2)
{
    return std::min(t1, t2);
}

template<typename T, typename... Args>
T minimum(T t1, T t2, Args... args)
{
    return minimum(minimum(t1, t2), args...);
}

// Dynamic programming bottom-up approach
// https://en.wikipedia.org/wiki/Damerau%E2%80%93Levenshtein_distance
int solve(const std::string& str1, const std::string& str2)
{
    const int sz1 = str1.size(), sz2 = str2.size();
    const int INF = sz1 + sz2 + 2;
    
    std::vector<std::vector<int>> dp (sz1+2, std::vector<int>(sz2+2));
    std::vector<int> da (256);
    
    // Fill table
    dp[0][0] = INF;
    
    for(int i = 0; i <= sz1; ++i)
    {
        dp[i+1][1] = i;
        dp[i+1][0] = INF;
    }
    
    
    for(int j = 0; j <= sz2; ++j)
    {
        dp[1][j+1] = j;
        dp[0][j+1] = INF;
    }
    
    for(int i = 1; i <= sz1; ++i)
    {
        int db = 0;
                       
        for(int j = 1; j <= sz2; ++j)
        {
            int i1 = da[str2[j-1]];
                               
            int j1 = db;
                               
            int d = (str1[i-1] == str2[j-1]) ? 0 : 1;
                               
            if(d == 0)
                db = j;
                               
            dp[i+1][j+1] = minimum(dp[i][j]+d, 
                                   dp[i+1][j]+1, 
                                   dp[i][j+1]+1, 
                                   dp[i1][j1]+(i-i1-1)+1+(j-j1-1));
        }
                       
        da[str1[i-1]] = i;
    }
    
    return dp[sz1+1][sz2+1];
}

int main()
{
    for (std::string a, b; std::cin >> a >> b && (a != "*" || a != "*");)
    {
        std::cout << solve(a, b) << std::endl;
    }
    
    return 0;
}
