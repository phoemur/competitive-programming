/*Find the leftmost digit that occurs in a given string.

Example

    For inputString = "var_1__Int", the output should be
    firstDigit(inputString) = '1';
    For inputString = "q2q-q", the output should be
    firstDigit(inputString) = '2';
    For inputString = "0ss", the output should be
    firstDigit(inputString) = '0'.

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] string inputString

    A string containing at least one digit.

    Guaranteed constraints:
    3 ≤ inputString.length ≤ 10.

    [output] char
*/

char firstDigit(std::string i) {
    return i[i.find_first_of("0123456789")];
}
