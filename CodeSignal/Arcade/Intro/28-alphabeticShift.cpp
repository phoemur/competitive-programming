/*Given a string, replace each its character by the next one in the English alphabet (z would be replaced by a).

Example

For inputString = "crazy", the output should be
alphabeticShift(inputString) = "dsbaz".

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] string inputString

    Non-empty string consisting of lowercase English characters.

    Guaranteed constraints:
    1 ≤ inputString.length ≤ 1000.

    [output] string

    The result string after replacing all of its characters.
*/

std::string alphabeticShift(std::string i) {
    std::for_each(i.begin(), i.end(), [](char& c){
        if (c == 'z') {c = 'a';}
        else {++c;}
    });
    return i;
}
