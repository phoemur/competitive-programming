/*CODFURY - Megatron and his rage
#sliding-window-1

 
Infuriated by the Decepticons' defeat after a long epic battle with the Autobots, Megatron, in his rage, has decided to destroy all the planets on his way back to Cybertron from Earth. There are multiple planets between Earth and Cybertron, and each planet has some number of Autobots to guard it from him. Since Megatron is low on ammo, he wants to fight as few autobots as possible (in fact, not more than "M" of them ) on his way back.
You need to find the maximum number of planets he can possibly destroy in his journey.
NOTE: Megatron can start his "destruction spree" from any planet, and can only move to the next planet from the planet he's currently on.

Infuriated by the Decepticons' defeat after a long epic battle with the Autobots, Megatron, in his rage, has decided to destroy all the planets on his way back to Cybertron from Earth. There are multiple planets between Earth and Cybertron, and each planet has some number of Autobots to guard it from him. Since Megatron is low on ammo, he wants to fight as few autobots as possible on his way back.He can defeat no more than "M" autobots in total.

You need to find the maximum number of planets he can possibly destroy in his journey.

 

NOTE: Megatron can start his "destruction spree" from any planet, and can only move to the next planet from the planet he's currently on.

 
Input

You will receive one integer "T" denoting the number of test cases. (T<=20)

Then, the next line will contain two non-negative space-separated integers "P" and "M", where P is the number of planets on his way back (P<=50000) and M is the maximum number of Autobots that Megatron can see (M<=1000,000).

After that, one line containing P integers separated by a single space will denote the number of Autobots present in each planet. (For each planet there will be no more than 1000 autobots).
Output

Your output should consist of "T" pairs of space-separated integers, one pair per line, denoting the number of Autobots Megatron will fight and the number of planets he will destroy respectively.
Example

Input:
1
4 50
20 5 23 45

Output:
48 3

EXPLANATION : 

Megatron starts at planet 1 (with 20 Autobots) and goes to planet 2, then the 3rd planet, 

at this point, he has seen 48 Autobots, if he decides to go to planet 4 he will see 93 Autobots…

so he stops his journey at the 3rd planet.

Megatron, however, could have started at planet 2 with 5 Autobots, then continue up to the 4th planet, then, 

he would have seen 73 Autobots, but, as he wants to see the minimum Autobots possible and 

this number of Autobots exceeds what he wants to see, he decides to choose the way from the 1st to the 3rd planet.

*/

#include <cstdio>

int arr[50001];

template<typename T>
inline T minimum(T t1, T t2)
{
    return t1 < t2 ? t1: t2;
}

int main()
{
    int tests;
    std::scanf("%d", &tests);
    
    while (tests--)
    {
        int p, m;
        std::scanf("%d %d", &p, &m);
        
        // Input
        for (int i = 0; i < p; ++i)
            std::scanf("%d", &arr[i]);
        
        // Solve using 2 pointers technique
        int slow = 0, fast = 0, sum = 0, res = 0, sum_res = 0;
        
        while (fast < p)
        {
            sum += arr[fast];
            ++fast;
            
            while (sum > m && slow < p)
            {
                sum -= arr[slow];
                ++slow;
            }
            
            if (res < fast - slow) // New best, update all
            {
                res = fast - slow;
                sum_res = sum;
            }
            else if (res == fast - slow) // Equal best, minimize sum
            {
                sum_res = minimum(sum_res, sum);
            }
        }
        
        std::printf("%d %d\n", sum_res, res);
    }
    
    return 0;
}
