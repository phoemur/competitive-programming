/*BEHAPPY - Be Awesome As Barney Stinson
#dynamic-programming

Barney Stinson ;) is way too flirty. He has many girlfriends and he wants to keep all of them happy. He has M girlfriends. He bought N gifts for them. Now he knows that some girlfriends need more gifts and some need less. So he decided that he will give atleast Ai gifts and at most Bi gifts to his ith girlfriend. He has to give away all the N gifts. Tell us in how many different ways he can do this.
INPUT

For each test case, first line contains two integers M and N, then follows M lines each having two integers Ai and Bi (1 <= i <= M). Input ends with M and N both equal to 0 and that case should not be processed.
OUTPUT:

For each test case, output the number of different ways in which he can distribute those gifts in a single line.
Constraints

1 <= M <= 20, 1 <= N <= 100, 0 <= Ai, Bi <=100
Example

Input:

3 5
0 1
1 3
1 4
0 0

Output:

6

Explanation

He can distribute 5 gifts in his 3 girlfriends in 6 different ways as follows (0 1 4), (0 2 3), (0 3 2), (1 1 3), (1 2 2), (1 3 1).
*/

#include <iostream>
#include <utility>
#include <vector>

// Recurrence relation
int solve_recursive(const std::vector<std::pair<int,int>>& minmax_pres, int pos, int presents)
{
    if (pos == 0)
    {
        if (presents == 0) return 1;
        else return 0;
    }
    else
    {
        int res = 0;
        for (int i = minmax_pres[pos-1].first; i <= minmax_pres[pos-1].second; ++i)
            if (i <= presents)
                res += solve_recursive(minmax_pres, pos-1, presents-i);
        
        return res;
    }
}

// Dynamic programming, bottom-up approach
long solve(const std::vector<std::pair<int,int>>& minmax_pres, int presents)
{
    const int sz = minmax_pres.size();
    
    std::vector<std::vector<long>> dp (sz + 1, std::vector<long>(presents + 1, 0));
    
    // Fill table according to recurrence relation expressed above
    dp[0][0] = 1; // base case
    for (int i = 1; i <= sz; ++i)
    {
        for (int j = 0; j <= presents; ++j)
        {
            long res = 0;
            for (int k = minmax_pres[i-1].first; k <= minmax_pres[i-1].second; ++k)
                if (k <= j)
                    res += dp[i-1][j-k];
                    
            dp[i][j] = res;
        }
    }
    
    return dp[sz][presents];
}

int main()
{
    int m, n;
    
    while (std::cin >> m >> n && (m != 0 || n != 0))
    {
        std::vector<std::pair<int,int>> minmax_pres (m + 1);
        
        for (int i = 1; i <= m; ++i)
            std::cin >> minmax_pres[i].first >> minmax_pres[i].second;
        
        //std::cout << solve_recursive(minmax_pres, m + 1, n) << std::endl;
        std::cout << solve(minmax_pres, n) << std::endl;
    }
    
    return 0;
}
