/* PRINT - Prime Intervals
no tags 

In this problem you have to print all primes from given interval.
Input

t - the number of test cases, then t lines follows. [t <= 150]
On each line are written two integers L and U separated by a blank. L - lower bound of interval, U - upper bound of interval. [2 <= L < U <= 2147483647] [U-L <= 1000000].
Output

For each test case output must contain all primes from interval [L; U] in increasing order.
Example

Input:

2
2 10
3 7

Output:

2
3
5
7
3
5
7
*/

#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>

#define SZ 47000u

unsigned char sieve[SZ];
std::vector<int> primes;

void prepare()
{
    std::memset(sieve, 1, SZ);
    primes.reserve(4855);

    for (int64_t p = 2; p < SZ; ++p)
    {
        if (sieve[p] == 1)
        {
            primes.push_back(p);

            for (int64_t i = p*p; i < SZ; i += p)
            {
                sieve[i] = 0;
            }
        }
    }
}

int main(int argc, char** argv)
{
    prepare();

    int tests;
    std::scanf("%d", &tests);

    while (tests--)
    {
        int low, high;
        std::scanf("%d%d", &low, &high);

        if (low == 1)
        {
            ++ low;
        }

        std::vector<int> arr (high - low + 1, 0);
        int limit = static_cast<int>(std::sqrt(high));

        for (int i = 0; primes[i] <= limit; ++i)
        {
            int64_t cur = primes[i] * 2;
        
            if (cur < low)
            {
                cur = (low / primes[i]) * primes[i];

                if (low % primes[i] != 0)
                    cur += primes[i];
            }

            for (;cur <= high; cur += primes[i])
            {
                arr[cur - low] = 1;
            }
        }

        for (int i = 0; i < arr.size(); ++i)
        {
            if (arr[i] == 0)
            {
                std::printf("%d\n", low+i);
            }
        }

    }
    
    return 0;
}
