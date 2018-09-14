/*AP2 - AP - Complete The Series (Easy)
no tags 

Arithmatic and geometric Progressions are 2 of the well known progressions in maths.

Arithmatic progression(AP) is a set in which the difference between 2 numbers in constant. for e.g., 1, 3, 5, 7, 9 .... In this series the difference between 2 numbers is 2.

The task here is very simple indeed.

You will be given the 3rd term , 3rd last term and the sum of the series. You need print length of the series & the series.
Input

First line will contain a number indicating the number of test cases.

Each of the following t lines will have 3 number '3term' ,'3Lastterm' and 'sum'

3term  - is the 3rd term in of the series and

3Lastterm  - is the 3rd term in of the series and

sum - is the sum of the series.
Output

For each input of the test case, you need to print 2 lines.

First line should have 1 value - the number of terms in the series.

2nd line of the output should print the series numbers separated by single space.
Example

Input:
1
3 8 55

Output:
10
1 2 3 4 5 6 7 8 9 10

NOTE:

    In all the test cases, all the series elements are positive integers.
    The series will have at least 7 elements.
    number of test cases <=100.
    All the numbers will fit in 64 bits (long long in C)

*/

#include <cstdint>
#include <iostream>

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        std::int64_t f3, l3, sum;
        std::cin >> f3 >> l3 >> sum;
        
        std::int64_t n = (2 * sum) / (f3 + l3);
        std::int64_t increment = (l3 - f3) / (n - 5);
        std::int64_t first = f3 - 2 * increment;
        
        
        std::cout << n << std::endl;
        while (n--)
        {
            std::cout << first << " ";
            first += increment;
        }
        
        std::cout << std::endl;
    }
    
    return 0;
}
