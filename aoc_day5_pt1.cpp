#include <bits/stdc++.h>
using namespace std;


bool checkFresh(const vector<pair<unsigned long long, unsigned long long>>& ranges,
                unsigned long long value) {
    for (auto &r: ranges){
        if (value >= r.first && value <= r.second)
            return true;
    }
    return false;
}

unsigned long long numFresh( const vector<pair<unsigned long log, unsigned long long>>& ranges){
    unsigned long long sum = 0;
    for (auto &r:ranges){
        sum+=(r.second-r.first+1);
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream fin("data/day5.txt");
    if (!fin) {
        cerr << "Failed to open file\n";
        return 1;
    }

    vector<pair<unsigned long long, unsigned long long>> ranges;
    vector<unsigned long long> values;

    string line;

    // --- Read ranges until an empty line ---
    while (true) {
        if (!getline(fin, line)) break;      // EOF
        if (line.empty()) break;             // blank line → stop

        unsigned long long a, b;
        char dash;
        stringstream ss(line);
        ss >> a >> dash >> b;                // read "x-y"
        ranges.emplace_back(a, b);
    }

    // --- Read integers until EOF ---
    unsigned long long x;
    while (fin >> x) values.push_back(x);

    // Optional: print to verify
    unsigned long long result = 0;
    bool fresh = false;
    result = numFresh(ranges);
    // for (unsigned long long v: values) {
    //     cout << "\nChecking if " << v << " is fresh: " ;
    //     fresh = checkFresh(ranges, v);
    //     cout << fresh;
    //     if (fresh) result++;
    // }
    cout << "\nResult: " << result;
    return 0;
}
