/*Given an integer product, find the smallest positive (i.e. greater than 0) integer the product of whose digits is equal to product. If there is no such integer, return -1 instead.

Example

    For product = 12, the output should be
    digitsProduct(product) = 26;
    For product = 19, the output should be
    digitsProduct(product) = -1.

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] integer product

    Guaranteed constraints:
    0 ≤ product ≤ 600.

    [output] integer
*/

int digitsProduct(int product) {
    if (product == 0) {return 10;}
    else if (product == 1) {return 1;}
    
    std::vector<int> digits;
    int res = 0;
    
    for (int div =9; div>1; --div) {
        while (product % div == 0) {
            product /= div;
            digits.push_back(div);
        }
    }
    
    if (product > 1) {return -1;}
    for (int i = digits.size()-1; i >=0; --i) {
        res = 10 * res + digits[i];
    }
    return res;
}
