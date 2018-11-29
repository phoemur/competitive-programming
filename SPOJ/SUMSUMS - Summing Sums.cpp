/*SUMSUMS - Summing Sums
no tags 

The N (1 ≤ N ≤ 50,000) cows, conveniently numbered 1, 2, ..., N, are trying to learn some encryption algorithms. After studying a few examples, they have decided to make one of their own! However, they are not very experienced at this, so their algorithm is very simple:

Each cow i is given a starting number Ci (0 ≤ Ci < 90,000,000), and then all the cows perform the following process in parallel:

    First, each cow finds the sum of the numbers of the other N-1 cows.
    After all cows are finished, each cow replaces her number with the sum she computed. To avoid very large numbers, the cows will keep track of their numbers modulo 98,765,431.

They told Canmuu the moose about it in November; he was quite impressed. Then one foggy Christmas Eve, Canmuu came to say:

    "Your algorithm is too easy to break! You should repeat it T (1 ≤ T ≤ 1,414,213,562) times instead."

Obviously, the cows were very frustrated with having to perform so many repetitions of the same boring algorithm, so after many hours of arguing, Canmuu and the cows reached a compromise: You are to calculate the numbers after the encryption is performed!
Input

    Line 1: Two space-separated integers: N and T.
    Lines 2..N+1: Line i+1 contains a single integer: Ci.

Output

    Lines 1..N: Line i contains a single integer representing the number of cow i (modulo 98,765,431) at the end of the encryption.

Example

Input:
3 4
1
0
4

Output:
26
25
29

The following is a table of the cows' numbers for each turn:

          Cows' numbers
Turn    Cow1  Cow2  Cow3
 0        1     0     4
 1        4     5     1
 2        6     5     9
 3       14    15    11
 4       26    25    29

Warning: large input/output data. */

#include <cstdio>
#include <vector>

#define MOD 98765431

// Multiply 2 NxN (square) matrix % MOD
std::vector<std::vector<long>> operator*(const std::vector<std::vector<long>>& lhs, 
                                         const std::vector<std::vector<long>>& rhs)
{    
    int N = lhs.size();
    std::vector<std::vector<long>> res (N, std::vector<long>(N, 0));
    
    // Multiply -> O(n^3)
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                res[i][j] = (res[i][j] + (lhs[i][k] * rhs[k][j])) % MOD;
        
    return res;
}

// Binary exponentiation of a square matrix
std::vector<std::vector<long>> power(std::vector<std::vector<long>> base, // pass by value to work on a copy
                                     int exp) 
{    
    int N = base.size();
    std::vector<std::vector<long>> res (N, std::vector<long>(N, 0));
    
    // Make res the identity matrix
    for (int i = 0; i < N; ++i)
        res[i][i] = 1;
    
    // Multiply by powers of 2 whose bit is set on exp
    while (exp > 0)
    {
        if (exp & 1)
            res = res * base;
        
        base = base * base; // Square the base
        exp >>= 1;
    }
    
    return res;
}

int main()
{
    int n, k;
    std::scanf("%d %d", &n, &k);
    
    // Transformation Matrix
    /*std::vector<std::vector<long>> trf (n, std::vector<long>(n, 1)); -> This TLE, lets change
    for (int i = 0; i < n; ++i)
        trf[i][i] = 0L;*/
    
    std::vector<std::vector<long>> trf {{0, n-1}, {1, n-2}};
    
    // Input F0
    std::vector<long> f1 (n);
    
    for (auto& elem: f1)
        std::scanf("%ld", &elem);
    
    auto res = power(trf, k);
        
    long x = res[0][0];
    long y = res[1][0];
    long diff = y - x;
    long sum = 0;
    
    for (int i = 0; i < n; ++i)
        sum = (sum + f1[i] * y) % MOD;

    for (int i = 0; i < n; ++i)
        std::printf("%ld\n", (sum - ((f1[i] * diff) % MOD) + MOD) % MOD);
    
    return 0;
}
