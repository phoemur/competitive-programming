/*Zonal Computing Olympiad 2014, 30 Nov 2013

You are playing a video game in which several stacks of boxes are lined up on the floor, with a crane on top to rearrange the boxes, as shown in the picture below.


The crane supports the following commands:

• Move one position left (does nothing if already at the leftmost position)

• Move one position right (does nothing if already at the rightmost position)

• Pick up a box from the current stack (does nothing if the crane already has a box)

• Drop a box on the current stack (does nothing if the crane doesn't already have a box)

Further, there is a limit H on the number of boxes on each stack. If a 'drop' command would result in a stack having more than H boxes, the crane ignores this drop command. If the current stack has no boxes, a 'pick up' command is ignored.

You are given the initial number of boxes in each stack and the sequence of operations performed by the crane. You have to compute the final number of boxes in each stack.

For example, suppose the initial configuration of the game is as shown in the figure above, with 7 stacks and H=4. Then, after the following sequence of instructions,

1. Pick up box
2. Move right
3. Move right
4. Move right
5. Move right
6. Drop box
7. Move left
8. Pick up box
9. Move left
10. Drop box


the number of boxes in each stack from left to right would be 2,1,3,1,4,0,1.

Input format

• Line 1 : The width of the game (the number of stacks of boxes), N, followed by the max height H of each stack.

• Line 2 : N integers, the initial number of boxes in each stack, from left to right. Each number is ≤ H.

• Line 3 : A sequence of integers, each encoding a command to the crane.

        The commands are encoded as follows:

        1 : Move left

        2 : Move right

        3 : Pick up box

        4 : Drop box

        0 : Quit


• The command Quit (0) appears exactly once, and is the last command.

• The initial position of the crane is above the leftmost stack, with the crane not holding any box.

Output format

A single line with N integers, the number of boxes in each stack, from left to right.

Sample input 1

7 4
3 1 2 1 4 0 1
3 2 2 2 2 4 1 3 1 4 0


Sample output 1

2 1 3 1 4 0 1


Sample input 2

3 5
2 5 2
3 2 4 2 2 2 1 4 1 1 1 1 0


Sample output 2

1 5 2 


Test data

There is only one subtask worth 100 marks. In all inputs:

• The number of commands is between 1 and 105, inclusive.

• 1 ≤ N ≤ 105

• 1 ≤ H ≤ 108.
*/

#include <iostream>
#include <vector>

int main()
{
    int n, h;
    std::cin >> n >> h;
    
    std::vector<int> vec (n);
    int crane_pos = 0;
    bool crane_carry = false;
    
    
    // Initial position Input
    for (int i = 0; i < n; ++i)
        std::cin >> vec[i];
    
    // Input and Process
    for (int op; std::cin >> op && op != 0;)
    {
        switch(op)
        {
            case 1:
                if (crane_pos > 0)
                    --crane_pos;
                break;
            case 2:
                if (crane_pos + 1 < n)
                    ++crane_pos;
                break;
            case 3:
            {
                if (!crane_carry)
                {
                    if (vec[crane_pos] > 0)
                    {
                        crane_carry = true;
                        vec[crane_pos]--;
                    }
                }
                break;
            }
            case 4:
            {
                if (crane_carry)
                {
                    if (vec[crane_pos] < h)
                    {
                        crane_carry = false;
                        vec[crane_pos]++;
                    }
                }
                break;
            }
            default:
                break;
        }
    }
    
    // Output
    for (int i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << (i == vec.size() - 1 ? "\n" : " ");
    }
    
    return 0;
}
