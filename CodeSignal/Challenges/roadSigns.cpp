/*Summer road trip time! You and your friends are driving all the way to Banff National Park for a camping trip in the woods.

While staring out of the car window, your friend started reading some road signs in a strange way to break the silence. The messages were all weird, they were nothing like what the road sign wrote when he read it out loud!

Given a sign in its more readable form with sign[i] being one section of the sign, guess what your friend will read out.

Yes, this is a reverse challenge, enjoy!

Example

    For sign = ["You matter.", "Don't give up."], the output should be roadSigns(sign) = "You don't matter. Give up.". What a nice message.

    https://imgur.com/a/VQC15kH

Input / Output

    [execution time limit] 0.5 seconds (cpp)

    [input] array.string sign

    The road sign itself. It is given in its proper form, and is up to you to scramble the words into its garbled message.

    Guaranteed constraints:
    0 < sign.length < 50
    0 < sign[i].length < 237

    [output] string

    The garbled message of the road sign.
*/

#define A auto

string r, roadSigns(A Z) 
{    
    vector<vector<string>> T;
    A x = Z.size();
    
    for (A s: Z) {
        transform(&s[0], &*end(s), &s[0], ::tolower);
        stringstream w {s};
        vector<string> tmp (istream_iterator<string>{w}, 
                            istream_iterator<string>{});
        x = max(x, tmp.size());
        T.push_back(tmp);
    }
    
    for (A i=0; i<x; ++i)
        for (A j=0; j<T.size(); ++j)
            if (i < T[j].size()) {
                // Fix punct and capitalization
                A s = T[j][i];
                if (s[0] < 48) r.pop_back();
                A z = r[r.size()-2];
                if (ispunct(z) && z != 44) s[0] -= 32;
                
                // Append
                r += s;
                r += 32;
            }
    
    r.pop_back();
    r[0] -= 32;
    return r;
}
