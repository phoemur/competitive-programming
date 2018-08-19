/*Given two strings, find the number of common characters between them.

Example

For s1 = "aabcc" and s2 = "adcaa", the output should be
commonCharacterCount(s1, s2) = 3.

Strings have 3 common characters - 2 "a"s and 1 "c".

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] string s1

    A string consisting of lowercase English letters.

    Guaranteed constraints:
    1 ≤ s1.length ≤ 15.

    [input] string s2

    A string consisting of lowercase English letters.

    Guaranteed constraints:
    1 ≤ s2.length ≤ 15.

    [output] integer
*/

int commonCharacterCount(std::string s1, std::string s2) {
    int count = 0;
    for (auto& c: s1) {
        auto pos = s2.find_first_of(c);
        
        if (pos != string::npos) {
            ++count;
            s2.erase(s2.begin()+pos);
        }
    }
    return count;
}
