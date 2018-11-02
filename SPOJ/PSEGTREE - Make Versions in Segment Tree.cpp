/*PSEGTREE - Make Versions in Segment Tree
no tags 

You have an array of N integers, named Version-0 array.
You need to do Q queries. There are 2 type of queries.

    idx pos v: Take Version-idx array and copy it into another array. Name the new array Version-K array where K = (number of queries of 1st type before this query + 1). Then add v the element at index pos in Version-K array.
    idx l r: In Version-idx array, sum the elements from index l to r. Print the sum of the range

Input

First line there will be an integer N < 100001, the length of the array. The following line wil contain N integers, the elements of Version-0 array. Each element is non-negative and at most 100.

The next line will contain an integer Q, the number of queries. Next Q lines will contain the queries. All queries in form

a b c d

If a = 1, then you have first kind of query and idx = b, pos = c, v = d.

If a = 2, then you have second kind of query and idx = b, l = c, r = d.

For all queries, it is guaranteed that Version-idx array exists. And

1 <= pos <= N
1 <= l <= r <= N
1 <= v <= 100
Output

If you incounter an query of second type, you need to print the required sum in a seperate line. These should be printed in the order they appears in the input.
Example

Input:
10
1 2 3 4 5 6 7 8 9 10 
5
2 0 1 6
1 0 10 30
1 1 2 10
1 2 3 10
2 3 2 3

Output:
21
25

*/

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

struct Node {
    int value;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    
    Node(int v, const std::shared_ptr<Node>& l, const std::shared_ptr<Node>& r)
        : value{v}, left{l}, right{r} {}
};

int arr[100002]; // Input array
std::vector<std::shared_ptr<Node>> versions; // Persistent segment Tree versions

// Build Version 0 of tree
void build(std::shared_ptr<Node>& node, int lo, int hi)
{
    if (lo == hi) // Leaf Node
        node->value = arr[lo];
    else
    {
        int mid = (lo + hi) / 2;
        node->left  = std::make_shared<Node>(0, nullptr, nullptr);
        node->right = std::make_shared<Node>(0, nullptr, nullptr);
        
        build(node->left, lo, mid);
        build(node->right, mid+1, hi);
        
        node->value = node->left->value + node->right->value;
    }
}

int query(const std::shared_ptr<Node>& node, int lo, int hi, int i, int j)
{
    if (lo > hi || lo > j || hi < i) // No overlap
        return 0;
    else if (lo >= i && hi <= j) // Total overlap
        return node->value;
    else // Partial overlap
    {
        int mid = (lo + hi) / 2;
        
        int q1 = query(node->left, lo, mid, i, j);
        int q2 = query(node->right, mid+1, hi, i, j);
        
        return q1 + q2;
    }
}

/** 
 * Upgrades to new Version 
 * @param prev : points to node of previous version 
 * @param cur  : points to node of current version 
 * Time Complexity : O(logn) 
 * Space Complexity : O(logn)  */
void upgrade(std::shared_ptr<Node>& prev, std::shared_ptr<Node>& cur, int lo, int hi, int idx, int value) 
{ 
    int mid = (lo + hi) / 2;
    
    if (idx > hi || idx < lo || lo > hi) 
        return; 
    else if (lo == hi) // modification in new version 
    { 
        cur->value = prev->value + value; 
    }
    else if (idx <= mid) 
    { 
        // link to right child of previous version 
        cur->right = prev->right; 
  
        // create new node in current version 
        cur->left = std::make_shared<Node>(0, nullptr, nullptr);
  
        upgrade(prev->left,cur->left, lo, mid, idx, value);
        
        cur->value = cur->left->value + cur->right->value;
    } 
    else
    { 
        // link to left child of previous version 
        cur->left = prev->left; 
  
        // create new node for current version 
        cur->right = std::make_shared<Node>(0, nullptr, nullptr);
  
        upgrade(prev->right, cur->right, mid+1, hi, idx, value);
        
        cur->value = cur->left->value + cur->right->value;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    versions.clear();
    versions.push_back(std::make_shared<Node>(0, nullptr, nullptr));
    
    int n;
    std::cin >> n;
    
    for (int i = 0; i < n; ++i)
        std::cin >> arr[i];
    
    build(versions[0], 0, n-1);
    
    int queries;
    std::cin >> queries;
    
    while (queries--)
    {
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        
        if (a == 1)
        {
            versions.push_back(std::make_shared<Node>(0, nullptr, nullptr));
            
            upgrade(versions[b], versions.back(), 0, n-1, c-1, d);
        }
        else
        {
            std::cout << query(versions[b], 0, n-1, c-1, d-1) << std::endl;
        }
    }
    
    return 0;
}
