#include <iostream>
#include <vector>
#include <string>
#include <sstream>
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
    return static_cast<unsigned long>(log10(number)) + 1;
}

// pow(10, n) as unsigned long
unsigned long pow_10(unsigned long n) {
    return static_cast<unsigned long>(pow(10.0, static_cast<double>(n)));
}

// Calculate multiplier based on number of digits
unsigned long getMultiplier(unsigned long numDigits) {
    unsigned long halfDigits = numDigits / 2;
    return pow_10(halfDigits) + 1;
}

// Get the smallest invalid (multiple of multiplier) >= number
unsigned long getSmallestInvalid(unsigned long number, unsigned long multiplier) {
    unsigned long k = number / multiplier;
    if (number % multiplier != 0) ++k;
    return multiplier * k;
}

// Get the largest invalid (multiple of multiplier) <= number
unsigned long getLargestInvalid(unsigned long number, unsigned long multiplier) {
    unsigned long k = number / multiplier;
    return multiplier * k;
}

unsigned long getSum(unsigned long num) {
    return num * (num + 1) / 2;
}

unsigned long getSumofInvalids(unsigned long lower, unsigned long upper, unsigned long multiplier) {
    if (lower == upper) return lower;
    unsigned long lower_sum = lower - multiplier;
    return multiplier * (getSum(upper / multiplier) - getSum(lower_sum / multiplier));
}

// Function to count invalid IDs in a range
unsigned long countInvalidIds(unsigned long lower, unsigned long upper) {
    unsigned long minInvalid = 0;
    unsigned long maxInvalid = 0;

    unsigned long smallDigits = countDigits(lower);
    unsigned long largeDigits = countDigits(upper);

    unsigned long global_result = 0;
    bool minInvalidPreset = false;

    // If lower has odd digits, jump to the first invalid in the next even-digit regime
    if (smallDigits % 2 != 0) {
        // Example: 7 digits -> first invalid in 8-digit regime = 10^7 + 10^3 = 10001000
        minInvalid = pow_10(smallDigits) + pow_10(smallDigits / 2);
        smallDigits++;

        // Only preserve this pre-set minInvalid if we are directly going into the final regime
        if (smallDigits == largeDigits) {
            minInvalidPreset = true;
        }
    }

    // If upper has odd digits, clamp to previous even-digit regime
    if (largeDigits % 2 != 0) {
        largeDigits--;
        upper = pow_10(largeDigits) - 1;
    }

    cout << "\n\n Num digits in lower range: " << smallDigits
         << "\t Num digits in upper range: " << largeDigits;

    unsigned long multiplier = getMultiplier(smallDigits);

    // Process full even-digit regimes strictly between smallDigits and largeDigits
    while (smallDigits < largeDigits) {
        // For these intermediate regimes, we always recompute minInvalid from the current lower
        minInvalidPreset = false;

        minInvalid = getSmallestInvalid(lower, multiplier);
        maxInvalid = pow_10(smallDigits) - 1;

        global_result += getSumofInvalids(minInvalid, maxInvalid, multiplier);
        cout << "\n Lower range: " << lower << "\t Upper range: " << upper
             << "\t Min Invalid: " << minInvalid << "\t Max Invalid: " << maxInvalid
             << "\t multiplier: " << multiplier;

        smallDigits += 2;
        multiplier = getMultiplier(smallDigits);
    }

    // Count remaining invalid IDs in the final regime
    if (smallDigits == largeDigits) {
        // If we had a pre-set minInvalid from the odd-digit lower case and we
        // directly entered this final regime, keep it. Otherwise, compute from lower.
        if (!minInvalidPreset) {
            multiplier = getMultiplier(smallDigits);
            minInvalid = getSmallestInvalid(lower, multiplier);
        } else {
            multiplier = getMultiplier(smallDigits);
        }

        if (minInvalid == upper) {
            return global_result + minInvalid;
        } else if (minInvalid > upper) {
            return global_result;
        }

        maxInvalid = getLargestInvalid(upper, multiplier);
        cout << "\n Lower range: " << lower << "\t Upper range: " << upper
             << "\t Min Invalid: " << minInvalid << "\t Max Invalid: " << maxInvalid
             << "\t multiplier: " << multiplier;

        global_result += getSumofInvalids(minInvalid, maxInvalid, multiplier);
        cout << "\n Result: " << global_result;
    }

    return global_result;
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
