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

template<typename InputIt>
void FFT(InputIt start, InputIt finish)
{    
    auto N = std::distance(start, finish);
    
    if (N < 2) 
        return;
    else {
        // divide
        auto mid = std::stable_partition(start, finish, [&start](auto& a) {
            return std::distance(&*start, &a) % 2 == 0; // pair indexes on the first half and odd on the last
        });
        
        //conquer
        FFT(start,  mid);   // recurse even items
        FFT(mid, finish);   // recurse odd  items
        
        //combine
        using value_type = typename std::iterator_traits<InputIt>::value_type;
        
        for (auto it = start; it != mid; std::advance(it, 1))
        {
            auto k = std::distance(start, it);
            auto odd_it = mid + k;
            auto w    = std::exp( value_type(0.0,-2.0 * pi() * k / N) ) * (*odd_it);
            
            *odd_it = *it - w;
            *it     = *it + w;
        }
    }
}

template<typename InputIt>
void IFFT(InputIt start, InputIt finish)
{
    std::transform(start, finish, start, [](auto& a){return std::conj(a);});
    
    FFT(start, finish);
    
    auto N = std::distance(start, finish);
    std::transform(start, finish, start, [N](auto& a) {
                                                          a = std::conj(a);
                                                          return a /= N;
                                                      });
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
        FFT(std::begin(A), std::end(A));
        FFT(std::begin(B), std::end(B));
        
        // Multiply
        for (std::size_t i = 0; i < sz; ++i) 
        {
            A[i] *= B[i];
        }
    
        // Inverse FFT
        IFFT(std::begin(A), std::end(A));
    
        // Remove padding zeroes
        A.resize(2*n+1);
        
        // Print
        for (auto& n: A)
            std::cout << static_cast<long>(std::round(n.real())) << " ";
        
        std::cout << std::endl;
    }
    
    return 0;
}
