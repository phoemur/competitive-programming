/*OLOLO - Onotole needs your help
#ad-hoc-1

	

Onotole has a lot of pyani. Each pyani has a number, writing on it. Pyanis with equal numbers are indistinguishable. Onotole knows everything, so, he knows that each pyani appeared twice, and only one pyani is unique. He wants to get вздръжни эффект, and he needs the unique pyani. Given the list of pyanis denote which one of them appeared once (it is guaranteed that other pyanis appeared twice).
Input

First line of input contains number of pyanis N <= 500 000. Next N lines contain a single positive integer 1 <= Pi <= 10^9.
Output

Output one positive integer on pyani, which appeared once.
Example

Input:
3
1
8
1

Output:
8

Onotole has found not optimal AC algorithms, so all solutions will be rejudged. He is watching you.
*/

#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    long res = 0;
    int n;
    std::cin >> n;
    while (n--)
    {
        long num;
        std::cin >> num;
        
        res ^= num;
    }
    
    std::cout << res << std::endl;
    
    return 0;
}
