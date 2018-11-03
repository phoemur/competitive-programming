/*TAP2013G - War
no tags 

[The original version of this problem (in Spanish) can be found at http://www.dc.uba.ar/events/icpc/download/problems/tap2013-problems.pdf]

War, an event worthy only of appearance in literature, movies or perhaps programming contests, has reached the Nlogonian empire, which is facing the neighboring empire of Quadradonia.

War protocols agreed upon by both parties indicate that the war will be waged in successive battles, in each of which a different soldier from each empire will face one another, so that each soldier will take part in exactly one battle. The empire that wins more battles will then win the war.

Each empire has an army formed by S soldiers, and each soldier has a certain combat skill. In each battle between two soldiers, the one with greatest combat skill wins the battle. If both soldiers have the same combat skills, the battle is declared a draw and technically no side claims victory. The spies of Nlogonia have intercepted secret information concerning the combat skill of each soldier of Quadradonia's army, so Nlogonia's queen requires your assistance in order to calculate the maximum number of battles that can be won during the war if her soldiers are sent in the appropriate order.

 
Input

The first line contains an integer number S representing the number of soldiers in each army (1 ≤ S ≤ 105). The second line contains S integer numbers Qi representing the combat skills of the different soldiers of Quadradonia's army, in the order in which the battles shall take place (1 ≤ Qi ≤ 109 for i = 1, ..., S). The third line contains S integer numbers Ni representing the combat skills of the different soldiers in Nlogonia's army, in an arbitrary order (1 ≤ Ni ≤ 109 for i = 1, ..., S).

 
Output

Print a line containing a single integer number representing the maximum number of battles that Nlogonia can win during the war.

 
Example 1

Input:
3
2 1 1000000000
1 1 2

Output:
1

Example 2

Input:
4
6 3 1 4
2 7 4 3

Output:
3
*/

#include <algorithm>
#include <cstdio>
#include <vector>

int main()
{
    // Input
    int n;
    std::scanf("%d", &n);
    
    std::vector<int> Q (n);
    std::vector<int> N (n);
    
    for (int i = 0; i < n; ++i) std::scanf("%d", &Q[i]);
    for (int i = 0; i < n; ++i) std::scanf("%d", &N[i]);
    
    // Sort
    std::sort(Q.begin(), Q.end());
    std::sort(N.begin(), N.end());
    
    // 2 pointers solve
    int res   = 0;
    int ptr_q = 0;
    int ptr_n = 0;
    
    while (ptr_q < n && ptr_n < n)
    {
        if (N[ptr_n] <= Q[ptr_q])
            ++ptr_n;
        else
        {
            ++res;
            ++ptr_q;
            ++ptr_n;
        }
    }
    
    std::printf("%d\n", res);
    
    return 0;
}
