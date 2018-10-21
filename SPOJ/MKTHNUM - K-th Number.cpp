/*MKTHNUM - K-th Number
#sorting #tree

English 	Vietnamese

You are working for Macrohard company in data structures department. After failing your previous task about key insertion you were asked to write a new data structure that would be able to return quickly k-th order statistics in the array segment.

That is, given an array a[1 ... n] of different integer numbers, your program must answer a series of questions Q(i, j, k) in the form: "What would be the k-th number in a[i ... j] segment, if this segment was sorted?"

For example, consider the array a = (1, 5, 2, 6, 3, 7, 4). Let the question be Q(2, 5, 3). The segment a[2 ... 5] is (5, 2, 6, 3). If we sort this segment, we get (2, 3, 5, 6), the third number is 5, and therefore the answer to the question is 5.

Input

The first line of the input contains n — the size of the array, and m — the number of questions to answer (1 ≤ n ≤ 100000, 1 ≤ m ≤ 5000).

The second line contains n different integer numbers not exceeding 10^9 by their absolute values — the array for which the answers should be given.

The following m lines contain question descriptions, each description consists of three numbers: i, j, and k (1 ≤ i ≤ j ≤ n, 1 ≤ k ≤ j - i + 1) and represents the question Q(i, j, k).

SAMPLE INPUT
7 3
1 5 2 6 3 7 4
2 5 3
4 4 1
1 7 3

Output

 
For each question output the answer to it — the k-th number in sorted 
a[i ... j] segment. 

SAMPLE OUTPUT
5
6
3

Note : naive solution will not work!!! */

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

// Visit https://www.geeksforgeeks.org/merge-sort-tree-for-range-order-statistics/ for explanation

int arr[100005];
std::vector<int> tree[300015]; // Merge Sort Tree

void build_tree(int node, 
                int a, 
                int b, 
                const std::vector<std::pair<int,int>>& vec)
{
    if (a == b) // Leaf node
    {
        tree[node].push_back(vec[a].second);
    }
    else
    {
        int mid = (a + b) / 2;
        
        build_tree(node*2, a, mid, vec);
        build_tree(node*2+1, mid+1, b, vec);
        
        tree[node].resize(tree[node*2].size() + tree[node*2+1].size());
        std::merge(std::begin(tree[node*2]), 
                   std::end(tree[node*2]), 
                   std::begin(tree[node*2+1]), 
                   std::end(tree[node*2+1]), 
                   std::begin(tree[node]));
    }
}

int query_tree(int node, 
               int lo, 
               int hi, 
               int query_start, 
               int query_end, 
               int k)
{
    if (lo == hi) // Leaf Node
        return tree[node][0];
    else
    {
        int mid = (lo + hi) / 2;
        
        // finds the last index in the left segment  
        // which is <= queryEnd 
        int last_in_qr =  std::distance(std::begin(tree[node*2]), 
                                        std::upper_bound(std::begin(tree[node*2]), 
                                                         std::end(tree[node*2]), 
                                                         query_end));
                                        
        // finds the first index in the left segment 
        // which is >= queryStart
        int first_in_qr = std::distance(std::begin(tree[node*2]), 
                                        std::lower_bound(std::begin(tree[node*2]), 
                                                         std::end(tree[node*2]), 
                                                         query_start));
        
        int M = last_in_qr - first_in_qr;
        
        if (M >= k)
        {
            // Kth smallest is in left subtree, so recursively call left subtree for Kth smallest number
            return query_tree(node*2, lo, mid, query_start, query_end, k);
        }
        else
        {
            // Kth smallest is in right subtree, so recursively call right subtree for the (K-M)th smallest number
            return query_tree(node*2+1, mid+1, hi, query_start, query_end, k - M);
        }
    }
}

int main()
{
    int n, m;
    std::scanf("%d %d", &n, &m);
    
    // vector of pairs of form {element, index} 
    std::vector<std::pair<int,int>> vec;
    vec.reserve(n);
    
    for (int i = 0; i < n; ++i)
    {
        std::scanf("%d", &arr[i]);
        vec.push_back(std::make_pair(arr[i], i));
    }
    
    std::sort(vec.begin(), vec.end());
    
    build_tree(1, 0, n-1, vec);
    
    while (m--)
    {
        int l, r, k;
        std::scanf("%d %d %d", &l, &r, &k);
        
        if (k > (r - l + 1) || l > r)
            std::printf("-1\n");
        else
        {
            int index = query_tree(1, 0, n-1, l-1, r-1, k);
        
            std::printf("%d\n", arr[index]);
        }
    }
    
    return 0;
}
