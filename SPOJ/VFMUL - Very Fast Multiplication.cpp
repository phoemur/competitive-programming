/*VFMUL - Very Fast Multiplication

https://www.spoj.com/problems/VFMUL/
*/

#include <algorithm>
#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

namespace Solution {

using cd = std::complex<double>;
constexpr static double PI = std::atan(1)*4;

// Read a std::vector<int>
std::istream& operator>>(std::istream& in, std::vector<int>& vec)
{
    vec.clear();
    
    // Ignore beginning white spaces
    while(std::isspace(in.peek()))
        in.get();
    
    // Read until next whitespace
    while (!std::isspace(in.peek()))
        vec.push_back(in.get() - '0');
    
    return in;
}

// Output std::vector<int> with formatting
std::ostream& operator<<(std::ostream& os, const std::vector<int>& vec)
{
    // Ignore leading zeroes
    int i = 0;
    int sz = vec.size();
    while (vec[i] == 0 && i + 1 < sz) ++i;
    
    // Output
    for (; i < sz; ++i)
        os << vec[i];
    
    return os;
}

// Reverse bits
inline int reverse(int num, int lg_n)
{
    int res = 0;
    for (int i = 0; i < lg_n; i++)
    {
        if (num & (1 << i))
            res |= 1 << (lg_n - 1 - i);
    }
    
    return res;
}

// Fast Fourier Transform -> https://cp-algorithms.com/algebra/fft.html
// Invert flag indicates Inverse FFT
void FFT(std::vector<cd>& a, bool invert = false) {
    int n = a.size();
    int lg_n = 0;
    
    while ((1 << lg_n) < n)
        lg_n++;

    for (int i = 0; i < n; i++)
    {
        if (i < reverse(i, lg_n))
            std::swap(a[i], a[reverse(i, lg_n)]);
    }

    for (int len = 2; len <= n; len <<= 1)
    {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(std::cos(ang), std::sin(ang));
        
        for (int i = 0; i < n; i += len)
        {
            cd w(1);
            for (int j = 0; j < len / 2; j++)
            {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}

// Multiply 2 std::vector<int> using FFT convolution
std::vector<int> multiply(const std::vector<int>& a, const std::vector<int>& b)
{
    std::vector<cd> fa (a.begin(), a.end()), 
                    fb (b.begin(), b.end());
                    
    // Insert padding zeroes to adjust size to a power of 2
    int n = 1;
    int result_sz = fa.size() + b.size();
    while (n < result_sz) 
        n <<= 1;
    
    fa.resize(n, 0);
    fb.resize(n, 0);
    
    // FFT
    FFT(fa);
    FFT(fb);
    
    // Multiply
    for (int i = 0; i < n; ++i)
        fa[i] *= fb[i];
    
    // Inverse FFT
    FFT(fa, true);

    // Build result vector
    std::vector<int> result (result_sz, 0);
    for (int i = 1; i < result_sz; ++i)
    {
        result[i] = std::round(fa[i-1].real());
    }
    
    // Normalize
    int carry = 0;
    for (int i = result_sz-1; i >= 0; --i)
    {
        result[i] += carry;
        carry = result[i] / 10;
        result[i] %= 10;
    }
    
    return result;
}

std::vector<int> operator*(const std::vector<int>& a, const std::vector<int>& b)
{
    return multiply(a, b);
}

} // End of namespace Solution

int main()
{
    using namespace Solution;
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int tests;
    std::cin >> tests;
    
    std::vector<int> a, b;
    while (tests--)
    {
        std::cin >> a >> b;
        
        std::cout << a * b << std::endl;
    }
        
    return 0;
}
