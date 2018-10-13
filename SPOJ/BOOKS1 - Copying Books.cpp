/*BOOKS1 - Copying Books
#binary-search

Before the invention of book-printing, it was very hard to make a copy of a book. All the contents had to be re-written by hand by so called scribers. The scriber had been given a book and after several months he finished its copy. One of the most famous scribers lived in the 15th century and his name was Xaverius Endricus Remius Ontius Xendrianus (Xerox). Anyway, the work was very annoying and boring. And the only way to speed it up was to hire more scribers.

Once upon a time, there was a theater ensemble that wanted to play famous Antique Tragedies. The scripts of these plays were divided into many books and actors needed more copies of them, of course. So they hired many scribers to make copies of these books. Imagine you have m books (numbered 1, 2 ... m) that may have different number of pages (p1, p2 ... pm) and you want to make one copy of each of them. Your task is to divide these books among k scribes, k <= m. Each book can be assigned to a single scriber only, and every scriber must get a continuous sequence of books. That means, there exists an increasing succession of numbers 0 = b0 < b1 < b2, ... < bk-1 <= bk = m such that i-th scriber gets a sequence of books with numbers between bi-1+1 and bi. The time needed to make a copy of all the books is determined by the scriber who was assigned the most work. Therefore, our goal is to minimize the maximum number of pages assigned to a single scriber. Your task is to find the optimal assignment.
Input

The input consists of N cases (equal to about 200). The first line of the input contains only positive integer N. Then follow the cases. Each case consists of exactly two lines. At the first line, there are two integers m and k, 1 <= k <= m <= 500. At the second line, there are integers p1, p2, ... pm separated by spaces. All these values are positive and less than 10000000.
Output

For each case, print exactly one line. The line must contain the input succession p1, p2, ... pm divided into exactly k parts such that the maximum sum of a single part should be as small as possible. Use the slash character ('/') to separate the parts. There must be exactly one space character between any two successive numbers and between the number and the slash.

If there is more than one solution, print the one that minimizes the work assigned to the first scriber, then to the second scriber etc. But each scriber must be assigned at least one book.
Example

Sample input:
2
9 3
100 200 300 400 500 600 700 800 900
5 4
100 100 100 100 100

Sample output:
100 200 300 400 500 / 600 700 / 800 900
100 / 100 / 100 / 100 100

*/

#include <algorithm>
#include <iostream>
#include <vector>

/* This function returns true if at most k workers can
 * write at most max_load pages each */
bool feasible(const std::vector<long>& vec, long max_load, int k)
{
    int required = 1, curr = 0;
    
    for (auto& book: vec)
    {
        if (curr + book <= max_load)
        {
            curr += book;
        }
        else
        {
            ++required;
            curr = book;
        }
    }
    
    return required <= k;
}

/* This function uses binary search to find 
 * the optimum work load for the scribers */
inline long get_bestload(const std::vector<long>& vec, long lo, long hi, int k)
{
    while (lo < hi)
    {
        long mid = lo + (hi - lo) / 2;
            
        if (feasible(vec, mid, k))
            hi = mid;
        else
            lo = mid + 1;
    }
    
    return lo;
}

/* Print according to requirement: If there is more than one solution, 
 * print the one that minimizes the work assigned to the first scriber, 
 * then to the second scriber etc. But each scriber must be 
 * assigned at least one book.*/
inline void print(const std::vector<long>& vec, long max_load, int k)
{
    long curr = 0, slash_count = 0;
    
    std::vector<bool> slash (vec.size()+1, false);
    
    for (int i = vec.size() - 1; i >= 0; --i)
    {
        if (curr + vec[i] <= max_load)
        {
            curr += vec[i];
        }
        else
        {
            slash[i+1] = true;
            ++slash_count;
            curr = vec[i];
        }
        
        if (k - 1 - slash_count == i )
        {
            std::fill(std::begin(slash)+1, std::begin(slash)+i+1, true);
            break;
        }
    }
    
    for (int i = 0; i < vec.size(); ++i)
    {
        if (slash[i])
            std::cout << "/ ";
        
        std::cout << vec[i] << " ";
    }
    
    std::cout << std::endl;
}

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int m, k;
        std::cin >> m >> k;
        
        std::vector<long> vec;
        vec.reserve(m);
        long sum = 0;
        long mx = 0;
        
        // Input
        for (int i = 0; i < m; ++i)
        {
            long elem;
            std::cin >> elem;
            
            sum += elem;
            mx = std::max(mx, elem);
            vec.push_back(elem);
        }
        
        long avrg = sum / m;
        mx = std::max(mx, avrg);
        
        // Get best load using bsearch
        auto load = get_bestload(vec, mx, sum, k);

        // Print
        print(vec, load, k);
    }
    
    return 0;
}
