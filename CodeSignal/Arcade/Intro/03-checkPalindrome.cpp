/*
Given the string, check if it is a palindrome.

Example

    For inputString = "aabaa", the output should be
    checkPalindrome(inputString) = true;
    For inputString = "abac", the output should be
    checkPalindrome(inputString) = false;
    For inputString = "a", the output should be
    checkPalindrome(inputString) = true.

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] string inputString

    A non-empty string consisting of lowercase characters.

    Guaranteed constraints:
    1 ≤ inputString.length ≤ 105.

    [output] boolean

    true if inputString is a palindrome, false otherwise.
*/

template<typename T>
std::enable_if_t<std::is_convertible<T, std::string>::value, bool>
checkPalindrome(T x) {
    return std::equal(x.begin(), x.begin() + x.size() / 2, x.rbegin());
}
