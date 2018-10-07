/*LKS - Large Knapsack
#knapsack #dynamic-programming

The knapsack problem or rucksack problem is a problem in combinatorial optimization: Given a set of items, each with a weight and a value, determine the number of each item to include in a collection so that the total weight is less than or equal to a given limit and the total value is as large as possible. It derives its name from the problem faced by someone who is constrained by a fixed-size knapsack and must fill it with the most valuable items.

Just implement 0/1 Knapsack.
Input

First line contains two integers K and N, where K in the maximum knapsack size and N is the number of items. N lines follow where ith line describes ith item in the form vi and wi where vi is the value and wi is the weight of ith item.
Output

Output a single number - maximum value of knapsack. (All operations and the answer are guaranteed to fit in signed 32-bit integer.)

Time limit changed to 2s on 02.07.11.
Example

Input:
10 3
7 3
8 8
4 6

Output:
11

Constraints

K <= 2000000
N <= 500
Vi <= 10^7
Wi <= 10^7
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

struct Item {
    int value;
    int weight;
};

// Recurrence relation
int solve_recursive(const std::vector<Item>& vec, 
                    const int pos, 
                    const int maxweight)
{
    if (pos == 0 || maxweight == 0)
        return 0;
    else if (vec[pos-1].weight > maxweight)
        return solve_recursive(vec, pos-1, maxweight);
    else
        return std::max(solve_recursive(vec, pos-1, maxweight), 
                        vec[pos-1].value + solve_recursive(vec, pos-1, maxweight - vec[pos-1].weight));
}

// Dynamic programming bottom-up approach
int solve_bottomup(const std::vector<Item>& vec, const int maxweight)
{
    const int n = vec.size();
    std::vector<std::vector<int>> dp (2, std::vector<int>(maxweight+1));
    
    // Fill table according to recurrence relation expressed above
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= maxweight; ++j)
        {
            if (i == 0 || j == 0)
                dp[1][j] = 0;
            else if (vec[i-1].weight > j)
                dp[1][j] = dp[0][j];
            else
                dp[1][j] = std::max(dp[0][j], vec[i-1].value + dp[0][j - vec[i-1].weight]);
        }
        
        std::iter_swap(&dp[0], &dp[1]);
    }
    
    return dp[0][maxweight];
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int k, n;
    std::cin >> k >> n;
    
    std::vector<Item> vec;
    vec.reserve(n);
    
    while (n--)
    {
        int a, b;
        std::cin >> a >> b;
        vec.push_back({a, b});
    }
    
    //std::cout << solve_recursive(vec, vec.size(), k) << std::endl;
    std::cout << solve_bottomup(vec, k) << std::endl;
    
    return 0;
}
