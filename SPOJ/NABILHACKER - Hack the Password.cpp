/*NABILHACKER - Hack the Password
no tags 

Many people asked me what actually contest programming do in real life projects. That does not feel so interesting to me. What I found interesting is, one day a hacker friend came to me. He asked me to solve one of his hacking problems.

When you try to steal someone's password, you may set a keylogger in his/her computer. Keylogger will give you a string that is typed as the password. But there is a problem, it will give you everything victim typed such as left key, right key, backspace everything. (Left key and right key means the keys you use to play car games, and backspace is the key you use to remove a letter, the button on the top of "Enter" button. )

Suppose, the victim typed "generio312" as password, but he follows these criteria:

1. he typed generio1.

2. Then he pressed the left key, and press 3. So the password will be generio31.

3. Then he pressed the right key and press 2. So the password will be generio312.

4. Now he typed ghj and then press backspace three times and remove these three letters. So the final password is generio312.

But, as I said, keylogger gives you all the typed key. You will get "generio1<3>2ghj---". (Here, < for left key, > for right key and - for backspace.)
Input

At first input T, the number of test cases.
Then input T strings. 1<=|s|<=10^6. The strings will include upper case, lower case, <, >, - and digits(0-9).
Output

The output should contain a string each line, the password.
Example

Input:

2

<<BP<A>>Cd-

ThisIsS3Cr3t
Output:

BAPC

ThisIsS3Cr3t

*/

#include <cctype>
#include <iostream>
#include <stack>
#include <string>

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int tests;
    std::cin >> tests;
    
    std::stack<char> my_stack;
    
    while (tests--)
    {        
        std::string input, output;
        std::cin >> input;
        
        for (char c: input)
        {
            switch (c)
            {
                case '-':
                {
                    if (!output.empty())
                        output.pop_back();
                    
                    break;
                }
                case '<':
                {
                    if (!output.empty())
                    {
                        my_stack.push(output.back());
                        output.pop_back();
                    }
                    
                    break;
                }
                case '>':
                {
                    if (!my_stack.empty())
                    {
                        output.push_back(my_stack.top());
                        my_stack.pop();
                    }
                    
                    break;
                }
                default:
                    output.push_back(c);
                
            }
        }
        
        while (!my_stack.empty())
        {
            output.push_back(my_stack.top());
            my_stack.pop();
        }
        
        std::cout << output << std::endl;
        
    }
    
    return 0;
}
