#include <algorithm>
#include <iostream>
#include <cstdint>
#include <cstring>

// Bit parallel LCS -> Allison-Dix algorithm O(mn/w)
int LCS(const std::string& X, const std::string& Y) 
{    
    int m = X.size();
    int n = Y.size();
    
    // Return on empty string
    if (m == 0 || n == 0) return 0;

    int w = (m + 31) >> 5; // ceil[m/32]

    std::uint32_t S[256][w];  //  Sigma {all  char}
    std::memset(S, 0, sizeof(std::uint32_t) * 256 * w);
    
    std::int32_t set = 1;

    for (int i = 0, j = 0; i < m; ++i)
    {
        S[X[i]][j] |= set;
        set <<= 1;
        if (!set) {set++;j++;}
    }

    std::uint32_t L[w]; //  Vetor L(i)
    std::memset(L, 0, sizeof(std::uint32_t) * w);

    for (int i = 0; i < n; ++i) 
    {
        std::uint32_t b1 = 1; // Borrows
        std::uint32_t b2 = 0;

        for (int j = 0; j < w; ++j)
        {
            std::uint32_t U  = L[j] | S[Y[i]][j];
            std::uint32_t c  = L[j] >> 31; // Carry
            std::uint32_t V  = U - (L[j] << 1 | b1+b2);
            b1 = c;
            b2 = (V > U);
            L[j] = U & (~V);
        }
    }

    // Count 1 bits from L[w] vector, Kernighan & Ritchie method
    int res = 0;
    for (int i = 0; i < w; ++i)
        for (; L[i]; ++res) 
            L[i] &= L[i] - 1;

    return res;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int t;
    std::cin >> t;
    
    std::string input;
    

    if (std::cin >> input)
    {
        std::string rev {input.rbegin(), input.rend()}; // Reversed string
        std::cout << input.size() - LCS(input, rev) << std::endl;
    }
    
    return 0;
}
