/*JULKA - Julka
#big-numbers

Julka surprised her teacher at preschool by solving the following riddle:

Klaudia and Natalia have 10 apples together, but Klaudia has two apples more than Natalia. How many apples does each of he girls have?

Julka said without thinking: Klaudia has 6 apples and Natalia 4 apples. The teacher tried to check if Julka's answer wasn't accidental and repeated the riddle every time increasing the numbers. Every time Julka answered correctly. The surprised teacher wanted to continue questioning Julka, but with big numbers she could't solve the riddle fast enough herself. Help the teacher and write a program which will give her the right answers.
Task

Write a program which

    reads from standard input the number of apples the girls have together and how many more apples Klaudia has,
    counts the number of apples belonging to Klaudia and the number of apples belonging to Natalia,
    writes the outcome to standard output

Input

Ten test cases (given one under another, you have to process all!). Every test case consists of two lines. The first line says how many apples both girls have together. The second line says how many more apples Klaudia has. Both numbers are positive integers. It is known that both girls have no more than 10100 (1 and 100 zeros) apples together. As you can see apples can be very small.
Output

For every test case your program should output two lines. The first line should contain the number of apples belonging to Klaudia. The second line should contain the number of apples belonging to Natalia.
Example

Input:
10
2
[and 9 test cases more]

Output:
6
4
[and 9 test cases more]

*/

#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>


int main()
{
    using namespace boost::multiprecision;
    
    for (int n = 0; n < 10; ++n)
    {
        cpp_int a, b, c;
        
        if (std::cin >> a >> b)
        {
            c = (a - b) / 2;
            std::cout << c + b << "\n" << c << std::endl;
        }
    }
    
    return 0;
}
