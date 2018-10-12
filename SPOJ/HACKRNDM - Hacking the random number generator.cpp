/*HACKRNDM - Hacking the random number generator
#binary-search

You recently wrote a random number generator code for a web application and now you notice that some cracker has cracked it. It now gives numbers at a difference of some given value k more predominantly. You being a hacker decide to write a code that will take in n numbers as input and a value k and find the total number of pairs of numbers whose absolute difference is equal to k, in order to assist you in your random number generator testing.

NOTE: All values fit in the range of a signed integer, n, k>=1
Input

1st line contains n & k.
2nd line contains n numbers of the set. All the n numbers are assured to be distinct.

(Edited: n <= 10^5)
Output

One integer saying the no of pairs of numbers that have a diff k.
Example

Input:
5 2
1 5 3 4 2

Output:
3

*/

#include <algorithm>
#include <cstdio>

bool bsearch(int* lo, int* hi, int num)
{
    while (lo < hi)
    {
        int* mid = lo + (hi - lo) / 2;
        
        if (*mid == num)
            return true;
        else if (*mid > num)
            hi = mid;
        else
            lo = mid + 1;
    }
    
    return false;
}

int main()
{
    int n, k;
    std::scanf("%d%d", &n, &k);
    
    int arr[100001];
    
    for (int i = 0; i < n; ++i)
        std::scanf("%d", &arr[i]);
    
    std::sort(arr, arr + n);
     
    int res = 0;
    for (int i = 0; i < n; ++i)
        if (bsearch(arr + i, arr + n, arr[i] + k))
            ++res;
    
    std::printf("%d\n", res);
    
    return 0;
}
