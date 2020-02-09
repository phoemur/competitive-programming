/*MUL - Fast Multiplication
#simple-math #recursion

Multiply the given numbers.
Input

n [the number of multiplications <= 1000]

l1 l2 [numbers to multiply (at most 10000 decimal digits each)]

Text grouped in [ ] does not appear in the input file.
Output

The results of multiplications.
Example

Input:
5
4 2
123 43
324 342
0 12
9999 12345

Output:
8
5289
110808
0
123437655

Warning: large Input/Output data, be careful with certain languages
*/

#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int n;
    std::cin >> n;
    
    cpp_int l1, l2;
    
    while (n--)
    {
        std::cin >> l1 >> l2;
        std::cout << l1 * l2 << std::endl;
    }
    

    return 0;
}
