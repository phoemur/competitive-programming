/*TOANDFRO - To and Fro
#ad-hoc-1

Mo and Larry have devised a way of encrypting messages. They first decide secretly on the number of columns and write the message (letters only) down the columns, padding with extra random letters so as to make a rectangular array of letters. For example, if the message is “There’s no place like home on a snowy night” and there are five columns, Mo would write down

t o i o y
h p k n n
e l e a i
r a h s g
e c o n h
s e m o t
n l e w x

Note that Mo includes only letters and writes them all in lower case. In this example, Mo used the character ‘x’ to pad the message out to make a rectangle, although he could have used any letter. Mo then sends the message to Larry by writing the letters in each row, alternating left-to-right and right-to-left. So, the above would be encrypted as

toioynnkpheleaigshareconhtomesnlewx

Your job is to recover for Larry the original message (along with any extra padding letters) from the encrypted one.
Input

There will be multiple input sets. Input for each set will consist of two lines. The first line will contain an integer in the range 2...20 indicating the number of columns used. The next line is a string of up to 200 lower case letters. The last input set is followed by a line containing a single 0, indicating end of input.
Output

Each input set should generate one line of output, giving the original plaintext message, with no spaces.
Example

Input:

5
toioynnkpheleaigshareconhtomesnlewx
3
ttyohhieneesiaabss
0

Output:

theresnoplacelikehomeonasnowynightx
thisistheeasyoneab

*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

inline void output(const std::vector<std::string>& matrix)
{
    for (std::size_t j = 0; j < matrix[0].size(); ++j)
        for (std::size_t i = 0; i < matrix.size(); ++i)
            std::cout << matrix[i][j];
        
    std::cout << std::endl;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int cols;
    
    while (std::cin >> cols && cols != 0)
    {
        std::vector<std::string> matrix;
        std::string input;
        std::cin >> input;
        
        int i = 0;
        for (auto it = input.begin(); it != input.end(); std::advance(it, cols), ++i)
        {            
            matrix.emplace_back(it, it + cols);
            
            if (i & 1)
                std::reverse(matrix.back().begin(), matrix.back().end());
        }
        
        output(matrix);
    }
    
    return 0;
}
