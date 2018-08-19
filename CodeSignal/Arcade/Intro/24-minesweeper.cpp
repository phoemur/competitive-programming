/*In the popular Minesweeper game you have a board with some mines and those cells that don't contain a mine have a number in it that indicates the total number of mines in the neighboring cells. Starting off with some arrangement of mines we want to create a Minesweeper game setup.

Example

For

matrix = [[true, false, false],
          [false, true, false],
          [false, false, false]]

the output should be

minesweeper(matrix) = [[1, 2, 1],
                       [2, 1, 1],
                       [1, 1, 1]]

Check out the image below for better understanding:

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] array.array.boolean matrix

    A non-empty rectangular matrix consisting of boolean values - true if the corresponding cell contains a mine, false otherwise.

    Guaranteed constraints:
    2 ≤ matrix.length ≤ 100,
    2 ≤ matrix[0].length ≤ 100.

    [output] array.array.integer

    Rectangular matrix of the same size as matrix each cell of which contains an integer equal to the number of mines in the neighboring cells. Two cells are called neighboring if they share at least one corner.
*/

bool isInside(std::vector<std::vector<bool>> &matrix, int i, int j){
    if( i < 0 or j < 0 or i > matrix.size()-1 or j > matrix[0].size()-1)
        return false;
    return true;
}

int getSum(std::vector<std::vector<bool>> &matrix, int i, int j){
    int sum = 0;
    for (int i2 = -1; i2 < 2; ++i2){
        for(int j2 = -1; j2 <2; ++j2){
            if(i2 != j2 or i2 != 0 or j2 !=0)
            if(isInside(matrix, i+i2, j+j2) and matrix[i+i2][j+j2]){
                sum+=1;
            }
        }
    }
    return sum;
}


auto minesweeper(std::vector<std::vector<bool>> matrix) {
    std::vector<std::vector<int>> r (matrix.size(), 
                                     std::vector<int> (matrix[0].size()));   
    for (int i=0; i<matrix.size(); ++i) {
        for (int j=0; j<matrix[0].size(); ++j) {
            r[i][j] = getSum(matrix, i, j); 
        }
    }
    return r;
}
