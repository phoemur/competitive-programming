/*Check if all digits of the given integer are even.

Example

    For n = 248622, the output should be
    evenDigitsOnly(n) = true;
    For n = 642386, the output should be
    evenDigitsOnly(n) = false.

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] integer n

    Guaranteed constraints:
    1 ≤ n ≤ 109.

    [output] boolean

    true if all digits of n are even, false otherwise.
*/

bool evenDigitsOnly(int n) 
{
    std::string s {std::to_string(n)};
    return std::all_of(s.begin(), s.end(), [](const char& a){
                           return (a - '0') % 2 == 0;
                       });
}
