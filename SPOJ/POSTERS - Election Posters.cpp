/*POSTERS - Election Posters
#ad-hoc-1

A parliamentary election was being held in Byteland. Its enterprising and orderly citizens decided to limit the entire election campaign to a single dedicated wall, so as not to ruin the panorama with countless posters and billboards. Every politician was allowed to hang exactly one poster on the wall. All posters extend from top to bottom, but are hung at different points of the wall, and may be of different width. The wall is divided horizontally into sections, and a poster completely occupies two or more adjacent sections.

With time, some of the posters were covered (partially or completely) by those of other politicians. Knowing the location of all the posters and the order in which they were hung, determine how many posters have at least one visible section in the end.
Input

The input begins with the integer t, the number of test cases. Then t test cases follow.

Each test case begins with a line containing integer n - the number of posters (1 <= n <= 40000). Then n lines follow, the i-th (1 <= i <= n) containing exactly two integers li ri, denoting the numbers of the leftmost and rightmost sections covered by the i-th poster (1 <= li < ri <= 107). The input order corresponds to the order of hanging posters.
Output

For each test case output a line containing one integer - the number of posters with visible sections.
Example

Sample input:
1
5
1 4
2 6
8 10
3 4
7 10

Sample output:
4

An illustration of the sample input is given below.*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>

struct Poster {
    int a;
    int b;
};

int tree[1000000]; // This is not the tree, just the lazy propagation array


inline void push_down(int node, int lo, int hi)
{
    if(tree[node] != 0)
    {
        if(lo != hi)
        {            
            tree[2*node] = tree[2*node+1] = tree[node];
            tree[node] = 0;
        }
    }
}

void range_update(int node, int lo, int hi, int i, int j, int val)
{    
    if (lo > hi || lo > j || hi < i)
        return;
    else if (lo >= i && hi <= j)
    {
        tree[node] = val;
    }
    else
    {
        push_down(node, lo, hi);
        
        int mid = (lo + hi) / 2;
        
        range_update(node*2, lo, mid, i, j, val);
        range_update(node*2+1, mid+1, hi, i, j, val);
    }
}

void query(int node, int lo, int hi, int i, int j, std::set<int>& output)
{    
    if (lo > hi || lo > j || hi < i)
        return;
    else if (tree[node] != 0 || lo == hi)
        output.insert(tree[node]);
    else
    {
        int mid = (lo + hi) / 2;
        
        query(node*2, lo, mid, i, j, output);
        query(node*2+1, mid+1, hi, i, j, output);
    }
}

int main()
{
    int tests;
    std::scanf("%d", &tests);
    
    while (tests--)
    {
        int n;
        std::scanf("%d", &n);
        
        std::vector<int> coord; // for coord compression
        std::vector<Poster> vec (n);
        
        // Input
        for (int i = 0; i < n; ++i)
        {
            int l, r;
            std::scanf("%d %d", &l, &r);
            
            vec[i].a = l;
            vec[i].b = r;
            coord.push_back(l);
            coord.push_back(r);
        }
        
        // Transform input vec with coord compression
        std::sort(coord.begin(), coord.end());
        int mx = 0;
        
        for (auto& elem: vec)
        {
            elem.a = std::distance(std::begin(coord), std::lower_bound(coord.begin(), coord.end(), elem.a));
            elem.b = std::distance(std::begin(coord), std::lower_bound(coord.begin(), coord.end(), elem.b));
            
            if (elem.a > elem.b)
                std::swap(elem.a, elem.b);
            
            mx = std::max(mx, elem.b);
        }
        
        // Clear Segtree
        std::memset(tree, 0, sizeof(int) * 1000000);
        
        // Put each poster with coor [a, b] with color i+1
        for (int i = 0; i < n; ++i)
        {
            range_update(1, 0, mx, vec[i].a, vec[i].b, i+1);
        }
        
        // Result
        std::set<int> res {};
        query(1, 0, mx, 0, mx, res);
        res.erase(0);
        
        std::printf("%d\n", res.size());
    }

    return 0;
}
