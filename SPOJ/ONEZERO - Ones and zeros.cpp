/*ONEZERO - Ones and zeros
#bfs

Certain positive integers have their decimal representation consisting only of ones and zeros, and having at least one digit one, e.g. 101. If a positive integer does not have such a property, one can try to multiply it by some positive integer to find out whether the product has this property.
Input

Number K of test cases (K is approximately 1000);
in each of the next K lines there is one integer n (1 <= n <= 20000)
Output

For each test case, your program should compute the smallest multiple of the number n consisting only of digits 1 and 0 (beginning with 1).
Example

Input:
3
17
11011
17
Output:
11101
11011
11101

*/

#include <iostream>
#include <queue>
#include <set>
#include <string>


// https://www.geeksforgeeks.org/find-the-smallest-binary-digit-multiple-of-given-number/
bool isBinaryNum(int N) 
{ 
    while (N > 0) 
    { 
        int digit = N % 10; 
        if (digit != 0 && digit != 1) 
            return false; 
        N /= 10; 
    }
    
    return true; 
} 

int mod(const std::string& t, int N) 
{ 
    int r = 0;
    
    for (int i = 0; i < t.size(); i++) 
    { 
        r = r * 10 + (t[i] - '0'); 
        r %= N; 
    }
    
    return r; 
}

std::string solve(int N)
{
    std::queue<std::string> q; 
    std::set<int> visit; 
  
    std::string t = "1"; 
  
    //  In starting push 1 into our queue 
    q.push(t); 
  
    //  loop untill queue is not empty 
    while (!q.empty()) 
    { 
        // Take the front number from queue. 
        t = q.front();      
        q.pop(); 
  
        // Find remainder of t with respect to N. 
        int rem = mod(t, N); 
  
        // if remainder is 0 then we have 
        // found our solution 
        if (rem == 0) 
            return t; 
  
        // If this remainder is not previously seen, 
        // then push t0 and t1 in our queue 
        else if(visit.find(rem) == visit.end()) 
        { 
            visit.insert(rem); 
            q.push(t + "0"); 
            q.push(t + "1"); 
        } 
    }
    
    return t;
}

int main()
{
    int tests;
    std::cin >> tests;
    
    while (tests--)
    {
        int n;
        std::cin >> n;
        
        if (isBinaryNum(n))
            std::cout << n << std::endl;
        else
            std::cout << solve(n) << std::endl;
    }
    
    return 0;
}
