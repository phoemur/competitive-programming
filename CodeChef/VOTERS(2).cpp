#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

int main()
{
    using namespace std;
    
    int n1, n2, n3;
    cin >> n1 >> n2 >> n3;
    
    vector<int> first (n1);
    copy_n(istream_iterator<int>(cin), n1, begin(first));

    vector<int> second (n2);
    copy_n(istream_iterator<int>(cin), n2, begin(second));
    
    vector<int> mid;
    set<int> result;
    
    set_intersection(first.begin(), first.end(), 
                     second.begin(), second.end(), 
                     inserter(result, result.end()));
    
    set_symmetric_difference(first.begin(), first.end(),
                             second.begin(), second.end(),
                             back_inserter(mid));
    
    vector<int> third (n3);
    copy_n(istream_iterator<int>(cin), n3, begin(third));
    
    set_intersection(mid.begin(), mid.end(),
                     third.begin(), third.end(),
                     inserter(result, result.end()));
    
    cout << result.size() << endl;
    copy(begin(result), 
         end(result),
         ostream_iterator<int>(cout, "\n"));
    
    return 0;
}
