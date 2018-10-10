/*EKO - Eko
#binary-search

Lumberjack Mirko needs to chop down M metres of wood. It is an easy job for him since he has a nifty new woodcutting machine that can take down forests like wildfire. However, Mirko is only allowed to cut a single row of trees.

Mirko‟s machine works as follows: Mirko sets a height parameter H (in metres), and the machine raises a giant sawblade to that height and cuts off all tree parts higher than H (of course, trees not higher than H meters remain intact). Mirko then takes the parts that were cut off. For example, if the tree row contains trees with heights of 20, 15, 10, and 17 metres, and Mirko raises his sawblade to 15 metres, the remaining tree heights after cutting will be 15, 15, 10, and 15 metres, respectively, while Mirko will take 5 metres off the first tree and 2 metres off the fourth tree (7 metres of wood in total).

Mirko is ecologically minded, so he doesn‟t want to cut off more wood than necessary. That‟s why he wants to set his sawblade as high as possible. Help Mirko find the maximum integer height of the sawblade that still allows him to cut off at least M metres of wood.
Input

The first line of input contains two space-separated positive integers, N (the number of trees, 1 ≤ N ≤ 1 000 000) and M (Mirko‟s required wood amount, 1 ≤ M ≤ 2 000 000 000).

The second line of input contains N space-separated positive integers less than 1 000 000 000, the heights of each tree (in metres). The sum of all heights will exceed M, thus Mirko will always be able to obtain the required amount of wood.
Output

The first and only line of output must contain the required height setting.
Example

Input:
4 7
20 15 10 17

Output:
15

Input:
5 20
4 42 40 26 46

Output:
36

*/

#include <cstdio>
#include <vector>

/* This function returns true if a saw height can
 * chop at least amount of wood */
inline bool predicate(const std::vector<int>& vec,
                      const int amount,
                      const int height)
{
    long sum = 0;
    
    for (auto& tree: vec)
        if (tree > height)
            sum += tree - height;
    
    return sum >= amount;
}


inline int bs_solve(const std::vector<int>& vec, 
                    const int amount, 
                    const int great)
{
    int lo = 0;
    int hi = great - 1;
    
    while (lo < hi)
    {
        int mid = lo + (hi - lo + 1) / 2;
        
        if (predicate(vec, amount, mid))
            lo = mid;
        else
            hi = mid - 1;
    }
    
    return lo;
}

int main()
{    
    int n, m;
    std::scanf("%d%d", &n, &m);
    
    std::vector<int> vec (n);
    int great = 0;
    
    for (auto& tree: vec)
    {
        std::scanf("%d", &tree);
        great = std::max(great, tree);
    }
    
    std::printf("%d\n", bs_solve(vec, m, great));     
    
    return 0;
}
