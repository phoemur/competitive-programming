/*ORDERSET - Order statistic set
#tree #binary-search

English 	Vietnamese

In this problem, you have to maintain a dynamic set of numbers which support the two fundamental operations

    INSERT(S,x): if x is not in S, insert x into S
    DELETE(S,x): if x is in S, delete x from S

and the two type of queries

    K-TH(S) : return the k-th smallest element of S
    COUNT(S,x): return the number of elements of S smaller than x

Input

    Line 1: Q (1 ≤ Q ≤ 200000), the number of operations
    In the next Q lines, the first token of each line is a character I, D, K or C meaning that the corresponding operation is INSERT, DELETE, K-TH or COUNT, respectively, following by a whitespace and an integer which is the parameter for that operation.

If the parameter is a value x, it is guaranteed that 0 ≤ |x| ≤ 109. If the parameter is an index k, it is guaranteed that 1 ≤ k ≤ 109.
Output

For each query, print the corresponding result in a single line. In particular, for the queries K-TH, if k is larger than the number of elements in S, print the word 'invalid'.
Example

Input
8
I -1
I -1
I 2
C 0
K 2
D -1
K 1
K 2

Output
1
2
2
invalid

*/

#include <bits/stdc++.h>

// Now this GCCism
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

using ordered_set = tree<int,
                         null_type,
                         less<int>,
                         rb_tree_tag,
                         tree_order_statistics_node_update>;

int main()
{
    ios_base::sync_with_stdio(false);
    
    ordered_set ST;
    
    int q;
    cin >> q;
    
    while (q--)
    {
        char op;
        int x;
        cin >> op >> x;
        
        switch(op)
        {
            case 'I':
                ST.insert(x);
                break;
            case 'D':
                ST.erase(x);
                break;
            case 'K':
            {
                if (x > ST.size())
                    cout << "invalid" << endl;
                else
                    cout << *ST.find_by_order(x-1) << endl;
                    
                break;
            }
            case 'C':
                cout << ST.order_of_key(x) << endl;
                break;
            default:
                break;
        }
    }
    
    return 0;
}
