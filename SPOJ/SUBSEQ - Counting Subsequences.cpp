/*SUBSEQ - Counting Subsequences
no tags 

"47 is the quintessential random number," states the 47 society. And there might be a grain of truth in that.

For example, the first ten digits of the Euler's constant are:

2 7 1 8 2 8 1 8 2 8

And what's their sum? Of course, it is 47.

Try walking around with your eyes open. You may be sure that soon you will start discovering occurences of the number 47 everywhere.
Problem specification

You are given a sequence S of integers we saw somewhere in the nature. Your task will be to compute how strongly does this sequence support the above claims.

We will call a continuous subsequence of S interesting if the sum of its terms is equal to 47.

E.g., consider the sequence S = (24, 17, 23, 24, 5, 47). Here we have two interesting continuous subsequences: the sequence (23, 24) and the sequence (47).

Given a sequence S, find the count of its interesting subsequences.
Input specification

The first line of the input file contains an integer T specifying the number of test cases. Each test case is preceded by a blank line.

The first line of each test case contains the length of a sequence N. The second line contains N space-separated integers : the elements of the sequence.
Output specification

For each test case output a single line containing a single integer : the count of interesting subsequences of the given sentence.
Example

Input:
2

13
2 7 1 8 2 8 1 8 2 8 4 5 9

7
2 47 10047 47 1047 47 47

Output:
3
4

Note: the input file will not exceed 4MB. */

#include <cstdio>
#include <map>
#include <vector>

int main()
{    
    int tests;
    std::scanf("%d", &tests);
    
    std::map<int,int> counter;
    
    while (tests--)
    {
        counter.clear();
        
        int n;
        std::scanf("%d", &n);
        
        std::vector<int> vec (n+1, 0); // Preffix sum vector
        counter[0] = 1;
        
        int res = 0;
        
        for (int i = 1; i <= n; ++i)
        {
            std::scanf("%d", &vec[i]);
            vec[i] += vec[i-1];
            counter[vec[i]]++;
            res += counter[vec[i] - 47];
        }
        
        std::printf("%d\n", res);
    }
    
    return 0;
}
