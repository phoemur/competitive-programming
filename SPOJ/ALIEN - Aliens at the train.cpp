/*ALIEN - Aliens at the train
#sliding-window-1

The aliens have arrived to Earth and everything is in harmony, the two races can live together. However, one specific Female Alien does not want to see humans on her way to the university, the alien must use the train as every human does. But she can choose any train station such she doesn’t see more than B humans, however, the Alien wants to go as far as possible with the train. Please, help her in this task.
Input

You will receive one integer T denoting the number of test cases, then, the next line will contain two integers At Bt where At and Bt is the number of stations in the train (1 <= At <= 100,000) and the number of people that the alien wants to see as maximum (1 <= Bt <= 10,000,000), after that, one line containing At integers separated by a single space will denote the number of people the Alien can find in the At-i-th station. (For each station there will be as much 100 people)
Output

Your output should consist on T pair of numbers denoting the number of people the alien will see and the number of stations she will pass respectively.
Example

INPUT:
1
5 100
20 15 30 80 100

OUTPUT
65 3

Output note:
The alien takes the train at station 1 (with 20 people) and goes to station 2, then the 3rd station, at this point, she have seen 65 people, if she decides to go to station 4 she will see 145 people… Then she exits the station.

The alien, however, can start at station 2 with 15 people, then continue up to the 4th station, then, she would have seen 125 people, but, as she wants to see the minimum people possible and this number of people exceeds what she wants to see, she decides to choose the way from the 1st to the 3rd station.

Clarification: The alien will be moving always forward (remember, she can choose any station as a start), NEVER backwards, and you should choose the best path that satisfies the output specification.
*/

#include <cstdio>

int arr[100001];

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
