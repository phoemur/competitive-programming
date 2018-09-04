/*ONP - Transform the Expression
#stack

Transform the algebraic expression with brackets into RPN form (Reverse Polish Notation). Two-argument operators: +, -, *, /, ^ (priority from the lowest to the highest), brackets ( ). Operands: only letters: a,b,...,z. Assume that there is only one RPN form (no expressions like a*b*c).
Input

t [the number of expressions <= 100]
expression [length <= 400]
[other expressions]

Text grouped in [ ] does not appear in the input file.
Output

The expressions in RPN form, one per line.

Example

Input:
3
(a+(b*c))
((a+b)*(z+x))
((a+t)*((b+(a+c))^(c+d)))

Output:
abc*+
ab+zx+*
at+bac++cd+^*

*/

#include <cctype>
#include <iostream>
#include <stack>
#include <string>

inline const short precedence(char op) noexcept
{
    switch (op)
    {
        case '+':
            return 1;
        case '-':
            return 2;
        case '*':
            return 3;
        case '/':
            return 4;
        case '^':
            return 5;
        default:
            return -1;
    }
}


inline bool has_precedence(char op1, char op2) noexcept
{
    return precedence(op1) > precedence(op2);
}


std::string solve(const std::string& exp)
{
    std::string res;
    res.reserve(exp.size());
    
    std::stack<char> st;
    
    for (char c: exp)
    {
        if (std::isalpha(c)) // Operand
        {
            res.push_back(c);
        }
        else if (c == '(')
        {
            st.push(c);
        }
        else if (c == ')')
        {
            // Add everything until the opening parenthesis is found
            while (!st.empty() && st.top() != '(')
            {
                res.push_back(st.top());
                st.pop();
            }
            
            if(!st.empty()) st.pop(); // Pop the opening parenthesis
        }
        else // Operator
        {
            // Add everything until an operator with greater precedence is found
            while (!st.empty() && has_precedence(st.top(), c))
            {
                res.push_back(st.top());
                st.pop();
            }
            
            st.push(c);
        }
    }
    
    // Add remaining ops
    while (!st.empty())
    {
        res.push_back(st.top());
        st.pop();
    }
    
    return res;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int n;
    std::cin >> n;
    
    std::string input;
    
    while (n--)
    {
        if (std::cin >> input)
            std::cout << solve(input) << std::endl;
    }
    
    return 0;
}
