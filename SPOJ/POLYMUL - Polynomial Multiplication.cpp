/*POLYMUL - Polynomial Multiplication
#fft-2 #karatsuba

Sam and Dean fight the supernatural creatures to protect the humans. Now they have come across a creature called the Vedala, which are always found in pairs. Each vedala can be represented by a polynomial. Both the Vedalas need to be killed at once or else they can't be killed. They can be killed only by using the product of the two polynomials representing the two Vedala. Help Sam and Dean find the product of the polynomials fast, so they can do thier work. 
Input

First line contains an integer T (≤ 10), number of test cases.

Each test case will have n (n ≤ 10000), maximum degree of the polynomials on the first line. 

Next two lines will have n+1 space separated integers each representing the coeffiecients of first and second polynomials respectively.

All input coefficients values are <=1000.
Output

For each test case ouput a line of 2n space seperated integers indicating coefficients of the polynomial created after multiplication.
Example

Input:
2
2
1 2 3
3 2 1
2
1 0 1
2 1 0

Output:
3 8 14 8 3
2 1 2 1 0*/

#include <algorithm>
#include <cmath>
#include <complex>
#include <iostream>
#include <iterator>
#include <vector>

constexpr auto pi() {return atan(1)*4;}

template<typename T>
T bitReverse(T x, T log2n) 
{ 
    static_assert(std::is_integral<T>::value, "Only integral types");
    
    T n = 0; 
    for (T i = 0; i < log2n; ++i) 
    { 
        n <<= 1; 
        n |= (x & 1); 
        x >>= 1; 
    } 
    
    return n; 
} 

void FFT(std::vector<std::complex<double>>& a)
{    
    const int n = a.size();
    const auto log2n = static_cast<int>(std::log2(n));
    
    std::vector<std::complex<double>> tmp (n);
    
    // bit reversal of the given array 
    for (int i = 0; i < n; ++i) { 
        int rev = bitReverse(i, log2n); 
        tmp[i] = a[rev]; 
    }
    
    // j is iota 
    const std::complex<double> J(0, 1); 
    for (int s = 1; s <= log2n; ++s) { 
        int m = 1 << s; // 2 power s 
        int m2 = m >> 1; // m2 = m/2 -1 
        std::complex<double> w(1, 0); 
  
        // principle root of nth complex  
        // root of unity. 
        std::complex<double> wm = std::exp(J * (pi() / m2));  
        for (int j = 0; j < m2; ++j) { 
            for (int k = j; k < n; k += m) { 
  
                // t = twiddle factor 
                auto t = w * tmp[k + m2];  
                auto u = tmp[k]; 
  
                // similar calculating y[k] 
                tmp[k] = u + t;  
  
                // similar calculating y[k+n/2] 
                tmp[k + m2] = u - t;  
            } 
            w *= wm; 
        } 
    }
    
    a = std::move(tmp);
}

void IFFT(std::vector<std::complex<double>>& a)
{
    // conjugate the complex numbers
    for (auto& num: a)
        num = std::conj(num);
    
    // forward fft
    FFT(a);
    
    // conjugate the complex numbers again and scale
    for (auto& num: a) 
    {
        num = std::conj(num);
        num /= a.size();
    }
}

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int n;
        std::cin >> n;
        
        // Calculate size and ajust it to be a power of 2 
        // (as required by recursive implementation)
        int sz = 2*n + 1;
        while ((sz & (sz - 1)) != 0) ++sz;
        
        std::vector<std::complex<double>> A      (sz);
        std::vector<std::complex<double>> B      (sz);
        
        std::copy_n(std::istream_iterator<long>(std::cin), n+1, std::begin(A));
        std::copy_n(std::istream_iterator<long>(std::cin), n+1, std::begin(B));
    
        // Fast Fourier Transform
        FFT(A);
        FFT(B);
        
        // Multiply
        for (std::size_t i = 0; i < A.size(); ++i) 
        {
            A[i] *= B[i];
        }
    
        // Inverse FFT
        IFFT(A);
    
        // Remove padding zeroes
        A.resize(2*n+1);
        
        // Print
        for (auto& n: A)
            std::cout << static_cast<long>(std::round(n.real())) << " ";
        
        std::cout << std::endl;
    }
    
    return 0;
}
