#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

int main()
{
    int n1, n2, n3;
    std::cin >> n1 >> n2 >> n3;
    
    std::vector<int> first (n1);
    std::copy_n(std::istream_iterator<int>(std::cin), n1, std::begin(first));

    std::vector<int> second (n2);
    std::copy_n(std::istream_iterator<int>(std::cin), n2, std::begin(second));
    
    std::vector<int> mid;
    std::set<int> result;
    
    std::set_intersection(first.begin(), first.end(), 
                          second.begin(), second.end(), 
                          std::inserter(result, result.end()));
    
    std::set_symmetric_difference(first.begin(), first.end(),
                                  second.begin(), second.end(),
                                  std::back_inserter(mid));
    
    std::vector<int> third (n3);
    std::copy_n(std::istream_iterator<int>(std::cin), n3, std::begin(third));
    
    std::set_intersection(mid.begin(), mid.end(),
                          third.begin(), third.end(),
                          std::inserter(result, result.end()));
    
    std::cout << result.size() << std::endl;
    std::copy(std::begin(result), 
              std::end(result),
              std::ostream_iterator<int>(std::cout, "\n"));
    
    return 0;
}
