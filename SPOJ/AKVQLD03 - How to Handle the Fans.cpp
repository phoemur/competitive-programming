/*AKVQLD03 - How to Handle the Fans
#tree #binary-search

Trey Parker and Matt Stone, the creators of “South Park” are having some problems handling their fans. The number of fans is so huge that can’t even count them properly. So they hired “N” employees for counting the fans. All the “N” employees had their own separate offices and they were located in a straight line with positions numbered as 1, 2, 3 … up to N. Fans can come to the office of any employee at any time and tell them how they feel about the show and if they are lucky enough, they may get to meet Trey Parker and Matt Stone.

All the employees keep on updating Trey and Matt about the number of fans currently in their offices, so at each moment, they will have a list of “N” positions and the number of fans in each of these positions. Trey and Matt suddenly start taking a walk from office at position “A” to position “B” to meet their fans, but before they start walking they want to know the sum of all the fans in the offices from position “A” to “B”. But counting them one by one is taking a lot of time, so now they hired you, an awesome software engineer to do this task. Your task is to find the sum of all the fans present in the offices between positions “A” to “B” ("A" and "B" inclusive). Let’s see if you could do it fast enough.
Input

The first line of Input contains two integers “N” and “Q”. “N” is the no. of employees hired by Trey and Matt. “Q” is the no. of queries to be followed.

Each of the next “Q” lines contain a query. A query can be of two types:

“add P F” – this means that “F” no. of fans came to the office at Position “P”

“find A B” – this means that Trey and Matt wants to know the sum of fans present at offices at positions “A” to “B”
Output

For each query of the type “find A B”, output the sum of fans present at offices at positions “A” to “B” in a different line.
Constraints

1 <= N <= 10^6

1 <= Q <= 10^5

1 <= A < B <= N

1 <= P <=N

1 <= F <= 10^4
Example

Input:

10 10

find 1 5

add 5 8

add 6 2

find 4 5

find 4 6

add 2 4

find 2 6

add 6 7

find 1 6

find 7 10

Output:

0

8

10

14

21

0

*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

namespace Segment {
    
template<typename T,
         typename Function = std::plus<T>>    
class Tree {
public:
    using size_type       = std::size_t;
    using value_type      = T;
    
private:
    std::vector<T> data_;
    std::size_t sz;
    Function func {};
    
public:
    // constructors
    explicit Tree(std::size_t n)
        : data_{}, sz{n}
    {
        // Make sz a power of 2
        while ((sz & (sz - 1)) != 0) ++sz;
        data_.resize(2 * sz, T{});
    }
    
    template<typename InputIt>
    Tree(InputIt first, InputIt last)
        : Tree(std::distance(first, last))
    {
        static_assert(std::is_constructible<T, typename std::iterator_traits<InputIt>::value_type>::value,
                      "Invalid input type");
                
        // Add leaf nodes
        std::copy(first, last, std::begin(data_) + sz);
        
        // Build the tree by calculating parents
        for (int i = sz - 1; i > 0; --i)
            data_[i] = func(data_[i<<1], data_[i<<1 | 1]);
    }
    
    Tree(std::initializer_list<T> lst)
        : Tree(std::begin(lst), std::end(lst)) {}
        
    Tree(const Tree&) = default;
    Tree& operator=(const Tree&) = default;
    Tree(Tree&&) = default;
    Tree& operator=(Tree&&) = default;
    ~Tree() noexcept = default;
    
    // function to update a tree node
    template<typename X = T>
    void update(std::size_t index, X&& value) 
    { 
        // set value at position index
        data_.at(index + sz) = std::forward<X>(value);
    
        // move upward and update parents
        for (int i=index + sz; i > 1; i >>= 1)
            if (!(i & 1))
                data_[i>>1] = func(data_[i], data_[i^1]);
            else
                data_[i>>1] = func(data_[i^1], data_[i]);
    }
    
    // function to get sum on interval [l, r)
    T query(int l, int r, T init = T()) const noexcept
    {     
        // loop to find the sum in the range
        for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
            if (l & 1) 
                init = func(init, data_[l++]);
    
            if (r & 1) 
                init = func(init, data_[--r]);
        }
    
        return init;
    }
    
    const T& operator[](std::size_t n) const noexcept
    {
        return data_[sz + n];
    }
    
    const T& at(int n) const
    {
        if (n < 0 || n >= sz)
            throw std::out_of_range("Out of bounds access at index " + std::to_string(n));
        
        return this->operator[](n);
    }
    
    const std::vector<T>&  data() const noexcept {return data_;}
    std::size_t            size() const noexcept {return sz;}
    
}; // class Tree
    
} // namespace Segment

int main()
{
    int n, q;
    std::cin >> n >> q;
       
    Segment::Tree<int> tree (n);
    std::string a;
    int l, r;
    
    while (q--)
    {
        std::cin >> a >> l >> r;
        
        if (a == "add")            
            tree.update(l-1, tree[l-1] + r);
        else if (a == "find")
            std::cout << tree.query(l-1, r) << std::endl;
    }
    
    return 0;
}
