/*TWENDS - Two Ends
#dynamic-programming

In the two-player game “Two Ends”, an even number of cards is laid out in a row. On each card, face up, is written a positive integer. Players take turns removing a card from either end of the row and placing the card in their pile. The player whose cards add up to the highest number wins the game. Now one strategy is to simply pick the card at the end that is the largest — we’ll call this the greedy strategy. However, this is not always optimal, as the following example shows: (The first player would win if she would first pick the 3 instead of the 4.)

3 2 10 4

You are to determine exactly how bad the greedy strategy is for different games when the second player uses it but the first player is free to use any strategy she wishes.
Input

There will be multiple test cases. Each test case will be contained on one line. Each line will start with an even integer n followed by n positive integers. A value of n = 0 indicates end of input. You may assume that n is no more than 1000. Furthermore, you may assume that the sum of the numbers in the list does not exceed 1,000,000.
Output

For each test case you should print one line of output of the form:

In game m, the greedy strategy might lose by as many as p points.

where m is the number of the game (starting at game 1) and p is the maximum possible difference between the first player’s score and second player’s score when the second player uses the greedy strategy. When employing the greedy strategy, always take the larger end. If there is a tie, remove the left end.
Example

Input:
4 3 2 10 4
8 1 2 3 4 5 6 7 8
8 2 2 1 5 3 8 7 3
0

Output:
In game 1, the greedy strategy might lose by as many as 7 points.
In game 2, the greedy strategy might lose by as many as 4 points.
In game 3, the greedy strategy might lose by as many as 5 points.

*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

// Top Down approach - memoization
int solve_topdown(const std::vector<int>& deck, 
                  int l, 
                  int r, 
                  std::vector<std::vector<int>>& memo)
{
    if (r < l) // Overall base case
    {
        return 0;
    }
    else if (memo[l][r] > std::numeric_limits<int>::min()) // Result already calculated, return from memo
    {
        return memo[l][r];
    }
    else if (l == r) // Greedy turn base case (minimizer)
    {
        memo[l][r] = deck[l] * -1;
        return memo[l][r];
    }
    else if ((r - l) % 2 == 1) // My turn (maximizer turn)
    {
        memo[l][r] = std::max(deck[l] + solve_topdown(deck, l+1, r, memo), 
                              deck[r] + solve_topdown(deck, l, r-1, memo));
        
        return memo[l][r];
    }
    else // Greedy turn (minimizer turn)
    {
        if (deck[l] >= deck[r])
            memo[l][r] = solve_topdown(deck, l+1, r, memo) - deck[l];
        else
            memo[l][r] = solve_topdown(deck, l, r-1, memo) - deck[r];
        
        return memo[l][r];
    }
}

// Bottom Up approach - tabulation
int solve_bottomup(const std::vector<int>& deck)
{
    auto n = deck.size();
    
    std::vector<std::vector<int>> dp (n, std::vector<int>(n, 0));
    
    // Base case
    for (int i = 0; i < n; ++i)
    {
        dp[i][i] = -1 * deck[i];
    }
    
    // Build from there
    for (int i = n-2; i >= 0; --i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if ((j - i) % 2 == 1) // My turn (maximizer turn)
            {
                dp[i][j] = std::max(deck[i] + dp[i+1][ j ],
                                    deck[j] + dp[ i ][j-1]);
            }
            else // Greedy turn (minimizer turn)
            {
                if (deck[i] >= deck[j])
                    dp[i][j] = dp[i+1][j] - deck[i];
                else
                    dp[i][j] = dp[i][j-1] - deck[j];
            }
        }
    }
    
    return dp[0].back();
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int n;
    int test = 1;
    std::vector<int> deck {};
    
    for (std::cin >> n; n != 0; std::cin >> n, ++test)
    {
        deck.resize(n);
        std::copy_n(std::istream_iterator<int>(std::cin), n, std::begin(deck));
        
        //std::vector<std::vector<int>> memo (n, std::vector<int>(n, std::numeric_limits<int>::min()));
        
        std::cout << "In game " 
                  << test
                  << ", the greedy strategy might lose by as many as " 
                  //<< solve_topdown(deck, 0, n-1, memo)
                  << solve_bottomup(deck)
                  << " points.\n";
    }

    return 0;
}
