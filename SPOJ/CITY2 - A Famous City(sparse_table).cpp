/*CITY2 - A Famous City
no tags 

After Mr. B arrived in Warsaw, he was shocked by the skyscrapers and took several photos. But now when he looks at these photos, he finds in surprise that he isn't even able to point out the number of buildings in it. So he decides to work it out as follows:

- divide the photo into n vertical pieces from left to right. The buildings in the photo can be treated as rectangles, the lower edge of which is the horizon. One building may span several consecutive pieces, but each piece can only contain one visible building, or no buildings at all.

- measure the height of each building in that piece.

- write a program to calculate the minimum number of buildings.

Mr. B has finished the first two steps, the remaining comes to you.
Input

Each test case starts with a line containing an integer n (1 <= n <= 100,000). Following this is a line containing n integers - the height of building in each piece respectively. Note that zero height means there are no buildings in this piece at all. All the input numbers will be nonnegative and less than 1,000,000,000.
Output

For each test case, display a single line containing the case number and the minimum possible number of buildings in the photo.
Example

Input:
3
1 2 3
3
1 2 1

Output:
Case 1: 3
Case 2: 2

Explanation

The possible configurations of the samples are illustrated below:

https://www.spoj.com/content/john_jones:city2.jpg

*/

#include <algorithm>
#include <cstdio>
#include <map>

#define K 25
#define MAXN 100001

int st[MAXN][K + 1]; // sparse table for RMQ queries
int log2table[MAXN+1]; // stores log2 results

inline void preprocess_log()
{
    log2table[1] = 0;
    for (int i = 2; i <= MAXN; i++)
        log2table[i] = log2table[i/2] + 1;
}

inline void create_sparse_table(int n)
{    
    for (int i = 0; i < n; ++i)
        std::scanf("%d", &st[i][0]);
    
    for (int j = 1; j <= K; j++)
        for (int i = 0; i + (1 << j) <= n; i++)
            st[i][j] = std::min(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
}

inline int RMQ(int a, int b)
{
    int j = log2table[b - a + 1];
    return std::min(st[a][j], st[b - (1 << j) + 1][j]);
}

int main()
{
    preprocess_log();
    
    int n;
    int cas = 1;
    
    while (std::scanf("%d", &n) != EOF)
    {
        create_sparse_table(n);
        
        int ans = 0;
        std::map<int,int> previous_idx;
        
        for (int i = 0; i < n; ++i)
        {
            if (st[i][0] > 0)
            {
                if (previous_idx.find(st[i][0]) == previous_idx.end() || 
                    RMQ(previous_idx[st[i][0]], i) < st[i][0])
                {
                    previous_idx[st[i][0]] = i;
                    ans++;
                }
            }
        }
        
        std::printf("Case %d: %d\n", cas++, ans);
    }
    
    return 0;
}
