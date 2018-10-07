/*FOODIE - FOODIE
#knapsack #dynamic-programming

Monica loves cooking and Joey is a big foodie. Monica cooks for him but she cooks way too much and fills the entire refrigerator with dishes.

Joey wants to have all the dishes, but his stomach can accomodate a maximum of k units of food. If he starts having a dish of a particular rack , he has to finish all the dishes of the chosen rack (Monica's rules and regulations :P ).

Now you being a Joey fan , are pretty sure he won't be able to make a good choice of racks and come to his rescue! Find the maximum units of food Joey can consume.

 
Input

There are t test cases (1<=t<=10). In each test case the first line specifies n and k , where n is the number of racks and k is as described in the problem statement (1<=n<=100 , 1<=k<=1000) .

Next n lines , first specifies r , the number of dishes in that rack (0<=r<=10) followed by r integers denoting the number of food units that particular dish comprises of. Each dish contains a maximum of 1000 food units.
Output

The maximum number of food units Joey can consume,
Example

Input:
2

3 7

3 1 2 3

1 1

2 2 2

3 10

3 4 2 2

2 4 2

3 1 1 1

Output:
7

9

*/

#include <algorithm>
#include <iostream>
#include <vector>

// Recurrence relation
int solve_recursive(const std::vector<int>& vec, const int pos, const int k)
{
    if (pos == 0 || k == 0)
        return 0;
    else if (vec[pos-1] > k)
        return solve_recursive(vec, pos-1, k);
    else
        return std::max(solve_recursive(vec, pos-1, k), 
                        vec[pos-1] + solve_recursive(vec, pos-1, k - vec[pos-1]));
}

// Dynamic programming bottom-up approach
int solve(const std::vector<int>& vec, const int k)
{
    const int n = vec.size();
    
    std::vector<std::vector<int>> dp (2, std::vector<int>(k+1));
    
    // Fill table according to recurrence relation expressed above
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= k; ++j)
        {
            if (i == 0 || j == 0)
                dp[1][j] = 0;
            else if (vec[i-1] > j)
                dp[1][j] = dp[0][j];
            else
                dp[1][j] = std::max(dp[0][j], vec[i-1] + dp[0][j - vec[i-1]]);
        }
        
        std::iter_swap(&dp[0], &dp[1]);
    }
    
    return dp[0][k];
}

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int n, k;
        std::cin >> n >> k;
        
        std::vector<int> vec (n);
        
        for (int i = 0; i < n; ++i)
        {
            int a, sum = 0;
            std::cin >> a;
            
            while (a--)
            {
                int x;
                std::cin >> x;
                sum += x;
            }
            
            vec[i] = sum;
        }
        
        // std::cout << solve_recursive(vec, n, k) << std::endl;
        std::cout << solve(vec, k) << std::endl;
    }
    
    return 0;
}
