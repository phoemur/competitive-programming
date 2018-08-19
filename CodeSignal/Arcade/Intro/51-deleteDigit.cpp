/*Given some integer, find the maximal number you can obtain by deleting exactly one digit of the given number.

Example

    For n = 152, the output should be
    deleteDigit(n) = 52;
    For n = 1001, the output should be
    deleteDigit(n) = 101.

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] integer n

    Guaranteed constraints:
    10 ≤ n ≤ 106.

    [output] integer
*/

int deleteDigit(int n) {
    int res = 0;
    for (std::size_t i=0;
         i < 1+std::floor(std::log10(n)); 
         ++i) {
        std::string tmp {std::to_string(n)};
        tmp.erase(tmp.begin()+i);
        auto r = std::stol(tmp);
        if (r >= res) {res = r;}
    }
    return res;
}
