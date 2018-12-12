/* NHAY - A Needle in the Haystack */
#include <iostream>
#include <string>
#include <vector>

std::vector<int> computeLPSArray(const std::string& pat)
{
    const int n = pat.size(); 
    int len = 0; 

    std::vector<int> lps (n, 0);// lps[0] is always 0 

    // the loop calculates lps[i] for i = 1 to M-1 
    for (int i = 1; i < n;) 
    { 
        if (pat[i] == pat[len])
        { 
            len++; 
            lps[i] = len; 
            i++; 
        } 
        else // (pat[i] != pat[len]) 
        { 
            // This is tricky. Consider the example. 
            // AAACAAAA and i = 7. The idea is similar 
            // to search step. 
            if (len != 0)
            { 
                len = lps[len - 1];
                // Also, note that we do not increment 
                // i here 
            } 
            else // if (len == 0) 
            { 
                lps[i] = 0; 
                i++; 
            } 
        } 
    }
    
    return lps;
}

/* Returns a vector of the indexes of all ocurrences of pat in txt */
std::vector<int> KMPSearch(const std::string& pat, const std::string& txt) 
{ 
    const int m = pat.size();
    const int n = txt.size(); 
    std::vector<int> res;
    
    // create lps[] that will hold the longest prefix suffix   
    // values for pattern 
    auto lps = computeLPSArray(pat);

    int i = 0; // index for txt[] 
    int j = 0; // index for pat[] 
    while (i < n) 
    { 
        if (pat[j] == txt[i]) 
        { 
            j++; 
            i++; 
        } 

        if (j == m) 
        { 
            //printf("Found pattern at index %d ", i - j); 
            res.push_back(i - j);
            j = lps[j - 1]; 
        } 

        // mismatch after j matches 
        else if (i < n && pat[j] != txt[i]) 
        { 
            // Do not match lps[0..lps[j-1]] characters, 
            // they will match anyway 
            if (j != 0) 
                j = lps[j - 1]; 
            else
                i = i + 1; 
        } 
    }
    
    return res;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    int n;
    std::string needle, haystack;
    
    while (std::cin >> n) 
    {
        std::cin >> needle >> haystack;
        
        auto matches = KMPSearch(needle, haystack);
        
        for (int idx : matches)
            std::cout << idx << "\n";
        
        std::cout << std::endl;
    }
        
    return 0;
}
