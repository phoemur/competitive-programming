/*ABA12C - Buying Apples!
#dynamic-programming

Harish went to a supermarket to buy exactly ‘k’ kilograms apples for his ‘n’ friends. The supermarket was really weird. The pricing of items was very different. He went to the Apples section and enquired about the prices. The salesman gave him a card in which he found that the prices of apples were not per kg. The apples were packed into covers, each containing ‘x’ kg of apples, x > 0 and ‘x’ is an integer. An ‘x’ kg packet would be valued at ‘y’ rupees. So, the placard contained a table with an entry ‘y’ denoting the price of an ‘x’ kg packet. If ‘y’ is -1 it means that the corresponding packet is not available. Now as apples are available only in packets, he decides to buy atmost ‘n’ packets for his ‘n’ friends i.e he will not buy more than n packets of apples.

Harish likes his friends a lot and so he does not want to disappoint his friends. So now, he will tell you how many friends he has and you have to tell him the minimum amount of money he has to spend for his friends.
Input

The first line of input will contain the number of test cases, C.

Each test case will contain two lines.

The first line containing N and K, the number of friends he has and the amount of Apples in kilograms which he should buy.

The second line contains K space separated integers in which the ith integer specifies the price of a ‘i’kg apple packet. A value of -1 denotes that the corresponding packet is unavailable.

    0 < N <= 100
    0 < K <= 100
    0 < price <= 1000

Output

The output for each test case should be a single line containing the minimum amount of money he has to spend for his friends. Print -1 if it is not possible for him to satisfy his friends.
Sample I/O

Input:
2
3 5
-1 -1 4 5 -1
5 5
1 2 3 4 5

Output:
-1
5

Explanation of test cases:

1) As there are only 3 and 4kg packets in the shop, he will not be able to satisfy his friends as he would not be able to buy exactly 5kg of apples.

2) He can buy five 1kg packet as he has to buy 5 kg. So the min money he should spend is 5.
*/


#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

long solve_recursive(int n, int index, const std::vector<int>& prices)
{
    if (n == 0) return 0;
    else if (n < 0 || index < 0) return std::numeric_limits<int>::max();
    else
    {
        if (prices[index] >= 0)
            return std::min(prices[index] + solve_recursive(n - index - 1, index, prices), 
                            solve_recursive(n, index-1, prices));
        else
            return solve_recursive(n, index-1, prices);
    }
        
}

int solve(int amount, const std::vector<int>& prices)
{
    std::vector<std::vector<long>> dp (amount+1, std::vector<long>(prices.size(), 0));

    
    for (int n = 1; n <= amount; ++n)
    {
        for (int index = 0; index < prices.size(); ++index)
        {
            dp[n][index] = index > 0 ? dp[n][index-1] : 
                                       std::numeric_limits<int>::max();
            
            if (prices[index] >= 0)
            {
                long sub_res = n - index - 1 >= 0 ? prices[index] + dp[n-index-1][index] : 
                                                    std::numeric_limits<int>::max();
                                                    
                dp[n][index] = std::min(dp[n][index], sub_res);
            }
                
        }
    }
    
    return dp[amount][prices.size()-1];
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int c;
    std::cin >> c;
    
    while (c--)
    {
        int n, k;
        std::cin >> n >> k;
        
        std::vector<int> prices (k, 0);
        std::copy_n(std::istream_iterator<int>(std::cin), k, std::begin(prices));
        
        long res = solve(k, prices);
        std::cout <<  (res == std::numeric_limits<int>::max() ? -1 : res) << std::endl;
    }
    
    return 0;
}
