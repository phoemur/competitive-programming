/*Zonal Computing Olympiad 2012, 26 Nov 2011

It's dinner time in Castle Camelot, and the fearsome Knights of the Round Table are clamouring for dessert. You, the chef, are in a soup. There are N knights, including King Arthur, each with a different preference for dessert, but you cannot afford to make desserts for all of them.

You are given the cost of manufacturing each Knight's preferred dessert–since it is a round table, the list starts with the cost of King Arthur's dessert, and goes counter-clockwise.

You decide to pick the cheapest desserts to make, such that for every pair of adjacent Knights, at least one gets his dessert. This will ensure that the Knights do not protest.
<!--

A strange feature of the Knights is that they will not complain about not getting dessert unless they get support from both their neighbours. So, you decide to pick the cheapest desserts to make, such that for every pair of adjacent Knights, at least one gets his dessert.
-->

What is the minimum cost of tonight's dinner, given this condition?

For instance, suppose there are 5 Knights and their desserts cost 1, 2, 1, 2 and 2. In this case, the minimum cost is 4, which you can achieve by feeding the first, third and fourth (or fifth) Knights.

Input format

There are 2 lines of input. The first line contains a single integer N, the number of seats at the table. The next line contains N space separated integers, each being the cost of the dessert of a Knight, listed in counterclockwise order around the table, starting with King Arthur.

Output format

The output should be a single line containing a single integer, the minimum possible cost for you, the chef.

Testdata

Each Knight's dessert costs strictly more than 0 and strictly less than 1000. You may assume that 1 ≤ N ≤ 106. In 30% of the test cases, 1 ≤ N ≤ 103.

    Subtask 1 (30 marks)
    Subtask 2 (70 marks)


Sample Input

5
1 2 1 2 2


Sample Output

4
*/

#include <algorithm>
#include <iostream>
#include <vector>

inline long solve(const std::vector<int>& vec)
{
    const int n = vec.size();
    
    std::vector<long> dp (n, 0);
    
    // Case 1: knight 0 Must receive his desert
    // Knight n-1 may or may not receive his
    dp[0] = vec[0];
    dp[1] = vec[0] + vec[1];
    for (int i = 2; i < n; ++i)
        dp[i] = vec[i] + std::min(dp[i-1], dp[i-2]);
    
    long res1 = std::min(dp[n-1], dp[n-2]);
    
    std::fill(dp.begin(), dp.end(), 0);
    
    // Case 2: Knight n-1 must receive his desert
    // Knight 0 may or may not
    dp[n-1] = vec[n-1];
    dp[n-2] = vec[n-1] + vec[n-2];
    for (int i = n-3; i>=0; --i)
        dp[i] = vec[i] + std::min(dp[i+1], dp[i+2]);
 
    long res2 = std::min(dp[0], dp[1]);
    
    return std::min(res1, res2);
}

int main()
{
    int n;
    std::cin >> n;
    
    std::vector<int> vec (n);
    for (auto& elem : vec) std::cin >> elem;
    
    if (n == 1)
        std::cout << vec[0] << std::endl;
    else if (n == 2)
        std::cout << std::min(vec[0], vec[1]) << std::endl;
    else
        std::cout << solve(vec) << std::endl;
    
    return 0;
}
