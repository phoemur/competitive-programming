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

#define MAXN 100001

int tree[3*MAXN]; // segtree for range minimum queries
int arr[MAXN]; // input array

void build(int node, int lo, int hi)
{
    if (lo > hi)
        return;
    else if (lo == hi)
        tree[node] = arr[lo];
    else
    {
        int mid = (lo + hi) / 2;
        
        build(node*2,      lo, mid);
        build(node*2+1, mid+1,  hi);
        
        tree[node] = std::min(tree[node*2], tree[node*2+1]);
    }
}

int range_query(int node, int lo, int hi, int i, int j)
{
    if (lo > hi || lo > j || hi < i)
        return 1 << 30;
    else if (lo >= i && hi <= j)
        return tree[node];
    else
    {
        int mid = (lo + hi) / 2;
        
        if (j <= mid)
            return range_query(node*2,      lo, mid, i, j);
        else if (i > mid)
            return range_query(node*2+1, mid+1,  hi, i, j);
        else
        {
            int q1 = range_query(node*2,      lo, mid, i, j);
            int q2 = range_query(node*2+1, mid+1,  hi, i, j);
            
            return std::min(q1, q2);
        }
    }
}

int main()
{   
    int n;
    int cas = 1;
    
    while (std::scanf("%d", &n) != EOF)
    {
        for (int i = 0; i < n; ++i)
            std::scanf("%d", &arr[i]);
        
        build(1, 0, n-1);
        
        int ans = 0;
        std::map<int,int> previous_idx {};
        
        for (int i = 0; i < n; ++i)
        {
            if (arr[i] > 0)
            {
                if (previous_idx.find(arr[i]) == previous_idx.end() || 
                    range_query(1, 0, n-1, previous_idx[arr[i]], i) < arr[i])
                {
                    previous_idx[arr[i]] = i;
                    ans++;
                }
            }
        }
        
        std::printf("Case %d: %d\n", cas++, ans);
    }
    
    return 0;
}
