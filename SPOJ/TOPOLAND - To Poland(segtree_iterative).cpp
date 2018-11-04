/*TOPOLAND - To Poland
no tags 

Little Russell and Mr. Fredricksen are embarking in a new journey with their balloon house. After visiting South America and helping Kevin, the Snipe, they decided to travel to Warsaw, Poland where new specimens of birds might be found.

Their trip is divided into several parts. Due to pressure levels and wind speed, each part of their journey requires that their house is equipped with a minimum number of balloons. As a good boy scout, Russell has already figured out how many balloons are necessary to go through each of the parts. The problem is that atmosphere conditions change and Russel is having trouble determining how many balloons the house should be equipped with to go through continuous parts of the journey, so they don't have to fill up more balloons than necessary.

To help out Russell, you are to develop a program that must deal with the following queries:

    Russell has added or removed balloons from the house
    The minimum number of balloons at certain part has changed
    How many balloons should be added or removed so that the house goes through continuous parts of the journey with the minimum necessary number of balloons?

Input

The first line contains a number T (T ≤ 100), the number of testcases.

Each testcase starts with numbers N (1 ≤ N ≤ 105) and M (0 ≤ M ≤ 103) where N is the number of parts in the journey and M  is the initial number of balloons in the house. Then N numbers follow, one per line, where each number Ni (0 ≤ Ni ≤ 109, 0 ≤ i < N) represents the initial number of balloons necessary to go through part i.

On the next line there is a number Q (1 ≤ Q ≤ 105), the number of queries that you should answer. Each of the next Q lines contains a query in one of the following formats:

    "A K" -  where A is the actual character 'A' (quotes for clarity) and K (-103 ≤ K ≤ 103) is the number of balloons that have been added or removed from the house.  It is assured that the total number of balloons in the house is never negative;
    "B J K" - where B is the actual character 'B' (quotes for clarity), J (0 ≤ J < N) is the number of the part of the journey (0-indexed) and K (0 ≤ K ≤ 109) is the new minimum number of balloons required to go through part J;
    "C I J" - where C is the actual character 'C' (quotes for clarity), and [I, J], 0 ≤ I ≤ J < N$ is the range that Russell would like to query. For each query of this type, print the difference between the number of balloons currently in the house and the minimum necessary to go through all the parts between I and J inclusive. Note that this query doesn't change the number of balloons in the house.

Output

For each testcase print one line with "Testcase X:" (quotes for clarity) where X is the number of the testcase (0-indexed). For each query of the type "C I J" print one line with the difference between the number of balloons currently in the house and the minimum necessary to go through all the parts between I and J inclusive.

Print one blank line after each testcase.
Example

Input:
2
3 11
5 2 4
1
C 0 2
3 11
16 2 17
5
C 0 2
A -2
C 1 2
B 0 0
C 0 1

Output:
Testcase 0:
6

Testcase 1:
6
8
7

*/

#include <algorithm>
#include <climits>
#include <cstdio>
#include <vector>

int main()
{
    int tests;
    std::scanf("%d", &tests);
    
    for (int test = 0; test < tests; ++test)
    {
        int n, m;
        std::scanf("%d %d", &n, &m);
        
        // Ensure sz is a power of 2 
        int sz = n;
        while ((sz & (sz - 1)) != 0) ++sz;
        std::vector<int> segtree (sz << 1, INT_MIN);
        
        // Input leaf nodes
        for (int i = 0; i < n; ++i)
            std::scanf("%d", &segtree[sz+i]);
        
        // Compute parent nodes
        for (int i = sz - 1; i > 0; --i)
            segtree[i] = std::max(segtree[i<<1], segtree[i<<1 | 1]);
        
        std::printf("Testcase %d:\n", test);
        
        int queries;
        std::scanf("%d", &queries);
        
        while (queries--)
        {
            char op;
            std::scanf(" %c", &op);
            
            if (op == 'A')
            {
                int k;
                std::scanf("%d", &k);
                m += k;
            }
            else if (op == 'B')
            {
                int j, k;
                std::scanf("%d %d", &j, &k);
                
                segtree[sz + j] = k;
                
                for (int i = sz+j; i > 1; i >>= 1)
                    segtree[i>>1] = std::max(segtree[i], segtree[i^1]);
            }
            else
            {
                int l, r;
                std::scanf("%d %d", &l, &r);
                
                int res = INT_MIN;
                for (l += sz, r += sz+1; l < r; l >>= 1, r >>= 1)
                {
                    if (l & 1) 
                        res = std::max(res, segtree[l++]);
    
                    if (r & 1) 
                        res = std::max(res, segtree[--r]);
                }
                
                res = std::abs(m - res);                
                std::printf("%d\n", res);
            }
        }
        
        std::printf("\n");
    }
    
    return 0;
}
