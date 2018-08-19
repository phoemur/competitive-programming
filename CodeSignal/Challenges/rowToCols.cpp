// reverse challenge https://app.codesignal.com/challenge/LfWCaKHdmeCQk6jZP

auto rowsToCols(vector<int> rows) {
    vector<int> res;
    vector<vector<bool>> table;
    
    transform(begin(rows), end(rows), back_inserter(table), [&](int a){
        vector<bool> num (sizeof(int) << 3);
        for (int i=0; i<num.size(); ++i) {
            num[i] = a >> i & 1;
        }
        
        num.erase(begin(num) + rows.size(), end(num));
        
        return num;
    });
    
    // Transpose
    for (int i=0; i<table.size(); ++i) {
        for (int j=i; j<table.size(); ++j) {
            swap(table[i][j], table[j][i]);
        }
    }
    

    transform(table.rbegin(), table.rend(), back_inserter(res), [&](auto& a){
        return accumulate(a.begin(), 
                          a.end(), 
                          0L, 
                          [](long x, bool y) {return (x << 1) + y;});
    });
    
    return res;
}
