/*WACHOVIA - Wachovia Bank
#knapsack #dynamic-programming

Danilo Gheyi is a renowned bank robber. He is known worldwide for accomplishing the most profitable bank robbery, in Fortaleza, Ceará. Danilo and his friends dug a tunnel to get into the main chest. There were some bags, with different amounts of money or jewelry and weight. They had to leave about 50% of the total value, since the truck couldn't carry all the bags.

Danilo wasn't caught, and to show that he can do itall again, he is planning a robbery to one of the safer banks in USA -the Wachovia Bank. He wants your help to maximize the amount stolen, avoiding a huge loss as it happened in Fortaleza.

Write a program that, given the maximum weight the truck is ableto carry and the information about each bag in the bank, determine the maximum value that Danilo can steal.
Input

The input consists of several instances. There is an integer N (1 ≤ N ≤ 200) in the first line; it stands for the number of instances. The first line of each instance contains two integers, K and M (8 ≤ K ≤ 1000 and 1 ≤ M ≤ 50) representing, respectively, the maximum weight the truck can handle and the amount of bags in the bank. The next M lines describe each bag with two integers A and B (8 ≤ A ≤ 200 and 1 ≤ B ≤ 25): the weight and the value of the bag, respectively.
Output

For each instance output a sentence “Hey stupid robber, you can get P.”, and P represents the maximum value Danilo can steal.
Example

Input:
3
34 5
178 12
30 1
13 7
34 8
87 6
900 1
900 25
100 10
27 16
131 9
132 17
6 5
6 23
56 21
100 25
1 25
25 25
100 2

Output:
Hey stupid robber, you can get 8.
Hey stupid robber, you can get 25.
Hey stupid robber, you can get 99.

*/

#include <algorithm>
#include <iostream>
#include <vector>

struct Item {
    int size;
    int value;
};

// Recurrence relation
int solve_recursive(const std::vector<Item>& vec, 
                    const int item_num, 
                    const int max_size)
{
    // Base cases
    if (item_num == 0 || max_size == 0) return 0;
    
    // If size of the last item is more than Knapsack capacity, then
    // this item cannot be included in the optimal solution
    else if (vec[item_num-1].size > max_size)
        return solve_recursive(vec, item_num - 1, max_size);
    
    else // Return the maximum of two cases: (1) nth item included (2) not included
        return std::max(vec[item_num-1].value + solve_recursive(vec, item_num - 1, max_size - vec[item_num-1].size), 
                        solve_recursive(vec, item_num - 1, max_size));
}

inline int solve(const std::vector<Item>& vec, const int max_size)
{
    const int sz = vec.size();
    
    std::vector<std::vector<int>> dp (sz + 1, std::vector<int>(max_size + 1));
    
    for (int i = 0; i <= sz; ++i)
    {
        for (int j = 0; j <= max_size; ++j)
        {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (vec[i-1].size > j)
                dp[i][j] = dp[i-1][j];
            else
                dp[i][j] = std::max(vec[i-1].value + dp[i-1][j - vec[i-1].size], dp[i-1][j]);
        }
    }
    
    return dp[sz][max_size];
}


int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int k, m;
        std::cin >> k >> m;
        
        std::vector<Item> vec;
        vec.reserve(m);
        
        while (m--)
        {
            int w, v;
            std::cin >> w >> v;
            vec.push_back({w, v});
        }
        
        // std::cout << "Hey stupid robber, you can get " << solve_recursive(vec, vec.size(), k) << ".\n";
        std::cout << "Hey stupid robber, you can get " << solve(vec, k) << ".\n";
    }
    
    return 0;
}
