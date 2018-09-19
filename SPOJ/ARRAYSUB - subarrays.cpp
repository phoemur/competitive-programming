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
void solve(const std::vector<int>& vec, int k)
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
    solve(vec, k);
        
    return 0;
}
