/*BRCKTS - Brackets
#tree

We will call a bracket word any word constructed out of two sorts of characters: the opening bracket "(" and the closing bracket ")". Among these words we will distinguish correct bracket expressions. These are such bracket words in which the brackets can be matched into pairs such that

    every pair consists of an opening bracket and a closing bracket appearing further in the bracket word
    for every pair the part of the word between the brackets of this pair has equal number of opening and closing brackets

On a bracket word one can do the following operations:

    replacement -- changes the i-th bracket into the opposite one
    check -- if the word is a correct bracket expression

Task

Write a program which

    reads (from standard input) the bracket word and the sequence of operations performed,
    for every check operation determines if the current bracket word is a correct bracket expression,
    writes out the outcome (to standard output).

Input

Ten test cases (given one under another, you have to process all!). Each of the test cases is a series of lines. The first line of a test consists of a single number n (1<=n<=30000) denoting the length of the bracket word. The second line consists of n brackets, not separated by any spaces. The third line consists of a single number m -- the number of operations. Each of the following m lines carries a number k denoting the operation performed. k=0 denotes the check operation, k>0 denotes replacement of k-th bracket by the opposite.
Output

For every test case your program should print a line:
Test i:
where i is replaced by the number of the test and in the following lines, for every check operation in the i-th test your program should print a line with the word YES, if the current bracket word is a correct bracket expression, and a line with a word NO otherwise. (There should be as many lines as check operations in the test.)
Example

Input:
4
()((
4
4
0
2
0
[and 9 test cases more]
Output:
Test 1:
YES
NO
[and 9 test cases more]

Warning: large Input/Output data, be careful with certain languages 
*/

#include <algorithm>
#include <iostream>

struct Node {
    int open;
    int closed;
};

char arr[30005];
Node tree[3*30005];

void build_tree(int node, int a, int b)
{
    if (a == b)
    {
        if (arr[a] == '(')
        {
            tree[node].open = 1;
            tree[node].closed = 0;
        }
        else
        {
            tree[node].open = 0;
            tree[node].closed = 1;
        }
    }
    else
    {
        int mid = (a + b) / 2;
        build_tree(node*2, a, mid);
        build_tree(node*2+1, mid+1, b);
        
        // merge
        int change = std::min(tree[2*node].open, tree[2*node+1].closed);
        tree[node].open = tree[2*node].open + tree[2*node+1].open - change;
        tree[node].closed = tree[2*node].closed + tree[2*node+1].closed - change;   
    }
}

Node query_tree(int node, int a, int b, int i, int j)
{
    if (a == i && b == j)
        return tree[node];
    else
    {        
        int mid = (a + b) / 2;
        
        if (i > mid)
            return query_tree(2*node+1, mid+1, b, i, j);
        else if (j <= mid)
            return query_tree(2*node, a, mid, i, j);
        else
        {
            Node res {};
            
            auto left  = query_tree(2*node, a, mid, i, j);
            auto right = query_tree(2*node+1, mid+1, b, i, j);
            
            int change = std::min(left.open, right.closed);
            res.open = left.open + right.open - change;
            res.closed = left.closed + right.closed - change;
            
            return res;
        }
    }
}

inline bool isValid(const Node& n)
{
    return n.open == 0 && n.closed == 0;
}

void update_tree(int node, int a, int b, int idx)
{
    if (a == b) // Leaf node
    {
        arr[idx] = arr[idx] == '(' ? ')' :'(';
        
        if(arr[idx] == '(')
        {
            tree[node].open = 1;
            tree[node].closed = 0;
        }
        else
        {
            tree[node].open = 0;
            tree[node].closed = 1;
        }
    }
    else
    {
        int mid = (a + b) / 2;
        
        if (idx > mid)
            update_tree(node*2+1, mid+1, b, idx);
        else
            update_tree(node*2, a, mid, idx);
        
        int change = std::min(tree[2*node].open, tree[2*node+1].closed);
        tree[node].open = tree[2*node].open + tree[2*node+1].open - change;
        tree[node].closed = tree[2*node].closed + tree[2*node+1].closed - change;   
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    for (int i = 1; i <= 10; ++i)
    {
        int n, queries;
        std::cin >> n;
        std::cin >> arr;
        std::cin >> queries;
        
        build_tree(1, 0, n-1);
        
        std::cout << "Test " << i << ":\n";
        
        while (queries--)
        {
            int num;
            std::cin >> num;
            
            if (num == 0)
            {
                if (isValid(query_tree(1, 0, n-1, 0, n-1)))
                    std::cout << "YES\n";
                else
                    std::cout << "NO\n";
            }
            else
            {
                update_tree(1, 0, n-1, num-1);
            }
        }
    }
}
