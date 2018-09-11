/*UOFTAE - Foxling Feeding Frenzy
#dynamic-programming

You've come across $N$ ($1 \leq N \leq 200$) adorable little Foxlings, and they're hungry! Luckily, you happen to have $M$ ($1 \leq M \leq 200$) crackers on hand, and everyone knows that Foxen love crackers! You'd like to distribute all of your crackers, without splitting any of them, among the Foxlings - but you have to be careful. Foxling $i$ must be fed at least $A_i$ crackers, or it will remain hungry, but no more than $B_i$ of them, or it will become hyper ($1 \leq A_i \leq B_i \leq 200$). You certainly don't want any hungry or hyper Foxlings on your hands, and you're curious as to how many ways this can be accomplished.

There are $T$ ($1 \leq T \leq 100$) scenarios as described above. For each one, you'd like to determine the number of different distributions of your crackers that would satisfy all of the Foxlings, modulo $10^9+7$ (as this value can be quite large).
Input

First line: 1 integer, $T$

For each scenario:

First line: 2 integers, $N$ and $M$

Next $N$ lines: 2 integers, $A_i$ and $B_i$, for $i = 1..N$
Output

For each scenario:

Line 1: 1 integer, the number of valid cracker distributions modulo $10^9+7$
Example

Input:

2
2 5
1 4
2 6
3 5
2 2
2 9
2 3

Output:

3
0

Explanation of Sample:

In the first scenario, you can give either 1, 2, or 3 crackers to the first Foxling, and the remaining 4, 3, or 2 (respectively) to the second.

In the second scenario, each Foxling must receive at least 2 crackers, while you only have 5 to give out, so you have no valid options.
*/

#include <iostream>
#include <utility>
#include <vector>

// Recurrence relation
int solve_recursive(const std::vector<std::pair<int,int>>& minmax, int pos, int crackers)
{
    if (pos == 0)
    {
        if (crackers == 0) return 1;
        else return 0;
    }
    else
    {
        int res = 0;
        for (int i = minmax[pos-1].first; i <= minmax[pos-1].second; ++i)
            if (i <= crackers)
                res += solve_recursive(minmax, pos-1, crackers - i);
        
        return res;
    }
}

// Dynamic programming, bottom-up approach
long solve(const std::vector<std::pair<int,int>>& minmax, int crackers)
{
    const int sz = minmax.size();
    const int mod = 1000000007;
    
    std::vector<std::vector<long>> dp (sz + 1, std::vector<long>(crackers + 1, 0));
    
    // Fill table according to recurrence relation expressed above
    dp[0][0] = 1; // base case
    for (int i = 1; i <= sz; ++i)
    {
        for (int j = 0; j <= crackers; ++j)
        {
            long res = 0;
            for (int k = minmax[i-1].first; k <= minmax[i-1].second; ++k)
                if (k <= j)
                    res += dp[i-1][j-k] % mod;
                    
            dp[i][j] = res % mod;
        }
    }
    
    return dp[sz][crackers];
}

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int n, m;
        std::cin >> n >> m;
        
        std::vector<std::pair<int,int>> minmax (n + 1);
        
        for (int i = 1; i <= n; ++i)
            std::cin >> minmax[i].first >> minmax[i].second;
        
        if (m <= 0)
            std::cout << 0 << std::endl;
        else
            std::cout << solve(minmax, m) << std::endl;
            //std::cout << solve_recursive(minmax, n + 1, m) << std::endl;
    }
    
    return 0;
}
