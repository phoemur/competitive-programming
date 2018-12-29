/*This is an interactive problem.

Chef has cooked N
meatballs, numbered 1 through N

. No two meatballs contain the same amount of meat. You want to eat the meatiest meatball, i.e. the meatball with the maximum amount of meat, but you do not know which one it is and Chef does not want to just give it for you. Therefore, he decided to play a game with you.

You may ask Chef at most Q=4+N/2
questions. In each question, you must give Chef the numbers of five distinct meatballs and Chef tells you the numbers of the 3-rd and 4

-th meatiest of these meatballs. Find the number of the meatiest meatball!
Interaction

    First, you should read a line containing a single integer T

denoting the number of test cases.
For each test case, you should start by reading a line containing a single integer N
.
To ask a question, you should print a line containing the character '?', a space and five space-separated integers i1
, i2, i3, i4 and i5: the numbers of five distinct meatballs (in any order). Then, you must read a line containing two space-separated integers: the numbers of the 3-rd and 4
-th meatiest meatball.
To finish solving a test case, print a line containing the character '!', a space and an integer im
: the number of the meatiest meatball (1≤im≤N

    ).

Don't forget to flush the output after printing each line!
Constraints

    1≤T≤1,000

6≤N≤100

Subtasks

Subtask #1 (60 points): Q=N+3

Subtask #2 (40 points): Q=4+N/2

(original constraints)
Example

You               Grader
                  1
                  6
? 1 2 3 4 5
                  3 4
? 1 2 3 4 6
                  3 4
? 1 2 3 5 6
                  3 5
? 1 2 4 5 6
                  4 5
? 1 3 4 5 6
                  4 5
? 2 3 4 5 6
                  4 5
! 6

Explanation

The meatballs are sorted in ascending order of meatiness.*/

#include <bits/stdc++.h>

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int n, a1, a2;
        std::cin >> n;
        
        std::vector<int> vec (n);
        std::iota(vec.begin(), vec.end(), 1);
        
        int disc[3];
        disc[0] = disc[1] = disc[2] = -1;
        
        auto up_disc = [&disc](int a){
            if (disc[0] == -1)
            {
                if (a != disc[1] && a != disc[2])
                {
                    disc[0] = a;
                    return;
                }
            }
            
            if (disc[1] == -1)
            {
                if (a != disc[0] && a != disc[2])
                {
                    disc[1] = a;
                    return;
                }
            }
            
            if (disc[2] == -1)
            {
                if (a != disc[0] && a != disc[1])
                {
                    disc[2] = a;
                    return;
                }
            }
        };
        
        while (vec.size() >= 5)
        {
            int tmp[5];
            std::copy(vec.rbegin(), vec.rbegin()+5, &tmp[0]);
            
            for (int i = 0; i < 5; ++i)
                vec.pop_back();
            
            std::cout << "?";
            for (int i = 0; i < 5; ++i)
                std::cout << " " << tmp[i];
            std::cout << std::endl;
            
            std::cin >> a1 >> a2;
            
            for (auto& elem: tmp)
                if (elem != a1 && elem != a2)
                    vec.push_back(elem);
            
            up_disc(a1);
            up_disc(a2);
                
            if (vec.size() == 4)
                vec.push_back(a1);
        }     
        
        std::pair<int,int> p1, p2, p3;
        
        std::cout << "? " << vec[0] << " " << vec[1] << " " << disc[0] << " " << disc[1] << " " << disc[2] << std::endl;
        std::cin >> p1.first >> p1.second;
        if (p1.first > p1.second) std::swap(p1.first, p1.second);
        
        std::cout << "? " << vec[1] << " " << vec[2] << " " << disc[0] << " " << disc[1] << " " << disc[2] << std::endl;
        std::cin >> p2.first >> p2.second;
        if (p2.first > p2.second) std::swap(p2.first, p2.second);
        
        std::cout << "? " << vec[0] << " " << vec[2] << " " << disc[0] << " " << disc[1] << " " << disc[2] << std::endl;
        std::cin >> p3.first >> p3.second;
        if (p3.first > p3.second) std::swap(p3.first, p3.second);
        
        
        if (p1 == p2)
            std::cout << "! " << vec[1] << std::endl;
        else if (p1 == p3)
            std::cout << "! " << vec[0] << std::endl;
        else
            std::cout << "! " << vec[2] << std::endl;
    }
    
    return 0;
}
