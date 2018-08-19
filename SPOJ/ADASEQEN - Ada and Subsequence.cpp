/*ADASEQEN - Ada and Subsequence
#dynamic-programming

Ada the Ladybug has two string which she wants to give to her friends. As she doesn't want to distinguish between them, she wants to use only some common subsequence. Firstly she wanted to simply use the longest common subsequence but then she realized it wouldn't be kosher.

She assigned a positive value to each letter. Now she wants to find the most expensive subsequence.
Input

The first line of each test-case will contain two integers 1 ≤ N, M ≤ 2000, the length of each subsequence.

The next line will contain 26 integers (1 ≤ Pi ≤ 105), the price of each letter.

The next line will contain string of length N consisting of lowercase english alphabet.

The next line will contain string of length M consisting of lowercase english alphabet.
Output

For each test-case, print the cost of the most expensive common subsequence.
Example Input

4 4
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
abcd
dbca

Example Output

2

Example Input

3 3
1 7 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
baa
aab

Example Output

7

Example Input

4 5
1 4 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 6
zbbz
bbzbb

Example Output

14

Example Input

3 3
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
abc
def

Example Output

0

*/

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>


int solve_recursive(const std::string& first, 
                    const std::string& second, 
                    int index_f, 
                    int index_s, 
                    std::map<char,int>& cost)
{
    if (index_f == 0 || index_s == 0) 
        return 0;
    else if (first[index_f-1] == second[index_s-1])
        return cost[first[index_f-1]] + solve_recursive(first, second, index_f-1, index_s-1, cost);
    else
        return std::max(solve_recursive(first, second, index_f,   index_s-1, cost), 
                        solve_recursive(first, second, index_f-1, index_s,   cost));
}

int solve_bottom_up(const std::string& first, 
                    const std::string& second, 
                    std::map<char,int>& cost)
{
    int fst_sz = first.size();
    int snd_sz = second.size();
    
    std::vector<std::vector<int>> dp (fst_sz+1, std::vector<int>(snd_sz+1));
    
    for (int i=0; i<=fst_sz; ++i) {
        for (int j=0; j<=snd_sz; ++j) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            
            else if (first[i-1] == second[j-1])
                dp[i][j] = cost[first[i-1]] + dp[i-1][j-1];
            
            else
                dp[i][j] = std::max(dp[i][j-1], dp[i-1][j]);
        }
    }
    
        
    return dp[fst_sz][snd_sz];
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int n, m;    
    std::cin >> n >> m;
    
    std::map<char,int> cost;
    for (char s = 26, c = 'a'; s--; c++) {std::cin >> cost[c];}
    
    std::string first, second;
    std::cin >> first >> second;
    
    //std::cout << solve_recursive(first, second, n, m, cost) << std::endl;
    std::cout << solve_bottom_up(first, second, cost) << std::endl;
    
    return 0;
}
