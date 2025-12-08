#include <bits/stdc++.h>
using namespace std;

vector<pair<unsigned long long, unsigned long long>>
mergeRanges(vector<pair<unsigned long long, unsigned long long>> ranges) {
    if (ranges.empty()) return {};

    // Sort by start, then end
    sort(ranges.begin(), ranges.end());

    vector<pair<unsigned long long, unsigned long long>> merged;
    auto cur = ranges[0];

    for (size_t i = 1; i < ranges.size(); ++i) {
        auto &next = ranges[i];

        if (next.first <= cur.second) {
            // Overlap: extend current range
            if (next.second > cur.second)
                cur.second = next.second;
        } else {
            // No overlap: push current and start new
            merged.push_back(cur);
            cur = next;
        }
    }
    merged.push_back(cur);
    return merged;
}

unsigned long long numFresh(const vector<pair<unsigned long long, unsigned long long>>& ranges) {
    unsigned long long sum = 0;
    for (const auto &r : ranges) {
        sum += (r.second - r.first + 1);
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
    string line;
    // --- Read ranges until an empty line ---
    while (true) {
        if (!getline(fin, line)) break;      // EOF
        if (line.empty()) break;             // blank line → stop

        unsigned long long a, b;
        char dash;
        stringstream ss(line);
        ss >> a >> dash >> b;
        ranges.emplace_back(a, b);
    }
    ranges = mergeRanges(ranges);
    unsigned long long result = numFresh(ranges);

    cout << "\nResult: " << result;
    return 0;
}
