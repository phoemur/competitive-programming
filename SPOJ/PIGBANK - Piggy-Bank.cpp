/*PIGBANK - Piggy-Bank
#dynamic-programming

Before ACM can do anything, a budget must be prepared and the necessary financial support obtained. The main income for this action comes from Irreversibly Bound Money (IBM). The idea behind is simple. Whenever some ACM member has any small money, he takes all the coins and throws them into a piggy-bank. You know that this process is irreversible, the coins cannot be removed without breaking the pig. After a sufficiently long time, there should be enough cash in the piggy-bank to pay everything that needs to be paid.

But there is a big problem with piggy-banks. It is not possible to determine how much money is inside. So we might break the pig into pieces only to find out that there is not enough money. Clearly, we want to avoid this unpleasant situation. The only possibility is to weigh the piggy-bank and try to guess how many coins are inside. Assume that we are able to determine the weight of the pig exactly and that we know the weights of all coins of a given currency. Then there is some minimum amount of money in the piggy-bank that we can guarantee. Your task is to find out this worst case and determine the minimum amount of cash inside the piggy-bank. We need your help. No more prematurely broken pigs!
Input

The input consists of T test cases. The number of them (T) is given on the first line of the input file. Each test case begins with a line containing two integers E and F. They indicate the weight of an empty pig and of the pig filled with coins. Both weights are given in grams. No pig will weigh more than 10 kg, that means 1 <= E <= F <= 10000. On the second line of each test case, there is an integer number N (1 <= N <= 500) that gives the number of various coins used in the given currency. Following this are exactly N lines, each specifying one coin type. These lines contain two integers each, Pand W (1 <= P <= 50000, 1 <= W <=10000). P is the value of the coin in monetary units, W is it's weight in grams.
Output

Print exactly one line of output for each test case. The line must contain the sentence "The minimum amount of money in the piggy-bank is X." where X is the minimum amount of money that can be achieved using coins with the given total weight. If the weight cannot be reached exactly, print a line "This is impossible.".
Example

Sample Input:

3
10 110
2
1 1
30 50
10 110
2
1 1
50 30
1 6
2
10 3
20 4

Sample output:

The minimum amount of money in the piggy-bank is 60.
The minimum amount of money in the piggy-bank is 100.
This is impossible.

*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

struct Coin {
    int value;
    int weight;
};

constexpr static int INF = std::numeric_limits<int>::max() / 1000;

// Recurrence Relation
int solve_recursive(const std::vector<Coin>& vec, int pos, int curr_weight, int empty)
{
    if (curr_weight == empty) // Base
        return 0;
    else if (curr_weight < empty) // Impossible 
        return INF;
    else if (pos == 0) // Impossible 
        return INF;
    else
        return std::min(vec[pos-1].value + solve_recursive(vec, pos, curr_weight - vec[pos-1].weight, empty), // Use this type of coin
                        solve_recursive(vec, pos-1, curr_weight, empty)); // Don't use it
}

int solve_bottomup(const std::vector<Coin>& vec, int weight, int empty)
{
    const int n = vec.size();
    
    std::vector<std::vector<int>> dp (2, std::vector<int>(weight+1, INF));
    
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= weight; ++j)
        {
            if (j == empty)
                dp[1][j] = 0;
            else if (j < empty)
                dp[1][j] = INF;
            else if (i == 0)
                dp[1][j] = INF;
            else
            {
                int index = j - vec[i-1].weight < 0 ? 0: j - vec[i-1].weight;
                
                dp[1][j] = std::min(vec[i-1].value + dp[1][index], dp[0][j]);
            }
        }
        
        std::iter_swap(&dp[0], &dp[1]);
    }
    
    return dp[0][weight];
}

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int empty, full;
        std::cin >> empty >> full;
        
        int n;
        std::cin >> n;
        
        std::vector<Coin> vec;
        vec.reserve(n);
        
        for (int i = 0; i < n; ++i)
        {
            int v, w;
            std::cin >> v >> w;
            vec.push_back({v, w});
        }
        
        //int res = solve_recursive(vec, n, full, empty);
        int res = solve_bottomup(vec, full, empty);
        
        if (res != INF)
            std::cout << "The minimum amount of money in the piggy-bank is " << res << ".\n";
        else
            std::cout << "This is impossible.\n";
    }
    
    return 0;
}
