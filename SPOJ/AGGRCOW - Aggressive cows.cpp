/*AGGRCOW - Aggressive cows
#binary-search

Farmer John has built a new long barn, with N (2 <= N <= 100,000) stalls. The stalls are located along a straight line at positions x1,...,xN (0 <= xi <= 1,000,000,000).

His C (2 <= C <= N) cows don't like this barn layout and become aggressive towards each other once put into a stall. To prevent the cows from hurting each other, FJ wants to assign the cows to the stalls, such that the minimum distance between any two of them is as large as possible. What is the largest minimum distance?
Input

t – the number of test cases, then t test cases follows.
* Line 1: Two space-separated integers: N and C
* Lines 2..N+1: Line i+1 contains an integer stall location, xi
Output

For each test case output one integer: the largest minimum distance.
Example

Input:

1
5 3
1
2
8
4
9

Output:

3

Output details:

FJ can put his 3 cows in the stalls at positions 1, 4 and 8,
resulting in a minimum distance of 3.*/


#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

/* This function returns true if the cows number can be assigned to stalls
 * with a certain minimun distace */
bool predicate(const std::vector<int>& stalls, int cows, int distance)
{
    int num_cows = 1, pos = stalls[0];
    
    for (std::size_t i = 1; i < stalls.size(); ++i)
    {
        if (stalls[i] - pos >= distance)
        {
            pos = stalls[i];
            ++num_cows;
            
            if (num_cows == cows)
                return true;
        }
    }
    
    return false;
}

/* This function returns the greatest minimum distance between 
 * cows given a certain stalll placement */
int bs_solve(const std::vector<int>& stalls, int cows)
{
    int lo = 0;
    int hi = stalls.back();
    
    while (lo < hi)
    {
        int mid = lo + (hi - lo + 1) / 2;
        
        if (predicate(stalls, cows, mid))
            lo = mid;
        else
            hi = mid -1;
    }
    
    return lo;
}

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int n, c;
        std::cin >> n >> c;
        
        std::vector<int> stalls (n);
        std::copy_n(std::istream_iterator<int>(std::cin), n, std::begin(stalls));
        std::sort(std::begin(stalls), std::end(stalls));
        
        std::cout << bs_solve(stalls, c) << std::endl;
    }
    
    return 0;
}
