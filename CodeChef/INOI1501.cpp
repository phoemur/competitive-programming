/*Indian National Olympiad in Informatics 2015

In this problem you are given two lists of N integers, a1, a2, ..., aN and b1, b2, ... bN. For any pair (i, j) with i, j ϵ {1, 2, ..., N} we define the segment from i to j, written as [i, j], to be i, i + 1, ..., j if i ≤ j and i, i + 1, ..., N, 1, 2, ...,j if i > j. Thus if N = 5 then the [2, 4] = {2, 3, 4} and [4, 2] = {4, 5, 1, 2}.

With each segment [i, j] we associate a special sum SSum[i, j] as follows:

    SSum[i, i] = ai.
    If i ≠ j then, 

    The positions i and j contribute ai and aj, respectively, to the sum while every other position k in [i, j] contributes bk.

Suppose N = 5 and that the two given sequences are as follows:
i  1  2  3  4  5
ai 2  3  2  3  1
bi 3  4  4  6  3

Then, SSum[1, 1] = 2, SSum[2, 4] = 3 + 4 + 3 = 10 and SSum[4, 2] = 3 + 3 + 3 + 3 = 12. Your aim is to compute the maximum value of SSum[i, j] over all segments [i, j]. In this example you can verify that this value is 18 (SSum[2, 1] = 18).
Input format

    The first line contains a single positive integer N.

    This is followed by a line containing N integers giving the values of the ais and this is followed by a line containing N integers giving the values of the bis.

Output format

A single integer in a single line giving the maximum possible special segment sum.

Note: The final value may not fit in a 32 bit integer. Use variables of an appropriate type to store and manipulate this value (long long in C/C++, long in Java).
Test Data

You may assume that -109 ≤ ai, bi ≤ 109.

Subtask 1 (10 Marks) 1 ≤ N ≤ 3000.
Subtask 2 (20 Marks) 1 ≤ N ≤ 106 and ai = bi for all 1 ≤ i ≤ N.
Subtask 3 (30 Marks) 3 ≤ N ≤106. Further a1 = b1 = aN = bN = -109 and for each
1 < k < N we have -999 ≤ ak, bk ≤ 999.
Subtask 4 (40 Marks) 1 ≤ N ≤ 106.
Example

Here is the sample input and output corresponding to the example above:
Sample input

5
2 3 2 3 1
3 4 4 6 3

Sample output

18
*/

#include <algorithm>
#include <cstdio>
#include <vector>

// Not used, just to ilustrate
long long special_sum(int i, int j, 
                      const std::vector<long long>& a,
                      const std::vector<long long>& b) // b is preffix sum array
{
    if (i == j)
        return a[i];
    else if (i < j)
        return (a[i] - b[i]) + a[j] + b[j-1] ;
    else // i > j
        return (a[i] - b[i]) + a[j] + b.back()  + (j > 0 ? b[j-1] : 0LL);
}

int main()
{
    int n;
    std::scanf("%d", &n);
    
    std::vector<long long> a     (n);
    std::vector<long long> b     (n);
    std::vector<long long> diff  (n); // Diff before (best diff until)
    std::vector<long long> diff2 (n); // Diff after
    
    for (auto& e: a) std::scanf("%lld", &e);
    
    // Input B as preffix sum array
    std::scanf("%lld", &b[0]);
    for (int i = 1; i < n; ++i)
    {
        std::scanf("%lld", &b[i]);
        b[i] += b[i-1];
    }
    
    // Build diff (a[i] - b[i]) max array
    diff[0] = a[0] - b[0];
    for (int i = 1; i < n; ++i)
        diff[i] = std::max(diff[i-1], a[i] - b[i]);
    
    // Build diff2
    diff2[n-1] = a[n-1] - b[n-1];
    for (int i = n-2; i >= 0; --i)
        diff2[i] = std::max(diff2[i+1], a[i] - b[i]);
    
    // j == 0
    long long res = std::max(a[0], // i == j 
                             a[0] + b[n-1] + diff2[1]); // i > j
    
    for (int j = 1; j < n-1; ++j)
        res = std::max({res, 
                        a[j] + b[j-1] + diff[j-1], // i < j 
                        a[j], // i == j
                        a[j] + b[n-1] + b[j-1] + diff2[j+1]}); // i > j
        
    // j == n-1
    if (n > 2)
        res = std::max({res, 
                        a[n-1], // i == j 
                        a[n-1] + b[n-2] + diff[n-2]}); // i < j
    else
        res = std::max(res, a[n-1]);
    
    std::printf("%lld\n", res);
    
    return 0;
}
