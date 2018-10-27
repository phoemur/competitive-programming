/*All submissions for this problem are available.###Read problems statements Mandarin , Bengali , Hindi , Russian and Vietnamese as well.

There are three friends; let's call them A, B, C. They made the following statements:

    A: "I have x

Rupees more than B."
B: "I have y
rupees more than C."
C: "I have z

    rupees more than A."

You do not know the exact values of x,y,z
. Instead, you are given their absolute values, i.e. X=|x|, Y=|y| and Z=|z|. Note that x, y, z may be negative; "having −r rupees more" is the same as "having r

rupees less".

Find out if there is some way to assign amounts of money to A, B, C such that all of their statements are true.
Input

    The first line of the input contains a single integer T

denoting the number of test cases. The description of T
test cases follows.
The first and only line of each test case contains three space-separated integers X
, Y and Z

    .

Output

For each test case, print a single line containing the string "yes" if the presented scenario is possible or "no" otherwise (without quotes).
Constraints

    1≤T≤1,000

1≤X,Y,Z≤1,000

Subtasks

Subtask #1 (30 points):

    1≤T≤30

1≤X,Y,Z≤3

Subtask #2 (70 points): original constraints
Example Input

2
1 2 1
1 1 1

Example Output

yes
no

Explanation

Example 1: One possible way to satisfy all conditions is: A has 10
rupees, B has 9 rupees and C has 11 rupees. Therefore, we have x=1, y=−2, z=1

.

Example 2: There is no way for all conditions to be satisfied.*/

#include <algorithm>
#include <cstdio>

int main()
{
    int arr[3];
    int tests;
    std::scanf("%d", &tests);
    
    while (tests--)
    {
        std::scanf("%d %d %d", &arr[0], &arr[1], &arr[2]);
        
        std::sort(arr, arr+3);
        
        if (std::abs(arr[2]) - arr[1] - arr[0] == 0)
            std::printf("yes\n");
        else
            std::printf("no\n");
    }
    
    return 0;
}
