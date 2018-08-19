/*Given a string, find the number of different characters in it.

Example

For s = "cabca", the output should be
differentSymbolsNaive(s) = 3.

There are 3 different characters a, b and c.

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] string s

    A string of lowercase English letters.

    Guaranteed constraints:
    3 ≤ s.length ≤ 1000.

    [output] integer
*/

int differentSymbolsNaive(std::string s) {
    return std::set<char>(s.begin(), s.end()).size();
}
