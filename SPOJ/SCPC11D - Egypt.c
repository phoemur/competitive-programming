/* SCPC11D - Egypt
no tags 

A long time ago, the Egyptians figured out that a triangle with sides of length 3, 4, and 5 had a right angle as its largest angle. You must determine if other triangles have a similar property.
Input

Input represents several test cases, followed by a line containing 0 0 0. Each test case has three positive integers, less than 30,000, denoting the lengths of the sides of a triangle.
Output

For each test case, a line containing "right" if the triangle is a right triangle, and a line containing "wrong" if the triangle is not a right triangle.
Example

Input:
6 8 10
25 52 60
6 8 10
25 52 60
5 12 13
0 0 0
5 12 13
0 0 0

Output:
right
wrong
right
*/

#include <stdio.h>
#include <math.h>

void swap(double* a, double* b)
{
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(int argc, char** argv)
{
    double t[3];

    while (1)
    {
        // Read
        scanf("%lf %lf %lf", &t[0], &t[1], &t[2]);
        
        // Check break
        if (t[0] == 0.0)
            if (t[1] == 0.0)
                if (t[2] == 0.0)
                    break;
        // Sort
        if (t[0] > t[2]) swap(&t[0], &t[2]);
        if (t[0] > t[1]) swap(&t[0], &t[1]);
        if (t[1] > t[2]) swap(&t[1], &t[2]);

        // Result
        if (hypot(t[0], t[1]) == t[2])
            printf("right\n");
        else
            printf("wrong\n");
    }

    return 0;
}
