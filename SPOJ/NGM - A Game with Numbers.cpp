/*NGM - A Game with Numbers
no tags 

Nikifor and Trofim play the following game: they write some positive integer smaller than 2,000,000,000 and take turns one after another. Nikifor is the first to make a move. The turn is made by the following rule: from the written integer any non-zero digit is subtracted, and the new integer replaces the old one on the desk. For example for integer 40534, the next move can be: 40530, 40531 or 40529. The winner is the player who writes zero on the desk.

Write a program to decide who will win if both players do their best.
Input

The input contains the positive integer from which the game is started.
Output

In the first line you must write 1 if Nikifor wins and 2 otherwise. If Nikifor wins then in the second line you must output the move in the first turn which guarantees victory for him. If there are many such moves then output any of them.
Example

Input:
14

Output:
1
4

Author: Filimonenkov D.O.
*/

#include <iostream>

int main()
{
    long num;
    std::cin >> num;
    
    if (num % 10)
        std::cout << 1 << "\n" << num % 10 << std::endl;
    else
        std::cout << 2 << std::endl;
    
    return 0;
}
