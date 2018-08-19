/*Write a function that returns the sum of two numbers.

Example

For param1 = 1 and param2 = 2, the output should be
add(param1, param2) = 3.

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] integer param1

    Guaranteed constraints:
    -1000 ≤ param1 ≤ 1000.

    [input] integer param2

    Guaranteed constraints:
    -1000 ≤ param2 ≤ 1000.

    [output] integer

    The sum of the two inputs.
*/

#include <bits/stdc++>
using namespace std;

template<typename T, typename = void>
struct has_add : std::false_type {};

template<typename T>
struct has_add<T, 
    std::void_t<decltype((std::declval<T&>()) + (std::declval<T&>()))>>
        : std::true_type {};

template<typename T>
std::enable_if_t<has_add<T>::value, T>
add(T param1, T param2) {
    return param1 + param2;
}
