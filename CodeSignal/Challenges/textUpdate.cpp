// Reverse challenge https://app.codesignal.com/challenge/SySpcgPip69rvPvrB

#define S string
#define Z second
#define B(X) begin(X), end(X)
#define A auto

S r, textUpdate(S t) {
    
    vector<pair<int,S>> T;
    stringstream s {t};
    A i=0;
    for (S b; getline(s, b, ' ');) T.emplace_back(i++, b);
    
    stable_sort(B(T), [](A a, A b){
        return  a.Z.size() > b.Z.size();
    });
    
    for (A j=0; j < (T.size() + 1) / 2; ++j)
        reverse(B(T[j].Z));
    
    sort(B(T));
    
    for (A p: T) r += p.Z + " ";
    r.pop_back();
    return r;
}
