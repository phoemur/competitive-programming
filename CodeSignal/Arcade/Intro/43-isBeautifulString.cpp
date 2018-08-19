/*A string is said to be beautiful if b occurs in it no more times than a; c occurs in it no more times than b; etc.

Given a string, check whether it is beautiful.

Example

    For inputString = "bbbaacdafe", the output should be
    isBeautifulString(inputString) = true;
    For inputString = "aabbb", the output should be
    isBeautifulString(inputString) = false;
    For inputString = "bbc", the output should be
    isBeautifulString(inputString) = false.

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] string inputString

    A string of lowercase letters.

    Guaranteed constraints:
    3 ≤ inputString.length ≤ 50.

    [output] boolean

*/

bool isBeautifulString(const std::string& i) {
    std::size_t count = std::count(i.begin(), i.end(), 'a');
    for (char tmp='b'; tmp <= 'z'; ++tmp) {
        std::size_t c = std::count(i.begin(), i.end(), tmp);
        if (c > count) {return false;}
        else {count = c;}
    }
    return true;
}
