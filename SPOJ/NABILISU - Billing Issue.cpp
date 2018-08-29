/* NABILISU - Billing Issue
no tags 

 
Everyday morning Nabil and Muzahid go to the famous hotel “Ruchi Bilash” and
complete their breakfast. But they have a system in it, everyday don’t know how, always Nabil makes a
bigger bill. For example: – Nabil made 65 tk and Muzahid made 55 tk. But there is a Funny thing.
Muzahid always gives the waiter tips at least 1 taka. And for that tips, they both pay equal. If we
consider previous example, than Nabil will pay 65 and Muzahid will also pay 65, His bill is 55 and 10 tk
tip for waiter. Remember: Muzahid’s bill never crosses Nabil’s bill.

Everyday morning Nabil and Muzahid go to the famous hotel “Ruchi Bilash” and complete their breakfast. But they have a system in it, everyday don’t know how, always Nabil makes a bigger bill. For example: – Nabil made 65 tk and Muzahid made 55 tk. But there is a Funny thing. Muzahid always gives the waiter tips at least 1 taka. And for that tips, they both pay equal. If we consider previous example, than Nabil will pay 65 and Muzahid will also pay 65, His bill is 55 and 10 tk tip for waiter.

Note that Muzahid’s bill never crosses Nabil’s bill.

 
Input

You will get an integer T, the number of test cases. After that line, there will be T lines as input. You will get 3 integers in every line a, b, k as Nabil’s bill, Muzahid’s bill and waiter’s tip.
Constraints

1 <= T <=10

1 <= a,b <= 1000

0 <= k <= 50
Output

Print “YES” (Without Quotes) if it is possible to fill such condition given above. Otherwise, print “NO” (Without Quotes). Follow the sample input output formation.
Example

Input:
5
65 55 10
75 55 20
75 55 10
55 75 20
50 50 0

Output:
Case 1: YES
Case 2: YES
Case 3: NO
Case 4: NO
Case 5: NO

[ This problem orginally contributed by MD. Yasir Uddin Nabil ]

*/

#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int n, a, b, c;
    std::cin >> n;
    
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a >> b >> c;
        
        if (b+c == a && c > 0)
            std::cout << "Case " << i << ": YES\n";
        else
            std::cout << "Case " << i << ": NO\n";

    }
    
    return 0;
}
