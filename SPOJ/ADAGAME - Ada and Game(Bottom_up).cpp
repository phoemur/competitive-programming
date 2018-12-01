/*ADAGAME - Ada and Game
#dynamic-programming

Ada the Ladybug is playing Game of Digits against her friend Velvet Mite Vinit. The game is played in following manner: At first, there is a four-digit number and a number of moves. Both Ada and Vinit take turns alternately (beginning with Ada). Both of them must increase ANY digit of the number, but if the digit was 9 it will become 0.

For example number 3590 can be expanded to: 4590,3690,3500 or 3591. If after all turns the number is greater than the original number, Ada wins - otherwise Vinit is the winner. Both of them play optimaly - can you decide who is the winner?

PS: It is possible, that Ada will have one more turn (if number of turns is odd)
Input

First line of input will consist T ≤ 200 number of test-cases. Each testcase will consist of four digit number 0 ≤ N < 104 [the original number] and 0 ≤ M ≤ 100 [the number of turns].
Output

For each test-case, print the name of winner ("Ada" or "Vinit").
Example Input

5
0000 0
5566 3
3333 10
9999 9
1234 30

Example Output

Vinit
Ada
Ada
Vinit
Ada

*/

#include <algorithm>
#include <cstdio>

int main()
{
    // 3D dynamic programming table
    short int dp[10000][101][2];
    
    for (int i = 0; i < 10000; ++i)
        dp[i][0][0] = dp[i][0][1] = i; // Base cases (moves == 0)

    for (int moves = 1; moves < 101; ++moves)
    {
        for (int num = 0; num < 10000; ++num)
        {
            int q3 = num          % 10 == 9 ? num - 9    : num + 1;    // digit[3]
            int q2 = (num / 10)   % 10 == 9 ? num - 90   : num + 10;   // digit[2]
            int q1 = (num / 100)  % 10 == 9 ? num - 900  : num + 100;  // digit[1]
            int q0 = (num / 1000) % 10 == 9 ? num - 9000 : num + 1000; // digit[0]
            
            dp[num][moves][1] = std::max(std::max(dp[q0][moves-1][0], dp[q1][moves-1][0]), 
                                         std::max(dp[q2][moves-1][0], dp[q3][moves-1][0]));
            
            dp[num][moves][0] = std::min(std::min(dp[q0][moves-1][1], dp[q1][moves-1][1]), 
                                         std::min(dp[q2][moves-1][1], dp[q3][moves-1][1]));
        }
    }
    
    int tests;
    std::scanf("%d", &tests);
    
    while (tests--)
    {
        int input, moves;
        std::scanf("%d %d", &input, &moves);
        
        if (dp[input][moves][1] > input)
            std::printf("Ada\n");
        else
            std::printf("Vinit\n");
    }
    
    return 0;
}
