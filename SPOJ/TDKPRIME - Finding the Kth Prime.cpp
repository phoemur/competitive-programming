/*TDKPRIME - Finding the Kth Prime
#sieve-of-eratosthenes

The problem statement is really simple. There are some queries. You are to give the answers.
Input

An integer stating the number of queries Q(equal to 50000), and Q lines follow, each containing one integer K between 1 and 5000000 inclusive.
Output

Q lines with the answer of each query: the Kth prime number.
Example

Input:
7
1
10
100
1000
10000
100000
1000000

Output:
2
29
541
7919
104729
1299709
15485863

*/

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

const int64_t L1D_CACHE_SIZE = 32768;
int sieve[5000001];

void segmented_sieve(int64_t limit, int* output)
{
    int64_t sqrt = static_cast<int64_t>(std::sqrt(limit));
    int64_t segment_size = std::max(sqrt, L1D_CACHE_SIZE);
    int64_t count = (limit < 2) ? 0 : 1;

    // we sieve primes >= 3
    int64_t i = 3;
    int64_t n = 3;
    int64_t s = 3;

    std::vector<char> sieve(segment_size);
    std::vector<bool> is_prime(sqrt + 1, true);
    std::vector<int64_t> primes;
    std::vector<int64_t> multiples;

    for (int64_t low = 0; low <= limit; low += segment_size)
    {
        std::fill(sieve.begin(), sieve.end(), true);

        // current segment = [low, high]
        int64_t high = low + segment_size - 1;
        high = std::min(high, limit);

        // generate sieving primes using simple sieve of Eratosthenes
        for (; i * i <= high; i += 2)
            if (is_prime[i])
                for (int64_t j = i * i; j <= sqrt; j += i)
                    is_prime[j] = false;
        
        // initialize sieving primes for segmented sieve
        for (; s * s <= high; s += 2)
        {
            if (is_prime[s])
            {
                primes.push_back(s);
                multiples.push_back(s * s - low);
            }
        }

        // sieve the current segment
        for (std::size_t i = 0; i < primes.size(); i++)
        {
            int64_t j = multiples[i];
            
            for (int64_t k = primes[i] * 2; j < segment_size; j += k)
                sieve[j] = false;
            
            multiples[i] = j - segment_size;
        }

        // Output
        for (; n <= high; n += 2)
            if (sieve[n - low]) // n is a prime
                output[count++] = n;
    }
}


int main()
{
    int queries;
    std::scanf("%d", &queries);
       
    sieve[0] = 2;
    segmented_sieve(86028157, &sieve[0]);
    
    while (queries--)
    {
        int kth;
        std::scanf("%d", &kth);
        
        std::printf("%d\n", sieve[kth-1]);
    }
    
    return 0;
}
