/*BLUNIQ - Unique Code
#tree

In Lapak City, every tourist is given a unique code based on their favorite number. If their favorite number is already used as a unique code, that tourist will be given the smallest unused unique code that is larger than his favorite number. For example, a tourist with 42 as his favorite number visits Lapak City. However, unique code 42 is already used. So that tourist is given the unique code 43. If 43 is also used, then that tourist is given the unique code 44, etc.

Every tourist that leaves Lapak City will delete their unique code, that means their code can be used for other newcomer if needed. Continuing the previous example, if the tourist with unique code 43 left Lapak City, and a tourist with favorite number 43 enters, that new tourist will be given the unique code 43.

Initially, all code is unused and no tourist is in Lapak City. On one day, there are N tourist event on Lapak City. Help Lapak City to determine unique code for the tourist.
Input

First line of input is N, the number of event (1 < N < 100000). Next N lines contain the events. For every tourist that visits Lapak City, the input is "1 x", with x is the favorite number of that tourist (1 < x < 1 000 000 000). For every tourist that leaves Lapak City, the input is "2 x", with x is the unique code of that tourist.
Output

For each visiting tourist, output their unique code.
Example

Input:
5
1 42
1 42
1 43
2 43
1 42

Output:
42
43
44
43

*/

#include <algorithm>
#include <cstdio>

static const int INF = 1 << 30;

// Segtree Node
struct Node {
    int value;   // The first free node at this node interval
    
    Node* left;
    Node* right;
    
    Node(int f)
        : value{f}, left{nullptr}, right{nullptr}
    {
        
    }
    
    ~Node() noexcept
    {
        if (left != nullptr)
        {
            delete left;
            left = nullptr;
        }
        
        if (right != nullptr)
        {
            delete right;
            right = nullptr;
        }
    }
};

int query(Node* node, int lo, int hi, int pos)
{
    if (node == nullptr)
        node = new Node(hi);
    
    if (lo == hi)
        return node->value;
    
    int mid = (lo + hi) / 2;
    
    if (node->left == nullptr)
        node->left = new Node(mid);
    if (node->right == nullptr)
        node->right = new Node(hi);
    
    if (node->left->value >= pos)
        return query(node->left, lo, mid, pos);
    else
        return query(node->right, mid+1, hi, pos);
}

void update(Node* node, int lo, int hi, int pos, int val)
{
    if (node == nullptr)
        node = new Node(hi);
    
    if (lo == hi)
    {
        if (lo == pos)
            node->value = val;
    }
    else
    {
        int mid = (lo + hi) / 2;
        
        if (pos <= mid)
            update(node->left, lo, mid, pos, val);
        else
            update(node->right, mid+1, hi, pos, val);
        
        if (node->left == nullptr)
            node->left = new Node(mid);
        if (node->right == nullptr)
            node->right = new Node(hi);
        
        node->value = std::max(node->left->value, node->right->value);
    }
}

int main()
{
    int n;
    std::scanf("%d", &n);
    
    Node* root = new Node(1);
    
    while (n--)
    {
        int op, fav;
        std::scanf("%d %d", &op, &fav);
        
        if (op == 1)
        {
            int p = query(root, 1, INF, fav);
            update(root, 1, INF, p, -1 * INF);
            std::printf("%d\n", p);
        }
        else // op == 2
        {
            update(root, 1, INF, fav, fav);
        }
    }
    
    delete root;
    
    return 0;
}
