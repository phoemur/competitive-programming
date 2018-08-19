/*Given a string, output its longest prefix which contains only digits.

Example

For inputString="123aa1", the output should be
longestDigitsPrefix(inputString) = "123".

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] string inputString

    Guaranteed constraints:
    3 ≤ inputString.length ≤ 35.

    [output] string
*/

std::string longestDigitsPrefix(std::string i) {
    auto pos = i.find_first_not_of("1234567890");
    return i.substr(0, pos);
}
