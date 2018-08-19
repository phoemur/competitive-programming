/*Ticket numbers usually consist of an even number of digits. A ticket number is considered lucky if the sum of the first half of the digits is equal to the sum of the second half.

Given a ticket number n, determine if it's lucky or not.

Example

    For n = 1230, the output should be
    isLucky(n) = true;
    For n = 239017, the output should be
    isLucky(n) = false.

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] integer n

    A ticket number represented as a positive integer with an even number of digits.

    Guaranteed constraints:
    10 ≤ n < 106.

    [output] boolean

    true if n is a lucky ticket number, false otherwise.

*/

bool isLucky(int n) {
    std::string test = std::to_string(n);
    std::size_t pos = test.size() / 2;
    
    int lhs = 0;
    int rhs = 0;
    
    for (int i = 0; i < pos; ++i) {
        lhs += (test[i] - '0');
        rhs += (*(test.end()-1-i) - '0');
    }
    return lhs == rhs;
}
