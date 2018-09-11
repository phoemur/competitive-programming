/*INVCNT - Inversion Count
#graph-theory #number-theory #shortest-path #sorting #bitmasks

Let A[0...n - 1] be an array of n distinct positive integers. If i < j and A[i] > A[j] then the pair (i, j) is called an inversion of A. Given n and an array A your task is to find the number of inversions of A.
Input

The first line contains t, the number of testcases followed by a blank space. Each of the t tests start with a number n (n <= 200000). Then n + 1 lines follow. In the ith line a number A[i - 1] is given (A[i - 1] <= 10^7). The (n + 1)th line is a blank space.
Output

For every test output one line giving the number of inversions of A.
Example

Input:
2

3
3
1
2

5
2
3
8
6
1


Output:
2
5

*/

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <type_traits>
#include <vector>

template<typename T,
         typename = typename std::enable_if<std::is_integral<T>::value, void>::type>
class BIT {
public:
    using size_type       = std::size_t;
    using value_type      = T;
    
private:
    std::vector<T> data_;
    
    void init()
    {
        for (unsigned i=0; i<data_.size(); ++i) {
            unsigned j = i + ((i+1) & -(i+1));
            if (j < data_.size()) {
                data_[j] += data_[i];
            }
        }
    }
    
public:
    // constructors
    
    template<typename InputIt>
    BIT(InputIt begin, InputIt end)
        : data_(begin, end) 
    {
        init();
    }
    
    explicit BIT(size_type s, T val = T())
        : data_(s, val)
    {
        init(); 
    }
    
    BIT(const std::initializer_list<T>& lst)
        : BIT(std::begin(lst), std::end(lst)) {}
        
    BIT(std::initializer_list<T>&& lst)
        : data_(std::move(lst))
    {
        init();
    }
    
    BIT() // default constructor
        : BIT(0) {}
        
    BIT(const BIT&) = default;
    BIT& operator=(const BIT&) = default;
    BIT(BIT&&) = default;
    BIT& operator=(BIT&&) = default;
    ~BIT() noexcept = default;
    
    // Returns the sum of the first i elements, 0 through i-1.
    T sum_until(int i) const 
    {
        T sum = 0;
        while (i) {
            sum += data_[i-1];
            i -= i & -i;
        }
        return sum;
    }
    
    // Returns the sum of the elements [i..j-1]
    T sum_range(size_type i, size_type j) const
    {
        T sum = 0;
        while (j > i) {
            sum += data_[j-1];
            j -= j & -j;
        }

        while (i > j) {
            sum -= data_[i-1];
            i -= i & -i;
        }
        return sum;
    }
    
    // add k to element i (and thus Fen_sum(a, j) for all j > i)
    void add(size_type i, T delta)
    {        
        while (i < data_.size()) {
            data_[i] += delta;
            i += (i+1) & -(i+1);
        }
    }
    
    // sets the value of the element at index i
    void set(size_type i, T value)
    {
        add(i, value - this->at(i));
    }
    
    // insert one element at the end
    void push_back(T val)
    {
        data_.push_back(0);
        set(data_.size()-1, val);
    }
    
    // remove one element at the end
    void pop_back()
    {
        set(data_.size()-1, 0);
        data_.pop_back();
    }
    
    // clear the tree
    inline void clear() {data_.clear();}   
    
    //unchecked access (only access, cannot assign)
    const T operator[](size_type n) const
    {
        return sum_range(n, n+1);
    }
    
    // Returns the value of the element at index n
    const T at(size_type n) const
    {
        if (n<0 || n>=data_.size()) throw std::out_of_range("Out of bounds access");
        return sum_range(n, n+1);        
    }
    
    size_type size()  const noexcept    { return data_.size(); }
    bool      empty() const noexcept    { return data_.empty(); }
    const std::vector<T>&  data() const noexcept {return data_;}
    
}; // end of class BIT

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int n;
        std::cin >> n;
        
        std::vector<int> a (n);
        std::vector<int> b (n);
        std::copy_n(std::istream_iterator<int>(std::cin), n, std::begin(a));
        std::iota(std::begin(b), std::end(b), 0);
        std::sort(std::begin(b), std::end(b), [&a](int l, int r){return a[l] < a[r];});
                
        BIT<int> bit (n+1);
        long res = 0;
        for (int i = 0; i < n; ++i)
        {
            res += bit.sum_range(b[i] + 1, n);
            bit.set(b[i], 1);
        }
        
        std::cout << res << std::endl;
    }
    
    return 0;
}
