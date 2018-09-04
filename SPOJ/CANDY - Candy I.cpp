/*CANDY - Candy I
#ad-hoc-1

Jennifer is a teacher in the first year of a primary school. She has gone for a trip with her class today. She has taken a packet of candies for each child. Unfortunatelly, the sizes of the packets are not the same.

Jennifer is afraid that each child will want to have the biggest packet of candies and this will lead to quarrels or even fights among children. She wants to avoid this. Therefore, she has decided to open all the packets, count the candies in each packet and move some candies from bigger packets to smaller ones so that each packet will contain the same number of candies. The question is how many candies she has to move.
Input specification

The input file consists of several blocks of data. Each block starts with the number of candy packets N(1<= N <=10000) followed by N integers (each less than 1000) in separate lines, giving the number of candies in each packet. After the last block of data there is the number -1.
Output specification

The output file should contain one line with the smallest number of moves for each block of data. One move consists of taking one candy from a packet and putting it into another one. If it is not possible to have the same number of candies in each packet, output the number -1.
Example

Input file:
5
1
1
1
1
6
2
3
4
-1

Output file:
4
-1

*/


#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

inline void solve(const std::vector<int>& packets)
{
    int total = std::accumulate(std::begin(packets), std::end(packets), 0);
        
    if (total % packets.size() == 0)
    {
        int amount = total / packets.size();
        int res = std::accumulate(std::begin(packets), 
                                  std::end(packets), 
                                  0, 
                                  [amount](int a, int b){
                                      if (b - amount > 0)
                                          return a + (b - amount);
                                      else
                                          return a;
                                  });
            
        std::cout << res << std::endl;
    }
    else
    {
        std::cout << -1 << std::endl;
    }
}

int main()
{
    int n;
    std::vector<int> packets;
    
    while (std::cin >> n && n != -1)
    {
        packets.resize(n);
        
        std::copy_n(std::istream_iterator<int>(std::cin), n, std::begin(packets));
        
        solve(packets);
    }
    
    return 0;
}
