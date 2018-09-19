/*ARRAYSUB - subarrays
#datastructures #sliding-window-1 #data-structure-1

Given an array and an integer k, find the maximum for each and every contiguous subarray of size k.
Input

the number n denoting number of elements in the array then after a new line we have the numbers of the array and then k in a new line

n < 10^6
k < 10^5
1 <= k <= n

and each element of the array is between 0 and 10^6

(Edited: In fact, n <= 10^5)
Output

print the output array
Example

Input:
9
1 2 3 1 4 5 2 3 6
3

Output:
3 3 4 5 5 5 6

*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

// Brute force works fine
void solve_bruteforce(const std::vector<int>& vec, int k)
{
    for (int i = 0; i < vec.size() - k + 1; ++i)
    {
        std::cout << *std::max_element(&vec[i], &vec[i+k]) << " ";
    }
}

// Solve using segment Tree
void solve_segtree(const std::vector<int>& vec, int k)
{
    const int n = vec.size();
    
    // Build segment Tree in a std::vector representation
    std::vector<int> segment_tree (2*n);
    std::copy(std::begin(vec), std::end(vec), std::begin(segment_tree) + n); // Add leaf nodes at the end first
    
    for (int i = n - 1; i > 0; --i) // Calculate parents from there
        segment_tree[i] = std::max(segment_tree[i<<1], segment_tree[i<<1 | 1]);
    
    // Query function
    auto query = [&segment_tree,n](int l, int r) 
    {
        int init = std::numeric_limits<int>::min();
        
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) 
        {
            if (l & 1) 
                init = std::max(init, segment_tree[l++]);
    
            if (r & 1) 
                init = std::max(init, segment_tree[--r]);
        }
        
        return init;
    };
    
    // Print queries
    for (int i = 0; i < n - k + 1; ++i)
        std::cout << query(i, i+k) << " ";
}

// Solve using Sparse Table Algorithm
void solve_sparsetable(const std::vector<int>& vec, int k)
{
    const int n = vec.size();
    
    // Preprocess
    std::vector<std::vector<int>> lookup (n);
    
    // Initialize M for the intervals with length 1
    for (int i = 0; i < n; i++)
        lookup[i].push_back(i);
        // lookup[i][0] = i
    
    // Compute values from smaller to bigger intervals
    for (int j=1; (1<<j)<=n; j++)
    {
        // Compute maximum value for all intervals with size 2^j
        for (int i=0; (i+(1<<j)-1) < n; i++)
        { 
            // For vec[2][10], we compare vec[lookup[0][3]] and
            // vec[lookup[3][3]]
            if (vec[lookup[i][j-1]] > vec[lookup[i + (1<<(j-1))][j-1]])
                // lookup[i][j] = lookup[i][j-1]
                lookup[i].push_back(lookup[i][j-1]);
            else
                // lookup[i][j] = lookup[i + (1 << (j-1))][j-1];
                lookup[i].push_back(lookup[i + (1 << (j-1))][j-1]);      
        }
    }
       
    // Print queries
    for (int i = 0; i < n - k + 1; ++i)
    {
        //int L = i, R = i + k;
        int j = static_cast<int>(std::log2(k));
        
        if (vec[lookup[i][j]] > vec[lookup[i + k - (1<<j)][j]])
            std::cout << vec[lookup[i][j]] << " ";
        else 
            std::cout << vec[lookup[i + k - (1<<j)][j]] << " ";
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    // Input block
    int n;
    std::cin >> n;
    
    std::vector<int> vec (n);
    std::copy_n(std::istream_iterator<int>(std::cin), n, std::begin(vec));
    
    int k;
    std::cin >> k;
    
    // solve_bruteforce(vec, k);
    // solve_sparsetable(vec, k);
    solve_segtree(vec, k);
        
    return 0;
}
