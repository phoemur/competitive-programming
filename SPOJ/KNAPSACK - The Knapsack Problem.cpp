/*KNAPSACK - The Knapsack Problem
no tags 

The famous knapsack problem. You are packing for a vacation on the sea side and you are going to carry only one bag with capacity S (1 <= S <= 2000). You also have N (1<= N <= 2000) items that you might want to take with you to the sea side. Unfortunately you can not fit all of them in the knapsack so you will have to choose. For each item you are given its size and its value. You want to maximize the total value of all the items you are going to bring. What is this maximum total value?
Input

On the first line you are given S and N. N lines follow with two integers on each line describing one of your items. The first number is the size of the item and the next is the value of the item.
Output

You should output a single integer on one like - the total maximum value from the best choice of items for your trip.
Example

Input:
4 5
1 8
2 4
3 0
2 5
2 3


Output:
13

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

// Dynamic programming Bottom-up approach
int solve(const std::vector<Item>& vec, 
          const int item_num, 
          const int max_size)
{
    const int sz = vec.size();
    
    std::vector<std::vector<int>> dp (sz+1, std::vector<int>(max_size+1));
    
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
    int s, n;
    std::cin >> s >> n;
    
    std::vector<Item> vec;
    vec.reserve(n);
    
    while (n--)
    {
        int sz, vl;
        std::cin >> sz >> vl;
        vec.push_back({sz, vl});
    }
    
    //std::cout << solve_recursive(vec, vec.size(), s) << std::endl;
    std::cout << solve(vec, vec.size(), s) << std::endl;
    
    return 0;
}
