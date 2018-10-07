/*MINVEST - Investment Money
#knapsack #dynamic-programming

English 	Vietnamese

John never knew he had a grand-uncle, until he received the notary’s letter. He learned that his late grand-uncle had gathered a lot of money, somewhere in South-America, and that John was the only inheritor.

John did not need that much money for the moment. But he realized that it would be a good idea to store this capital in a safe place, and have it grow until he decided to retire. The bank convinced him that a certain kind of bond was interesting for him. This kind of bond has a ﬁxed value, and gives a ﬁxed amount of yearly interest, payed to the owner at the end of each year.


The bond has no ﬁxed term. Bonds are available in different sizes. The larger ones usually give a better interest. Soon John realized that the optimal set of bonds to buy was not trivial to ﬁgure out. Moreover, after a few years his capital would have grown, and the schedule had to be re-evaluated. Assume the following bonds are available:

Value Annual interest
4000 400
3000 250



With a capital of 10 000$ one could buy two bonds of 4000$, giving a yearly interest of 800$. Buying two bonds of 3000$, and one of 4000$ is a better idea, as it gives a yearly interest of e900. After two years the capital has grown to 11800$, and it makes sense to sell a 3000$ one and buy a 4000$ one, so the annual interest grows to 1050$.

This iswhere this story grows unlikely: the bank does not charge for buying and selling bonds. Next year the total sum is 12850$, which allows for three times 4000$, giving a yearly interest of 1200$. Here is your problem: given an amount to begin with, a number of years, and a set of bonds with their values and interests, ﬁnd out how big the amount may grow in the given period, using the best schedule for buying and selling bonds.

Input

 

The ﬁrst line contains a single positive integer N which is the number 
of test cases.  
The ﬁrst line of a test case contains two positive integers: 
the amount to start with (at most 1000 000$), and the number of years the 
capital may grow (at most 40).
The following line contains a single number: the number d (1 ≤ d ≤ 10) of 
available bonds.
The next d lines each contain the description of a bond. 
The description of a bond consists of two positive integers: the value 
of the bond, and the yearly interest for that bond. The
value of a bond 
is always a multiple of 1000$. The interest of a bond is never more than
10% of its value

SAMPLE INPUT
1
10000 4
2
4000 400
3000 250

Output

For each test case, output – on a separate line – the capital at the end
of the period, after an optimal schedule of buying and selling.

SAMPLE OUTPUT
14050

 

*/

#include <algorithm>
#include <iostream>
#include <vector>

struct Bond {
    int price;
    int interest;
};

// Recurrence relation
// We'll exploit the fact that prices are always multiples of 1000
long solve_util(const std::vector<Bond>& vec, 
                int pos, 
                long amount) // here amount is already divided by 1000
{
    if (pos == 0 || amount == 0)
        return 0;
    else if (vec[pos-1].price > amount * 1000)
        return solve_util(vec, pos-1, amount);
    else
        return std::max(solve_util(vec, pos-1, amount), 
                        vec[pos-1].interest + solve_util(vec, pos, ((amount * 1000) - vec[pos-1].price) / 1000));
}

long solve_recursive(const std::vector<Bond>& vec, long amount, int years)
{
    while (years--)
    {
        amount += solve_util(vec, vec.size(), amount / 1000);
    }
    
    return amount;
}

// Dynamic programming bottom-up approach
long solve(const std::vector<Bond>& vec, long amount, int years)
{
    const int sz = vec.size();
    
    std::vector<std::vector<long>> dp (2);
    
    while (years--)
    {
        int sz2 = amount / 1000; // Exploit the fact that prices are always multiples of 1000
        
        // Clear dp table and resize
        for (auto& row: dp)
        {
            std::fill(std::begin(row), std::end(row), 0);
            row.resize(sz2 + 1, 0);
        }
        
        // Calculate result for this year
        // According to recurrence relation expressed above
        for(int i = 0; i <= sz; ++i)
        {
            for (int j = 0; j <= sz2; ++j)
            {
                if (i == 0 || j == 0)
                    dp[1][j] = 0;
                else if (vec[i-1].price > j * 1000)
                    dp[1][j] = dp[0][j];
                else
                {
                    int index = j - (vec[i-1].price / 1000) < 0 ? 0: j - (vec[i-1].price / 1000);
                    dp[1][j] = std::max(dp[0][j], 
                                        vec[i-1].interest + dp[1][index]);
                }
            }
            
            std::iter_swap(&dp[0], &dp[1]);
        }
            
        // Increment amount
        amount += dp[0][sz2];
    }
    
    return amount;
}

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        long amount;
        int years, n;
        std::cin >> amount >> years >> n;
        
        std::vector<Bond> vec;
        vec.reserve(n);
        
        while (n--)
        {
            int a, b;
            std::cin >> a >> b;
            vec.push_back({a, b});
        }
        
        //std::cout << solve_recursive(vec, amount, years) << std::endl;
        std::cout << solve(vec, amount, years) << std::endl;
    }
    
    return 0;
}
