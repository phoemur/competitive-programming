/*LCS0 - Longest Common Subsequence
#lcs

No imagination at the moment.
Input

You will be given two lines. The first line will contain the string A, the second line will contain the string B. Both strings consist of no more than 50000 lowercase Latin letters.
Output

Output the length of the longest common subsequence of strings A and B.
Example

Input

abababab
bcbb

Output

3

*/

#include <algorithm>
#include <iostream>
#include <cstdint>
#include <cstring>

// Reference solution -> https://repositorio.ufba.br/ri/bitstream/ri/20213/1/LCS_TCC-Final.pdf
// Which is based on Allison-Dix algorithm O(mn/w). w is the word size of the machine
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
    
    std::string a, b;
    std::cin >> a >> b;

    if (a.size() < b.size())
        std::swap(a, b);
    
    std::cout << LCS(a, b) << std::endl;

    return  0;
}
