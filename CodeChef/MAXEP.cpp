/*This is an interactive problem.

Max has an electrical panel. He knows that there is an integer x
(1≤x≤N) such that if the panel is connected to voltage greater or equal to x, it will break. However, he does not know the exact value of x

.

You must help Max determine x

. You may perform operations of two types:

    Connect the panel to voltage y

, where y is an arbitrary integer between 1 and N inclusive. This operation costs 1
coin, and you may only perform it if the panel is not broken. After this operation, you find out whether the panel is broken.
Fix the broken panel. This operation costs c

    coins.

Each operation may be performed any number of times as long as you have enough coins. Initially, you have 1,000

coins.
Interaction

    First, you should read a line containing two space-separated integers N

and c
.
To perform an operation of the first type, you should print a line containing two space-separated integers 1
and y. Then, you must read a line containing a single integer: 0 if the panel is not broken after this operation, 1 if it is broken or −1
if the operation was invalid.
To perform an operation of the second type, you should print a line containing a single integer 2
.
Finally, you should print a line containing two space-separated integers 3
and x

    .

Don't forget to flush the output after printing each line!
Constraints

    1≤N≤150,000

1≤c≤150

Subtasks

Subtask #1 (15 points): 1≤N≤1,000

Subtask #2 (25 points): 1≤c≤50

Subtask #3 (60 points): original constraints
Example

You             Grader
                10 8
1 7
                1
2
1 5
                1
2
1 3
                0
1 4
                1
2
3 4
*/

#include <iostream>

int main()
{    
    int n, c;
    std::cin >> n >> c;
    
    // Advance until broken or reach end
    int i = 1;
    int res = 0;
    
    while (i <= n)
    {
        std::cout << 1 << " " << i << std::endl;
        std::cin >> res;
                
        if (res == 1)
            break;
        else // res == 0
            i += 400;
    }
    
    if (i > 1)
    {    
        if (res == 1)
            std::cout << 2 << std::endl;
        
        for (int j = i - 399; j <= i; ++j)
        {
            std::cout << 1 << " " << j << std::endl;
            std::cin >> res;
        
            if (res == 1)
            {
                std::cout << 3 << " " << j << std::endl;
                break;
            }
        }
    }
    else
        std::cout << 3 << " " << i << std::endl;
    
    
    return 0;
}
