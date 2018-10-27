/*All submissions for this problem are available.
A tutorial for this problem is now available on our blog. Click here to read it.

You are asked to calculate factorials of some small positive integers.
Input

An integer t, 1<=t<=100, denoting the number of testcases, followed by t lines, each containing a single integer n, 1<=n<=100.
Output

For each integer n given at input, display a line with the value of n!
Example
Sample input:

4
1
2
5
3

Sample output:

1
2
120
6

*/

#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;
using namespace std;

inline cpp_int factorial(const int num)
{
    cpp_int res = 1;
    for (int i=1; i<= num; ++i)
        res *= i;
    
    return res;    
}

int main()
{
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        cout << factorial(n) << endl;
    }

    return 0;
}
