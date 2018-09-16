/*OFFSIDE - He is offside!
no tags 

Hemisphere Network is the largest television network in Tumbolia, a small country located east of South America (or south of East America). The most popular sport in Tumbolia, unsurprisingly, is soccer; many games are broadcast every week in Tumbolia.

Hemisphere Network receives many requests to replay dubious plays; usually, these happen when a player is deemed to be offside by the referee. An attacking player is offside if he is nearer to his opponents’ goal line than the second last opponent. A player is not offside if

    he is level with the second last opponent or

    he is level with the last two opponents. 

Through the use of computer graphics technology, Hemisphere Network can take an image of the field and determine the distances of the players to the defending team’s goal line, but they still need a program that, given these distances, decides whether a player is offside.
Input

The input file contains several test cases. The first line of each test case contains two integers A and D separated by a single space indicating, respectively, the number of attacking and defending players involved in the play (2 <= A,D <= 11). The next line contains A integers Bi separated by single spaces, indicating the distances of the attacking players to the goal line (1 <= Bi <= 104). The next line contains D integers Cj separated by single spaces, indicating the distances of the defending players to the goal line (1 <= Cj <= 104). The end of input is indicated by A = D = 0.
Output

For each test case in the input print a line containing a single character: “Y” (uppercase) if there is an attacking player offside, and “N” (uppercase) otherwise.
Example

Input:
2 3
500 700
700 500 500
2 2
200 400
200 1000
3 4
530 510 490
480 470 50 310
0 0

Output:
N
Y
N

*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    for (int a, d; std::cin >> a >> d && (a != 0 || d != 0);)
    {
        std::vector<int> att (a);
        std::vector<int> def (d);
        
        // Input
        std::copy_n(std::istream_iterator<int>(std::cin), a, std::begin(att));
        std::copy_n(std::istream_iterator<int>(std::cin), d, std::begin(def));
        
        // Find most forward attacker
        int at = *std::min_element(std::begin(att), std::end(att));
        
        // Find number of deffending players closer to the goal 
        int res = std::count_if(std::begin(def), std::end(def), [at](int a){return a <= at;});
        
        // Output
        std::cout << (res > 1 ? "N\n" : "Y\n");
    }
    
    return 0;
}
