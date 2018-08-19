/*Given the positions of a white bishop and a black pawn on the standard chess board, determine whether the bishop can capture the pawn in one move.

The bishop has no restrictions in distance for each move, but is limited to diagonal movement. Check out the example below to see how it can move:

Example

    For bishop = "a1" and pawn = "c3", the output should be
    bishopAndPawn(bishop, pawn) = true.

    For bishop = "h1" and pawn = "h3", the output should be
    bishopAndPawn(bishop, pawn) = false.

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] string bishop

    Coordinates of the white bishop in the chess notation.

    [input] string pawn

    Coordinates of the black pawn in the same notation.

    [output] boolean

    true if the bishop can capture the pawn, false otherwise.
*/

bool bishopAndPawn(std::string bishop, std::string pawn) {
    const int b[2] {bishop[0]-'A', bishop[1] - '1'};
    const int p[2] {pawn[0]-'A', pawn[1] - '1'};
    
    if (b[0]+p[1] == p[0]+b[1] || b[0]+b[1] == p[0]+p[1]) {
        return true;
    }
    return false;
}
