/*OPCPIZZA - Pizzamania
#binary-search

Singham and his friends are fond of pizza. But this time they short of money. So they decided to help each other. They all decided to bring pizza in pairs. Our task is to find the total number of pairs possible which can buy pizza, given the cost of pizza. As pizza boy dont have any cash for change, if the pair adds upto more money than required, than also they are unable to buy the pizza. Each friend is guaranteed to have distinct amount of money. As it is Singham's world, money can also be negative ;).
Input

The first line consist of t (1 <= t <= 100) test cases. In the following 2*t lines, for each test case first there is n and m, where n (1 <= n <= 100000) is number of Singham's friend and m is the price of pizza. The next line consist of n integers, seperated by space, which is the money each friend have. 

The value of m and money is within the limits of int in C, C++.
Output

A single integer representing the number of pairs which can eat pizza.
Example

Sample Input:
2
4 12
9 -3 4 3
5 -9
-7 3 -2 8 7

Sample Output:
1
1

*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int n, price;
        std::cin >> n >> price;
        
        std::vector<int> friends (n);
        std::copy_n(std::istream_iterator<int>(std::cin), n, std::begin(friends));
        std::sort(std::begin(friends), std::end(friends));
        
        int res = 0;
        
        for (auto it = std::begin(friends); it != std::end(friends); std::advance(it, 1))
        {
            if (*it == price - *it) 
                --res;
            
            if (std::binary_search(it, std::end(friends), price - *it))
                ++res;
        }
        
        std::cout << res << std::endl;
    }
    
    return 0;
}

/* 2nd version with 2 pointers
inline int solve(std::vector<int>& friends, int price)
{
    std::sort(std::begin(friends), std::end(friends));
    
    int lo = 0;
    int hi = friends.size() - 1;
    int res = 0;
    
    while (lo < hi)
    {
        int sum = friends[lo] + friends[hi];
        if (sum == price)
        {
            ++res;
            ++lo;
        }
        else if (sum > price)
            --hi;
        else
            ++lo;
    }
    
    return res;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int n, price;
        std::cin >> n >> price;
        
        std::vector<int> friends (n);
        std::copy_n(std::istream_iterator<int>(std::cin), n, std::begin(friends));
        
        std::cout << solve(friends, price) << std::endl;
    }
    
    return 0;
}
*/
