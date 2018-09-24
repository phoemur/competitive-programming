/*UPDATEIT - Update the array !
#bitmasks

You have an array containing n elements initially all 0. You need to do a number of update operations on it. In each update you specify l, r and val which are the starting index, ending index and value to be added. After each update, you add the 'val' to all elements from index l to r. After 'u' updates are over, there will be q queries each containing an index for which you have to print the element at that index.
Input

First line consists of t, the number of test cases. (1 <= t <= 10)

Each test case consists of "n u",number of elements in the array and the number of update operations, in the first line (1 <= n <= 10000 and 1 <= u <= 100000)

Then follow u lines each of the format "l r val" (0 <= l,r < n, 0 <= val <=10000)

Next line contains q, the number of queries. (1 <= q <= 10000)

Next q lines contain an index (0 <= index < n)
Output

For each test case, output the answers to the corresponding queries in separate lines.
Example

Input:
1
5 3
0 1 7
2 4 6
1 3 2
3
0
3
4

Output:
7
8
6

*/

#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

// Hate ugly code, but this gets TLE easily
inline void fastRead (int *a)
{
    char c = 0;
    while(c<33)
    c = fgetc(stdin);
    *a = 0;
    while(c>33)
    {
        *a = *a*10 + c - '0';
        c = fgetc(stdin);
    }
}

int main()
{    
    int tests;
    fastRead(&tests);
    
    while (tests--)
    {
        int n, u;
        fastRead(&n);
        fastRead(&u);
        
        std::vector<int> bit (n+1);
        
        while (u--)
        {
            int l, r, val;
            fastRead(&l);
            fastRead(&r);
            fastRead(&val);
            
            ++l;
            ++r;
            
            while (l <= n)
            {
                bit[l] += val;
                l += (l & -l);
            }
            
            ++r;
            while (r <= n)
            {
                bit[r] += val * -1;
                r += (r & -r);
            }
        }
        
        int queries;
        fastRead(&queries);
        
        while (queries--)
        {
            int q;
            fastRead(&q);
            
            ++q;
            int sum = 0;
            while (q > 0)
            {
                sum += bit[q];
                q -= (q & -q);
            }
            
            printf("%d\n", sum);
        }
    }
    
    return 0;
}
