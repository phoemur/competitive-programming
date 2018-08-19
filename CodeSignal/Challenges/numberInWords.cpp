/*You're practicing writing numbers in word form, according to the following rules:

    The first letter is capitalized
    Hyphenated words are used for numbers under 100 (eg: "Thirty-two")

Given an integer number, return a string representing the number in word form.

Examples

    For number = 1, the output should be numberInWords(number) = "One".

    For number = 12, the output should be numberInWords(number) = "Twelve".

    For number = 14, the output should be numberInWords(number) = "Fourteen".

    For number = 21, the output should be numberInWords(number) = "Twenty-one".

    For number = 299, the output should be numberInWords(number) = "Two hundred ninety-nine".

    For number = 123456, the output should be numberInWords(number) = "One hundred twenty-three thousand four hundred fifty-six".

Input / Output

    [execution time limit] 0.5 seconds (cpp)

    [input] integer number

    An integer representing the number you need to write out.

    Guaranteed constraints:
    1 ≤ number ≤ 106

    [output] string

    A string representing the number in word form.
*/

vector<string> splitNum(int num)
{
    vector<string> res {};
    string str {to_string(num)};
    
    // pad to 3 digits
    int pad = str.size() % 3;
    if (pad > 0) {str.insert(0, 3-pad, '0');}
    
    // split in groups of three
    for (int i=str.size(); i>0; i -= 3) {
        res.emplace_back(str.substr(i-3, 3));  
    }
    
    return res;
}

inline void rstrip(string& in)
{
    while(isspace(in.back())) {
        in.pop_back();
    }
}

inline string hundreds(const string& num)
{
    const char* single[] = {"", "one", "two", "three", 
                            "four", "five", "six", "seven", "eight", "nine"};
    const char* two[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", 
                         "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    const char* tens[]   = {"", "", "twenty", "thirty", "forty", "fifty", 
                            "sixty", "seventy", "eighty", "ninety"};
       
    string res {};
    
    if (num[0] != '0') {
        res += single[num[0] - '0'];
        res += " hundred ";
    }
    
    if (num[1] == '0') {
        res += single[num[2] - '0'];
    }
    else if (num[1] == '1') {
        res += two[num[2] - '0'];
    }
    else {
        res += tens[num[1] - '0'];
                
        if (num[2] != '0') {
            res += "-";
            res += single[num[2] - '0'];
        }
    }
    
    rstrip(res);
    
    return res;
}


string numberInWords(int num)
{    
    const char* power[]  = {"", " thousand ", " million ", " billion "};
    
    string res {};
    auto vec = splitNum(num);
    
    for (int i=0; i<vec.size(); ++i) {
        auto n = stoi(vec[i]);
        if (n > 0) {
            auto tmp = hundreds(vec[i]);
            tmp += power[i];
            
            res.insert(begin(res), begin(tmp), end(tmp));
        }
    }
    
    rstrip(res);
    res[0] = toupper(res[0]);
    
    return res;
}
