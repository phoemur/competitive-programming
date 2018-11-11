/*CODESPTB - Insertion Sort
#tree

Insertion Sort is a classical sorting technique. One variant of insertion sort works as follows when sorting an array a[1..N] in non-descending order:

for i <- 2 to N
    j <- i
    while j > 1 and a[j] < a[j - 1]
        swap a[j] and a[j - 1]
        j <- j - 1

The pseudocode is simple to follow. In the ith step, element a[i] is inserted in the sorted sequence a[1..i - 1]. This is done by moving a[i] backward by swapping it with the previous element until it ends up in it's right position.

As you probably already know, the algorithm can be really slow. To study this more, you want to find out the number of times the swap operation is performed when sorting an array.
Input

The first line contains the number of test cases T. T test cases follow. The first line for each case contains N, the number of elements to be sorted. The next line contains N integers a[1],a[2]...,a[N].
Output

Output T lines, containing the required answer for each test case.
Constraints

1 <= T <= 5
1 <= N <= 100000
1 <= a[i] <= 1000000
Example

Sample Input:
2
5
1 1 1 2 2
5
2 1 3 1 2

Sample Output:
0
4

*/

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <utility>

long BIT[100001];

void update_bit(int pos, int n)
{
    while (pos <= n)
    {
        BIT[pos]++;
        pos += (pos & -pos);
    }
}

long query_bit(int pos)
{
    long sum = 0;
    
    while (pos > 0)
    {
        sum += BIT[pos];
        pos -= (pos & -pos);
    }
    
    return sum;
}

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int n;
        std::cin >> n;
        
        std::memset(BIT, 0, sizeof(long) * (n+1));
        
        std::vector<std::pair<int,int>> arr (n);
        
        for (int i = 0; i < n; ++i)
        {
            std::cin >> arr[i].first; // Value
            arr[i].second = i+1;      // 1 based index
        }
        
        std::sort(arr.rbegin(), arr.rend());
        
        long res = 0;
        for (int i = 0; i < n; ++i)
        {
            res += query_bit(arr[i].second);
            update_bit(arr[i].second, n);
        }
        
        std::cout << res << std::endl;
    }
    
    return 0;
}
