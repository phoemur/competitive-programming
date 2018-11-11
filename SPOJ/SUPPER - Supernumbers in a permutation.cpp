/*SUPPER - Supernumbers in a permutation
no tags 

An n-element permutation is an n-element sequence of distinct numbers from the set {1, 2, ...,n}. For example the sequence 2,1,4,5,3 is a 5-element permutation. We are interested in the longest increasing subsequences in a permutation. In this exemplary permutation they are of length 3 and there are exactly 2 such subsequences: 2,4,5 and 1,4,5. We will call a number belonging to any of the longest increasing subsequences a supernumber. In the permutation 2,1,4,5,3 the supernumbers are 1,2,4,5 and 3 is not a supernumber. Your task is to find all supernumbers for a given permutation.
Task

Write a program which

    reads a permutation from standard input,
    finds all its supernumbers,
    writes all found numbers to standard output.

Input

Ten test cases (given one under another, you have to process all!). Each test case consists of two lines. In the first line there is a number n (1<=n<=100000). In the second line: an n-element permutation - n numbers separated by single spaces.
Output

For every test case your program should write two lines. In the first line - the number of supernumbers in the input permutation. In the second line the supernumbers separated by single spaces in increasing order.
Example

Input:
5
2 1 4 5 3
[and 9 test cases more]

Output:
4
1 2 4 5
[and 9 test cases more]

Warning: large Input/Output data, be careful with certain languages
*/

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

#define MAXN 100005

int tree[MAXN << 2]; 
int  arr[MAXN]; 
int  LIS[MAXN]; 
int  LDS[MAXN];

// Point update
inline void update(int node, int lo, int hi, int idx, int value) {
    if (lo > hi || lo > idx || hi < idx)
        return;
    else if(lo == hi)
        tree[node] = value;
    else
    {
        int mid = (lo + hi) / 2;
        
        if (idx <= mid)
            update(node*2,      lo, mid, idx, value);
        else
            update(node*2+1, mid+1,  hi, idx, value);
        
        tree[node] = std::max(tree[node*2], tree[node*2+1]);
    }
}

// Range query
inline int query(int node, int lo, int hi, int i, int j)
{
    if (lo > hi || lo > j || hi < i)
        return 0;
    else if (lo >= i && hi <= j)
        return tree[node];
    else
    {
        int mid = (lo + hi) / 2;
        int q1 = query(node*2,      lo, mid, i, j);
        int q2 = query(node*2+1, mid+1,  hi, i, j);
        
        return std::max(q1, q2);
    }
}

int main() 
{
    for (int t = 1; t <= 10; ++t)
    {
        int n;
        std::cin >> n;

        std::memset(tree, 0, sizeof(tree));

        // Make LIS array
        int maxi = 1;
        for(int i = 1 ; i <= n ; ++ i) 
        {
            std::cin >> arr[i];
            LIS[i] = 1 + query(1, 1, n, 1, arr[i]);
            update(1, 1, n, arr[i], LIS[i]);
            maxi = std::max(maxi, LIS[i]);
        }
        
        std::memset(tree, 0, sizeof(tree));

        //  Make LDS array
        for(int i = n ; i ; -- i) 
        {
            LDS[i] = 1 + query(1, 1, n, arr[i], n);
            update(1, 1, n, arr[i], LDS[i]);
        }
        
        // Result storage
        std::vector <int> ans;

        for(int i = 1 ; i <= n ; ++ i)
            if(LIS[i] + LDS[i] - 1 == maxi)
                ans.push_back(arr[i]);
            
        std::sort(ans.begin(), ans.end());

        std::cout << ans.size() << "\n";

        for(int i = 0 ; i < ans.size() ; ++ i)
            if(i != ans.size() - 1)
                std::cout << ans[i] << ' ';
            else
                std::cout << ans[i];

        std::cout << '\n';
    }
}
