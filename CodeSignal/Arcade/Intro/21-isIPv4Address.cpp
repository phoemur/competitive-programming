/*An IP address is a numerical label assigned to each device (e.g., computer, printer) participating in a computer network that uses the Internet Protocol for communication. There are two versions of the Internet protocol, and thus two versions of addresses. One of them is the IPv4 address.

IPv4 addresses are represented in dot-decimal notation, which consists of four decimal numbers, each ranging from 0 to 255 inclusive, separated by dots, e.g., 172.16.254.1.

Given a string, find out if it satisfies the IPv4 address naming rules.

Example

    For inputString = "172.16.254.1", the output should be
    isIPv4Address(inputString) = true;

    For inputString = "172.316.254.1", the output should be
    isIPv4Address(inputString) = false.

    316 is not in range [0, 255].

    For inputString = ".254.255.0", the output should be
    isIPv4Address(inputString) = false.

    There is no first number.

Input/Output

    [execution time limit] 0.5 seconds (cpp)

    [input] string inputString

    A string consisting of digits, full stops and lowercase English letters.

    Guaranteed constraints:
    1 ≤ inputString.length ≤ 30.

    [output] boolean

    true if inputString satisfies the IPv4 address naming rules, false otherwise.
*/

auto split_string(const std::string& input, const char delimiter) 
{
    std::stringstream ss {input};
    std::vector<std::string> result;
    for (std::string buffer; 
         getline(ss, buffer, delimiter);) 
            {result.push_back(move(buffer));}    
    return result;
}

bool isIPv4Address(const std::string& input) 
{
    if (input.find_first_not_of("1234567890.") != std::string::npos){
        return false;
    }
    auto ip = split_string(input, '.');
    if (ip.size() != 4) {return false;}
    for (auto& i: ip) {
        if (i.size()==0 || i.size()>3){return false;}
        if (std::stol(i) < 0 || std::stol(i) > 255) {return false;}
    }
    return true;
}
