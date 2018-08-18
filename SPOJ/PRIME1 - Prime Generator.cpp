/*
PRIME1 - Prime Generator
#number-theory

Peter wants to generate some prime numbers for his cryptosystem. Help him! Your task is to generate all prime numbers between two given numbers!
Input

The input begins with the number t of test cases in a single line (t<=10). In each of the next t lines there are two numbers m and n (1 <= m <= n <= 1000000000, n-m<=100000) separated by a space.
Output

For every test case print all prime numbers p such that m <= p <= n, one number per line, test cases separated by an empty line.
Example

Input:
2
1 10
3 5

Output:
2
3
5
7

3
5

Warning: large Input/Output data, be careful with certain languages (though most should be OK if the algorithm is well designed)
Information
After cluster change, please consider PRINT as a more challenging problem. 
*/

#include <iostream>
using namespace std;

inline bool isPrime(int num) noexcept
{
    // Corner cases
    if (num <= 1) return false;
    else if (num <= 3) return true;
    else if (num % 2 == 0 || num % 3 == 0) return false;

    // Check loop
    for (int i=5; i*i <= num; i += 6) {
        if (num % i == 0 || num % (i+2) == 0) return false;
    }
    
    return true;
}

int main() {
	int queries, l, r;
	cin >> queries;
	
	while (queries--) {
		
		cin >> l >> r;
		
		for (;l<=r; ++l) {
			if (isPrime(l)) {
				cout << l << endl;
			}
		}
		
		cout << endl;
	}
	
	return 0;
}
