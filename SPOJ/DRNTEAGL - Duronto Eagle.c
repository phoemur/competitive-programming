/* DRNTEAGL - Duronto Eagle
#geometry

During his study in Amazing International University-Bangladesh Kazi Hossain accidentally made a space ship while doing a course assignment. He named the space ship Duronto Eagle. Now he wants to travel to other habitable planets in the galaxy with Duronto Eagle. As Kazi is a very brave guy he wants to start his space journey by travelling to the farthest planet in the galaxy first.

The co-ordinate of the planet Kazi is currently in (planet Earth) is always (0, 0). You are given the co-ordinates of the other N habitable planets in the galaxy in a 2D Cartesian plane. You have to find the index of the farthest planet considering the Euclidean distance from planet Earth (0, 0). Indices range from 1 to N.
Input

Input starts with an integer T (≤ 100), denoting the number of test cases. Each of the test cases starts with an integer N (1 ≤ N ≤ 50), denoting the number of planets. Each of the next N lines contains two integers xi yi (-10000 ≤ xi, yi ≤ 10000) describing the coordinates of the planets in the galaxy.
Output

For each case print the case number and the index of the farthest planet from Earth that Kazi will be travelling first. If there’s multiple possible answers output the one that comes first in the input. See sample input output for clarification.
Example

Input:
2
3
4 0
0 5
2 2
4
2 3
1 1
5 5
-4 -1

Output:
Case 1: 2
Case 2: 3
*/

#include <stdio.h>
#include <math.h>

int main(int argc, char** argv)
{
    int cases;
    scanf("%d", &cases);

    for (int i = 1; i <= cases; ++i)
    {
        int planets;
        scanf("%d", &planets);
        double max_dist = 0.0;
        int best = 0;

        for (int j = 1; j <= planets; ++j)
        {
            int a, b;
            double dist = 0.0;

            scanf("%d %d", &a, &b);

            dist = a*a + b*b;
            dist = sqrt(dist);

            if (dist > max_dist)
            {
                max_dist = dist;
                best = j;
            }
        }


        printf("Case %d: %d\n", i, best);
    }

    return 0;
}

