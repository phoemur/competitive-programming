/*You are given an array of desired filenames in the order of their creation. Since two files cannot have equal names, the one which comes later will have an addition to its name in a form of (k), where k is the smallest positive integer such that the obtained name is not used yet.

Return an array of names that will be given to the files.

Example

For names = ["doc", "doc", "image", "doc(1)", "doc"], the output should be
fileNaming(names) = ["doc", "doc(1)", "image", "doc(1)(1)", "doc(2)"].

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] array.string names

    Guaranteed constraints:
    5 ≤ names.length ≤ 15,
    1 ≤ names[i].length ≤ 15.

    [output] array.string
*/

bool find_back(std::string s, int i, auto& names) {
    return std::find(names.begin(),names.begin()+i,s) != names.begin()+i;
}

std::vector<std::string> fileNaming(std::vector<std::string> names) {    
    for (std::vector<std::string>::size_type i = 1;
                                  i < names.size();
                                                ++i) {
        if (find_back(names[i], i, names)){
            for (int j = 1; j<= names.size(); ++j) {
                std::string base;
                base = names[i] + '(' + to_string(j) + ')';
                if (!find_back(base, i, names)) {
                    names[i] = base;
                    break;
                }
            }
        }
    }
    return names;
}
