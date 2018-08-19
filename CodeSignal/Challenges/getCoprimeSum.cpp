/*Given an integer n, we'd like to find the sum of all integers between 1 and n (inclusive) that are relatively prime to n.

Since this number can be quite large, return the sum mod 109 + 7.

Example

    For n = 10 the output should be getCoprimeSum(n) = 20.
    d 	1 	2 	3 	4 	5 	6 	7 	8 	9 	10
    gcd(n, d) 	1 	2 	1 	2 	5 	2 	1 	2 	1 	10

    Only 1, 3, 7, and 9 are relatively prime with n, and 1 + 3 + 7 + 9 = 20.

Input / Output

    [execution time limit] 0.5 seconds (cpp)

    [input] integer n

    A non-negative integer that we're trying to find coprimes with respect to.

    Guaranteed constraints:
    1 ≤ n ≤ 108

    [output] integer

    The sum of all numbers less than or equal to n that are relatively prime to n (mod 109 + 7)
*/

auto Y(int n)
{   
    set<double> r;
    while (n%2 == 0) {
        r.insert(2);
        n /= 2;
    }
    
    for (int i = 3; i <= sqrt(n); i += 2) {
        while (n%i == 0) {
            r.insert(i);
            n /= i;
        }
    }
    
    if (n > 2) r.insert(n);
    
    return r;
}

int getCoprimeSum(double n) {
    if (n == 1) return 1;
    
    auto r = n/2 * n;
    for (auto& i: Y(n)) {
        r *= (1 - (1/i));
    }
    
    return (long)r % 1000000007;
}
