/* BINA - Binary Again
no tags 

One day I was playing card game on the computer of ACM ICPC Training Lab and my friend Istiyak was thinking something. Suddenly he said, “Munna, can you tell me whether A is divisible B or not?”.

Then I said to him, “That’s very simple! tell me A and B”. Then he said, “That’s not simple as you are thinking. I will tell you the binary of A and B”. Then he asked me that can I do it now?

I am not the man who can be defeated easily. But I also don’t know how to do it. As you are a good friend of mine. You are going to complete this task in my favor.
Input

On the first line you will be given the test case number T (T < 255).

Then for each test case you will be given two set of binary number, one on each line. Each set of binary will fit in 64 bit integers.
Output

For each test case print the test case number and print “YES” if A is divisible by B, otherwise print “NO” without quotes.
Example

Input:
3
11010
10
1111
11
111
11

Output:
Case 1: YES
Case 2: YES
Case 3: NO
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
    char buffer[65];

    int tests;
    scanf("%d", &tests);

    for (int cnt = 1; cnt <= tests; ++cnt)
    {
        scanf("%s", buffer);
        int64_t a = strtoll(buffer, NULL, 2);

        scanf("%s", buffer);
        int64_t b = strtoll(buffer, NULL, 2);

        printf("Case %d: ", cnt);
        if (b == 0)
            printf("NO\n");
        else if (a % b == 0)
            printf("YES\n");
        else
            printf("NO\n");    
    }

    return 0;
}
