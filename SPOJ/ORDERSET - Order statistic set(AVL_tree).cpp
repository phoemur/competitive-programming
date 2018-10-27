/*ORDERSET - Order statistic set
#tree #binary-search

English 	Vietnamese

In this problem, you have to maintain a dynamic set of numbers which support the two fundamental operations

    INSERT(S,x): if x is not in S, insert x into S
    DELETE(S,x): if x is in S, delete x from S

and the two type of queries

    K-TH(S) : return the k-th smallest element of S
    COUNT(S,x): return the number of elements of S smaller than x

Input

    Line 1: Q (1 ≤ Q ≤ 200000), the number of operations
    In the next Q lines, the first token of each line is a character I, D, K or C meaning that the corresponding operation is INSERT, DELETE, K-TH or COUNT, respectively, following by a whitespace and an integer which is the parameter for that operation.

If the parameter is a value x, it is guaranteed that 0 ≤ |x| ≤ 109. If the parameter is an index k, it is guaranteed that 1 ≤ k ≤ 109.
Output

For each query, print the corresponding result in a single line. In particular, for the queries K-TH, if k is larger than the number of elements in S, print the word 'invalid'.
Example

Input
8
I -1
I -1
I 2
C 0
K 2
D -1
K 1
K 2

Output
1
2
2
invalid

*/

#include <bits/stdc++.h>

template<typename T>
class AvlTree {
    // node of the tree
    struct Node {
        Node* left; // owning left and right pointers
        Node* right;
        T data;
        int height;
        int sum;
        
        template<typename X = T>
        Node(X&& ele, Node* lt, Node* rt, int h = 0, int s = 1)
            :  left{lt}, right{rt}, data{std::forward<X>(ele)}, height{h}, sum{s} {}
                
        Node(const Node&) = delete; // must use clone method
        Node& operator=(const Node&) = delete;
                
        ~Node() noexcept
        {
            if (left  != nullptr) delete left;
            if (right != nullptr) delete right;
        }
    };
    
    // top of the tree
    Node* root;
    
    // Number of elements
    std::size_t sz;
       
public:
    // constructors block
    AvlTree() : root{nullptr}, sz{0} {}
    AvlTree(const AvlTree& other)
        : root{clone(other.root)}, sz{other.sz} {}
        
    AvlTree& operator=(const AvlTree& other) 
    {
        // copy and swap idiom
        AvlTree tmp (other);
        std::swap(root, tmp.root);
        std::swap(sz, tmp.sz);

        return *this;
    }
    
    AvlTree(AvlTree&& other) noexcept
        : AvlTree()
    {
        std::swap(root, other.root);
        std::swap(sz, other.sz);
    }
    
    AvlTree& operator=(AvlTree&& other) noexcept
    {
        std::swap(root, other.root);
        std::swap(sz, other.sz);
        return *this;
    }
    
    ~AvlTree() noexcept
    {
        if (root != nullptr) delete root;
    }
    
    template<typename Iter>
    AvlTree(Iter first, Iter last)
        : AvlTree()
    {
        using c_tp = typename std::iterator_traits<Iter>::value_type;
        static_assert(std::is_constructible<T, c_tp>::value, "Type mismatch");
        
        for (auto it = first; it != last; std::advance(it, 1)) {
            insert(*it);
        }
    }
    
    AvlTree(const std::initializer_list<T> lst)
        : AvlTree(std::begin(lst), std::end(lst)) {}

    AvlTree& operator=(std::initializer_list<T> lst)
    {
        // copy and swap idiom
        AvlTree tmp (lst);
        std::swap(root, tmp.root);
        std::swap(sz, tmp.sz);

        return *this;
    }
    
    // member functions block
    inline bool empty() const noexcept
    {
        return root == nullptr;
    }
    
    inline const std::size_t& size() const noexcept
    {
        return sz;
    }
    
    template<typename X = T,
             typename... Args>
    void insert(X&& first, Args&&... args)
    {
        insert_util(std::forward<X>(first), root);
        ++sz;
        insert(std::forward<Args>(args)...);
    }
    
    template<typename X = T>
    void insert(X&& first)
    {
        insert_util(std::forward<X>(first), root);
        ++sz;
    }
    
    template<typename X = T,
             typename... Args>
    void remove(const X& first, Args&&... args) noexcept
    {
        remove_util(first, root);
        --sz;
        remove(std::forward<Args>(args)...);
    }
    
    void remove(const T& first) noexcept
    {
        remove_util(first, root);
        --sz;
    }
    
    const T& min_element() const
    {
        if (empty()) throw std::logic_error("Empty container");
        return findMin(root)->data;
    }
    
    const T& max_element() const
    {
        if (empty()) throw std::logic_error("Empty container");
        return findMax(root)->data;
    }
    
    void clear() noexcept
    {
        if (root != nullptr) delete root;
        root = nullptr;
    }
        
    bool search(const T& x) const noexcept
    {
        return search(x, root);
    }
    
    const T find_by_order(int k) const noexcept
    {
        return find_by_order(k, root);
    }
    
    int order_of_key(const T& k) const noexcept
    {
        int ans = order_of_key(k, root);
        
        if (this->search(k))
            return ans - 1;
        else
            return ans;
    }
    
private:
    Node* clone(Node* t) const
    {
        if (t == nullptr) 
            return nullptr;
        else
            return new Node(t->data, clone(t->left), clone(t->right), t->height, t->sum);
    }
    
    const T find_by_order(int k, Node* r) const noexcept
    {
        if (r == nullptr)
            return 0;
        
        int left = get_sum(r->left);
        
        if (left == k)
            return r->data;
        else if (k < left)
            return find_by_order(k, r->left);
        else
            return find_by_order(k - left - 1, r->right);
    }
    
    int order_of_key(const T& k, Node* r) const noexcept
    {
        if (r == nullptr)
            return 0;
        else if (k < r->data)
            return order_of_key(k, r->left);
        else if (k == r->data)
            return get_sum(r->left) + 1;
        else
            return get_sum(r->left) + 1 + order_of_key(k, r->right);
    }
    
    inline int height(Node* t) const noexcept
    {
        return t == nullptr ? -1 : t->height;
    }
       
    // binary search an element in the tree
    bool search(const T& x, Node* t) const noexcept
    {
        while( t != nullptr )
            if( x < t->data )
                t = t->left;
            else if( t->data < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    template<typename X = T>
    void insert_util(X&& x, Node*& t)
    {
        if (t == nullptr)
            t = new Node(std::forward<X>(x), nullptr, nullptr);
        else if (x < t->data)
            insert_util(std::forward<X>(x), t->left);
        else if (x > t->data)
            insert_util(std::forward<X>(x), t->right);
        else //duplicate key
            --sz;
        
        balance(t);
    }
    
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove_util(const T& x, Node*& t) noexcept
    {
        if(t == nullptr){
            ++sz;
            return;   // Item not found; do nothing
        } 
        
        if(x < t->data)
            remove_util(x, t->left);
        else if(t->data < x)
            remove_util(x, t->right);
        else if(t->left != nullptr && t->right != nullptr) { // Two children
            t->data = findMin(t->right)->data;
            remove_util(t->data, t->right);
        }
        else { // One child
            Node *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            
            // Avoid propagation of destructors setting nullptr
            oldNode->left = nullptr;
            oldNode->right = nullptr;
            
            delete oldNode;
        }
        
        balance(t);
    }
    
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    Node* findMin(Node* t) const noexcept
    {
        if(t != nullptr)
            while (t->left != nullptr)
                t = t->left;
        
        return t;
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    Node* findMax(Node* t) const noexcept
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
            
        return t;
    }
    
    int get_sum(Node* t) const noexcept
    {
        if (t == nullptr)
            return 0;
        else
            return t->sum;
    }
    
    void balance(Node*& t) noexcept
    {
        static const int ALLOWED_IMBALANCE = 1;
        
        if(t == nullptr) return;
        
        if(height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {
            if(height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        }
        else if(height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
            if(height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);
        }
        
        t->height = std::max(height(t->left), height(t->right)) + 1;
        t->sum = get_sum(t->left) + get_sum(t->right) + 1;
    }
    
    
    // Rotations block
    
    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild(Node*& k2) noexcept
    {
        Node *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = std::max(height(k2->left), height(k2->right)) + 1;
        k2->sum = get_sum(k2->left) + get_sum(k2->right) + 1;
        k1->height = std::max(height(k1->left), k2->height) + 1;
        k1->sum = get_sum(k1->left) + get_sum(k1->right) + 1;
        k2 = k1;
    }
    
    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild(Node*& k1) noexcept
    {
        Node *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = std::max(height(k1->left), height(k1->right)) + 1;
        k1->sum = get_sum(k1->left) + get_sum(k1->right) + 1;
        k2->height = std::max(height(k2->right), k1->height) + 1;
        k2->sum = get_sum(k2->left) + get_sum(k2->right) + 1;
        k1 = k2;
    }
    
    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild(Node*& k3) noexcept
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild(Node*& k1) noexcept
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
}; // end of class avltree



int main()
{
    std::ios_base::sync_with_stdio(false);
    
    AvlTree<int> tree {};
    
    int q;
    std::cin >> q;
    
    while (q--)
    {
        char op;
        int x;
        std::cin >> op >> x;
        
        switch(op)
        {
            case 'I':
                tree.insert(x);
                break;
            case 'D':
                tree.remove(x);
                break;
            case 'K':
            {
                if (x > tree.size())
                    std::cout << "invalid" << std::endl;
                else
                    std::cout << tree.find_by_order(x-1) << std::endl;
                    
                break;
            }
            case 'C':
                std::cout << tree.order_of_key(x) << std::endl;
                break;
            default:
                break;
        }
    }
    
    return 0;
}
