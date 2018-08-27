/*TRT - Treats for the Cows
#dynamic-programming

FJ has purchased N (1 <= N <= 2000) yummy treats for the cows who get money for giving vast amounts of milk. FJ sells one treat per day and wants to maximize the money he receives over a given period time. The treats are interesting for many reasons:

    The treats are numbered 1..N and stored sequentially in single file in a long box that is open at both ends. On any day, FJ can retrieve one treat from either end of his stash of treats.
    Like fine wines and delicious cheeses, the treats improve with age and command greater prices.
    The treats are not uniform: some are better and have higher intrinsic value. Treat i has value v(i) (1 <= v(i) <= 1000).
    Cows pay more for treats that have aged longer: a cow will pay v(i)*a for a treat of age a.

Given the values v(i) of each of the treats lined up in order of the index i in their box, what is the greatest value FJ can receive for them if he orders their sale optimally?

The first treat is sold on day 1 and has age a=1. Each subsequent day increases the age by 1.
Input

Line 1: A single integer, N

Lines 2..N+1: Line i+1 contains the value of treat v(i)
Output

The maximum revenue FJ can achieve by selling the treats
Example

Input:
5
1
3
1
5
2

Output:
43

*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

// Top Down approach - memoization
int solve_topdown(const std::vector<int>& treats, 
                  int l, 
                  int r,
                  std::vector<std::vector<int>>& memo)
{
    int days = treats.size() - (r - l + 1) + 1;
    
    // Base cases
    if (memo[l][r] != -1) // Result already calculated before, return from memo
    {
        return memo[l][r];
    }
    else if (l == r)
    {
        memo[l][r] = treats[r] * days;
        return memo[l][r];
    }
    else if (r < l) 
    {
        return 0;
    }
    
    // Recursion
    auto rl = days * treats[l] + solve_topdown(treats, l + 1, r, memo);
    auto rr = days * treats[r] + solve_topdown(treats, l, r - 1, memo);
    
    memo[l][r] = std::max(rl, rr);
    return memo[l][r];
}

// Bottom Up approach - tabulation
int solve_bottomup(const std::vector<int>& treats)
{
    auto sz = treats.size();
    
    std::vector<std::vector<int>> dp (sz, std::vector<int>(sz, 0));
    
    // Base cases
    for (std::size_t i=0; i<sz; ++i) 
    {
        dp[i][i] = sz * treats[i];
    }
    
    // Build Table from there
    for (int l = sz - 2; l >= 0; --l)
    {
        for (int r = l + 1; r < sz; ++r)
        {
            int days = sz + l - r;
            
            auto rl = days * treats[l] + dp[l+1][ r ];
            auto rr = days * treats[r] + dp[ l ][r-1];
            
            dp[l][r] = std::max(rl, rr);
        }
    }
    
    return dp[0].back();
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int n;
    std::cin >> n;
    std::vector<int> treats (n);
    std::copy_n(std::istream_iterator<int>(std::cin), n, std::begin(treats));
    
    // std::vector<std::vector<int>> memo (n, std::vector<int>(n, -1));
    // std::cout << solve_topdown(treats, 0, n-1, memo) << std::endl;
    
    std::cout << solve_bottomup(treats) << std::endl;
    
    return 0;
}
