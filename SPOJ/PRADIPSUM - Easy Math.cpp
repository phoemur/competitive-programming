/*PRADIPSUM - Easy Math
no tags 

Zoro is a student of a primary school. He likes to solve mathematical problem. One day he tries to solve a math, but he is unable to solve the problem efficiently because of being a student of primary school. As you are a programmer he wants your help to solve this problem. The problem is to find the sum of some consecutive numbers.

Example, if the first number is 2 and the last number is 5, then the result would be

2 + 3 + 4 + 5 = 14
Input

Every line contains two integers a and b. Input is terminated by the end of file.
Output

Output the sum the of all numbers between a and b (inclusively).
Constraints

-108  ≤ (a , b) ≤ 108
Example

Input:

2 5

5 10
Output:

14

45

*/

#include <algorithm>
#include <iostream>

int main()
{
    long long a, b, sum, first, last;
    
    while (std::cin >> a >> b)
    {
        sum = 0;
        first = std::min(a, b);
        last = std::max(a, b);
        
        for (;first <= last; ++first)
            sum += first;
        
        std::cout << sum << std::endl;
    }
    
    return 0;
}
