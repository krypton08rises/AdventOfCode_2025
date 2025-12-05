#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>
#include <cmath>

using namespace std;

// Function to parse a range string "start-end" into a pair of integers
pair<unsigned long, unsigned long> parseRange(const string& rangeStr) {
    size_t dashPos = rangeStr.find('-');
    unsigned long start = stoul(rangeStr.substr(0, dashPos));
    unsigned long end = stoul(rangeStr.substr(dashPos + 1));
    return make_pair(start, end);
}

// Check number of digits in a number
unsigned long countDigits(unsigned long number) {
    if (number < 10) return 1;
    return static_cast<unsigned long>(log10(static_cast<long double>(number))) + 1;
}

// Integer 10^n
unsigned long pow_10(unsigned long n) {
    unsigned long res = 1;
    while (n--) res *= 10;
    return res;
}

// Function to count (and sum) invalid IDs in a range for Part Two
// An ID is invalid if it is some block B repeated k >= 2 times.
unsigned long countInvalidIds(unsigned long lower, unsigned long upper) {
    if (lower > upper) return 0;

    unordered_set<unsigned long> seen;   // to avoid double-counting
    unsigned long total = 0;

    unsigned long minDigits = countDigits(lower);
    unsigned long maxDigits = countDigits(upper);

    for (unsigned long n = minDigits; n <= maxDigits; ++n) {
        // Clamp to this digit-length band [10^(n-1), 10^n - 1]
        unsigned long bandLow  = pow_10(n - 1);
        unsigned long bandHigh = pow_10(n) - 1;

        unsigned long L = (lower > bandLow) ? lower : bandLow;
        unsigned long U = (upper < bandHigh) ? upper : bandHigh;
        if (L > U) continue;

        // For this digit length n, consider all block lengths m dividing n
        // with k = n/m >= 2.
        for (unsigned long m = 1; m <= n / 2; ++m) {
            if (n % m != 0) continue;
            unsigned long k = n / m;
            if (k < 2) continue;

            // R(n,m) = (10^n - 1) / (10^m - 1)
            unsigned long ten_n = pow_10(n);
            unsigned long ten_m = pow_10(m);
            unsigned long denom = ten_m - 1;
            if (denom == 0) continue; // m = 0 can't happen, but safety
            unsigned long R = (ten_n - 1) / denom;

            // B-range from [L, U]:
            // L <= B * R <= U  =>  L/R <= B <= U/R
            unsigned long B_min = L / R;
            if (L % R != 0) ++B_min;
            unsigned long B_max = U / R;

            // Also B must be an m-digit number with no leading zero
            unsigned long blockLow  = pow_10(m - 1);
            unsigned long blockHigh = ten_m - 1;

            if (B_min < blockLow)  B_min = blockLow;
            if (B_max > blockHigh) B_max = blockHigh;
            if (B_min > B_max) continue;

            // Generate all X = B * R for B in [B_min, B_max]
            for (unsigned long B = B_min; B <= B_max; ++B) {
                unsigned long X = R * B;

                // Extra safety clamp
                if (X < lower || X > upper) continue;

                // Deduplicate across different (n,m) decompositions
                if (seen.insert(X).second) {
                    total += X;
                }
            }
        }
    }

    return total;
}

int main() {
    string input;
    getline(cin, input);

    vector<pair<unsigned long, unsigned long>> ranges;
    stringstream ss(input);
    string rangeStr;
    unsigned long results = 0;

    // Split input by commas and parse each range
    while (getline(ss, rangeStr, ',')) {
        ranges.push_back(parseRange(rangeStr));
    }

    // Process each range
    for (const auto& range : ranges) {
        results += countInvalidIds(range.first, range.second);
        cout << "\nResult State: " << results;
    }

    cout << endl;
    return 0;
}
