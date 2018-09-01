/*ANARC08E - Relax! It is just a game
#dynamic-programming

You: What's the score? Did I miss much?

Me: It's 2-1 for elAhli and the second half just started. The first half was quite boring.

You: Who scored first? elAhli or ezZamalek?

Me: What difference does it make?

You: Big difference! I can predict the outcome of the match if I knew the order of which goals were scored in the first half.

Me: What do you mean?

You: It's 2-1 for elAhli, right? One of three things could have happened: elAhli scored two goals then ezZamalek scored; Or, elAhli scored its first goal, then ezZamalek, then elAhli again; Or, ezZamalek scored first, then elAhli scored its two goals.

Me: So?!! I still don't understand what difference does that make? It's still 2-1 for elAhli! Why don't you just relax and let us continue watching the game in peace.

You: You don't understand!! I believe the probability of who'll win depends on the order of how goals were scored. Now I have to predict the outcome for 3 possibilities.

Me: And what if the score was 3-2? What would you have done then?

You: I would have to work for 5 different possibilities. No?

Me: Of course not! The number of possibilities isn't always equal to the sum.

You: Can you tell me when will it be equal to the sum?

Me: You're a programmer, why don't you write a program that counts the number of possibilities and compare it to the sum?

You: I don't have the time, I want to watch the match. Besides, I have nine other problems to worry about.

Me: I'll give you a hint. The possibilities will be equal to the sum only if one of the teams scored a certain number of goals.
Input

Your program will be tested on one or more test cases. Each test case specifies two natural numbers (A and B ) (separated by one or more spaces) representing the score of the first half. No team will be able to score more than 10 goals. The last line of the input file contains two -1's (which is not part of the test cases.)
Output

Format For each test case where the number of possibilities is equal to the sum, print:

A+B=C

Where A and B are as above and C is their sum. If the number of possibilities is not equal to the sum, replace the '=' sign with '!=' (without the quotes.)
Example

Input:
2 1
1 0
-1 -1

Output:
2+1=3
1+0=1

*/

#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int a, b;
    
    while (true)
    {
        std::cin >> a >> b;
        
        if (a == -1) break;
        else if (a == 1 || b == 1)
            std::cout << a << "+" << b << "=" << a + b << std::endl;
        else
            std::cout << a << "+" << b << "!=" << a + b << std::endl;
    }
    
    return 0;
}
