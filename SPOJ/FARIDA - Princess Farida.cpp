/*FARIDA - Princess Farida
#dynamic-programming

Once upon time there was a cute princess called Farida living in a castle with her father, mother and uncle. On the way to the castle there lived many monsters. Each one of them had some gold coins. Although they are monsters they will not hurt. Instead they will give you the gold coins, but if and only if you didn't take any coins from the monster directly before the current one. To marry princess Farida you have to pass all the monsters and collect as many coins as possible. Given the number of gold coins each monster has, calculate the maximum number of coins you can collect on your way to the castle.
Input

The first line of input contains the number of test cases. Each test case starts with a number N, the number of monsters, 0 <= N <= 10^4. The next line will have N numbers, number of coins each monster has, 0 <= The number of coins with each monster <= 10^9. Monsters described in the order they are encountered on the way to the castle.
Output

For each test case print “Case C: X” without quotes. C is the case number, starting with 1. X is the maximum number of coins you can collect.
Example

Input:
2
5
1 2 3 4 5
1
10

Output:
Case 1: 9
Case 2: 10

*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

// Recurrence relation
long solve_recursive(const std::vector<long>& monsters, int index)
{
    if (index < 0) return 0;
    else if (index == 0) return monsters[0];
    else if (index == 1) return std::max(monsters[0], monsters[1]);
    else return std::max(monsters[index] + solve_recursive(monsters, index - 2), 
                                           solve_recursive(monsters, index - 1));
}

// Dynamic programming bottom-up approach
inline long solve_bottomup(const std::vector<long>& monsters)
{
    const int sz = monsters.size();
    if (sz == 0) return 0;
    else if (sz == 1) return monsters[0];
    
    std::vector<long> dp (sz);
    
    // Base cases
    dp[0] = monsters[0];
    dp[1] = std::max(monsters[0], monsters[1]);
    
    // Fill table
    for (int i = 2; i < sz; ++i)
    {
        dp[i] = std::max(monsters[i] + dp[i-2], dp[i-1]);
    }
    
    return dp[sz-1];
}

// Dynamic programming bottom-up approach optimized for O(1) memory
inline long solve(const std::vector<long>& monsters)
{
    long m1 = 0, m2 = 0;
    
    for (auto& amount: monsters)
    {
        long take = amount + m1;
        m1 = m2;
        m2 = std::max(m1, take);
    }
    
    return m2;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int tests;
    std::cin >> tests;
    
    for (int state = 1; state <= tests; ++state)
    {
        long n;
        std::cin >> n;
        
        if (n <= 0)
        {
            std::cout << "Case " << state << ": 0" << std::endl;
        }
        else
        {
            std::vector<long> monsters (n);
            std::copy_n(std::istream_iterator<long>(std::cin), n, std::begin(monsters));
        
            // std::cout << "Case " << state << ": " << solve_recursive(monsters, n - 1) << std::endl;
            // std::cout << "Case " << state << ": " << solve_bottomup(monsters) << std::endl;
            std::cout << "Case " << state << ": " << solve(monsters) << std::endl;
        }
    }
    
    return 0;
}
