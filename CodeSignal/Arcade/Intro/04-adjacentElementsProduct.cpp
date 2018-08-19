/*
Given an array of integers, find the pair of adjacent elements that has the largest product and return that product.

Example

For inputArray = [3, 6, -2, -5, 7, 3], the output should be
adjacentElementsProduct(inputArray) = 21.

7 and 3 produce the largest product.

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] array.integer inputArray

    An array of integers containing at least two elements.

    Guaranteed constraints:
    2 ≤ inputArray.length ≤ 10,
    -1000 ≤ inputArray[i] ≤ 1000.

    [output] integer

    The largest product of adjacent elements.
*/

template<typename T>
std::enable_if_t<std::is_arithmetic<T>::value, T>
adjacentElementsProduct(std::vector<T> inputArray) {
    std::adjacent_difference(begin(inputArray), 
                             end(inputArray),
                             begin(inputArray),
                             std::multiplies<T>());
    return *(std::max_element(inputArray.begin()+1, inputArray.end()));
}
