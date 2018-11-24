/*LAZYPROG - The lazy programmer
no tags 

A new web-design studio, called SMART (Simply Masters of ART), employs two people. The first one is a web-designer and an executive director at the same time. The second one is a programmer. The director is so a nimble guy that the studio has already got N contracts for web site development. Each contract has a deadline di.

It is known that the programmer is lazy. Usually he does not work as fast as he could. Therefore, under normal conditions the programmer needs bi of time to perform the contract number i. Fortunately, the guy is very greedy for money. If the director pays him xi dollars extra, he needs only (bi - ai*xi) of time to do his job. But this extra payment does not influence other contracts. This means that each contract should be paid separately to be done faster. The programmer is so greedy that he can do his job almost instantly if the extra payment is (bi/ai) dollars for the contract number i.

The director has a difficult problem to solve. He needs to organize programmer’s job and, may be, assign extra payments for some of the contracts so that all contracts are performed in time. Obviously he wishes to minimize the sum of extra payments. Help the director!
Input

First line of the input contains an integer t (1 ≤ t ≤ 45), equal to the number of testcases. Then descriptions of t testcases follow.

First line of description contains the number of contracts N (1 ≤ N ≤ 100000, integer). Each of the next N lines describes one contract and contains integer numbers ai, bi, di (1 ≤ ai, bi ≤ 10000; 1 ≤ di ≤ 1000000000) separated by spaces.

At least 90% of testcases will have 1 ≤ N ≤ 10000.
Output

For each testcase in the input your program should output one line with a single real number S. Here S is the minimum sum of money which the director needs to pay extra so that the programmer could perform all contracts in time. The number must have two digits after the decimal point.
Example

Input:
1
2
20 50 100
10 100 50

Output:
5.00

*/

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>

struct Contract {
    int a;
    int b;
    int d;
};

bool operator<(const Contract& lhs, const Contract& rhs)
{
    return lhs.d < rhs.d;
}

int main()
{
    int tests;
    std::cin >> tests;
    
    for (int cas = 1; cas <= tests; ++cas)
    {
        int n;
        std::cin >> n;
        
        std::vector<Contract> vec (n);
        
        for (int i = 0; i < n; ++i)
            std::cin >> vec[i].a >> vec[i].b >> vec[i].d;
        
        std::sort(vec.begin(), vec.end());
        
        std::priority_queue<std::pair<int,int>> PQ;
        int time = 0;
        double money = 0.0;
        
        for (const auto& elem: vec)
        {
            time += elem.b;
            PQ.push({elem.a, elem.b});
            
            if (time > elem.d)
            {
                while (true)
                {
                    auto cur = PQ.top();
                    PQ.pop();
                    
                    if (time - cur.second <= elem.d) // Pay only needed and exit
                    {
                        cur.second -= time - elem.d;
                        money += static_cast<double>(time - elem.d) / cur.first;
                        time = elem.d;
                        PQ.push(cur);
                        break;
                    }
                    else // Pay all needed to make this contract instantly and proceed to the next best pay relation
                    {
                        money += static_cast<double>(cur.second) / cur.first; 
                        time -= cur.second;
                    }
                }
            }
        }
        
        std::cout << std::setprecision(2) << std::fixed << money << std::endl;
    }
    
    return 0;
}
