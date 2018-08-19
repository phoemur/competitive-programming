/*Construct a square matrix with a size N × N containing integers from 1 to N * N in a spiral order, starting from top-left and in clockwise direction.

Example

For n = 3, the output should be

spiralNumbers(n) = [[1, 2, 3],
                    [8, 9, 4],
                    [7, 6, 5]]

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] integer n

    Matrix size, a positive integer.

    Guaranteed constraints:
    3 ≤ n ≤ 100.

    [output] array.array.integer
*/

std::vector<std::vector<int>> spiralNumbers(int n) {
    std::vector<std::vector<int>> vec (n, std::vector<int>(n));
    
    int nCS = static_cast<int>(ceil(static_cast<double>(n)/2.0));
 	int j;
	int sideLen = n;
	int currNum = 1;
    for (int i=0; i<nCS; i++) {
		for ( j = 0; j < sideLen; j++ )
			vec[ i ][ i + j ] = currNum++;
 
		for ( j = 1; j < sideLen; j++ )
			vec[ i + j ][ n - 1 - i ] = currNum++;
 
		for ( j = sideLen - 2; j > -1; j-- )
			vec[ n - 1 - i ][ i + j ] = currNum++;
 
		for ( j = sideLen - 2; j > 0; j-- )
			vec[ i + j ][ i ] = currNum++;
 
		sideLen -= 2;
    }
    return vec;
}
