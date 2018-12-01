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
#include <cstring>
#include <iostream>

int memo[10000][101][2];

/* Dynamic Programming Top Down (memoization) */
int solve_recursive(int number, int moves, int maximizer)
{
    if (moves == 0)
        return number;
    else if (memo[number][moves][maximizer] != 0)
        return memo[number][moves][maximizer];
    
    int q3 = number          % 10 == 9 ? number - 9    : number + 1;    // digit[3]
    int q2 = (number / 10)   % 10 == 9 ? number - 90   : number + 10;   // digit[2]
    int q1 = (number / 100)  % 10 == 9 ? number - 900  : number + 100;  // digit[1]
    int q0 = (number / 1000) % 10 == 9 ? number - 9000 : number + 1000; // digit[0]
    
    if (maximizer)
        memo[number][moves][maximizer] = std::max({solve_recursive(q0, moves - 1, !maximizer), 
                                                   solve_recursive(q1, moves - 1, !maximizer), 
                                                   solve_recursive(q2, moves - 1, !maximizer), 
                                                   solve_recursive(q3, moves - 1, !maximizer)});
    else
        memo[number][moves][maximizer] = std::min({solve_recursive(q0, moves - 1, !maximizer), 
                                                   solve_recursive(q1, moves - 1, !maximizer), 
                                                   solve_recursive(q2, moves - 1, !maximizer), 
                                                   solve_recursive(q3, moves - 1, !maximizer)});
        
    return memo[number][moves][maximizer];
}

int main()
{
    std::memset(memo, 0, sizeof(int) * 10000 * 101 * 2);
    
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int input, moves;
        std::cin >> input >> moves;
        
        int res = solve_recursive(input, moves, true);
        
        if (res > input)
            std::cout << "Ada" << std::endl;
        else
            std::cout << "Vinit" << std::endl;
    }
    
    return 0;
}
