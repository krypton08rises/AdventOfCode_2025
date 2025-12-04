#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <limits>
#include <cstdlib>

using namespace std;

// Function to parse a range string "start-end" into a pair of integers
pair<int,int> parseRange(const string& rangeStr) {
    size_t dashPos = rangeStr.find('-');
    int start = stoll(rangeStr.substr(0, dashPos));
    int end = stoll(rangeStr.substr(dashPos + 1));
    return make_pair(start, end);
}

// Check number of digits in a number
int countDigits(int number) {
    if (number <  10) return 1;
    return static_cast<int>(log10(number)) + 1;
}

// bool checkInvalid(int number ){
//   string firstHalf = to_string(number);

// }

// Calculate multiplier based on number of digits
int getMultiplier(int numDigits) {
    int halfDigits = numDigits / 2;
    return static_cast<int>(pow(10, halfDigits)) + 1;
}

// Get the smallest mirror number greater than or equal to a given number
int getSmallestInvalid(int number) {
    string numStr = to_string(number);
    int len = numStr.length();
    string firstHalf = numStr.substr(0, (len) / 2);
    string invalidNum = firstHalf + firstHalf;

    if (stoll(invalidNum) >= number) {
        return stoll(invalidNum);
    } else {
        // Increment the first half and form the mirror again
        int firstHalfNum = stoll(numStr.substr(0, len / 2)) + 1;
        invalidNum = to_string(firstHalfNum);
        return stoll(invalidNum + invalidNum);
  }
}

// Get the largest mirror number less than or equal to a given number
int getLargestInvalid(long number) {
    string numStr = to_string(number);
    int len = numStr.length();
    string firstHalf = numStr.substr(0, (len + 1) / 2);
    string invalidNum = firstHalf + firstHalf;
    if (stoll(invalidNum) <= number){
      return stoll(invalidNum);
    }
    else {
      int firstHalf = stoll(numStr.substr(0, len / 2)) - 1;
      invalidNum = to_string(firstHalf);
      return stoll(invalidNum + invalidNum);
    }
}

string getInvalids(long lower, long upper, long multiplier){
  if (lower == upper){
    return to_string(lower);
  }
  string results = "";
  while (lower < upper) {
    results += to_string(lower);
    lower += multiplier;
  }
  return results;
}
// int numInvalids(long lower, long upper, long multiplier){
//     if (upper < lower) return 0;
//     return ((upper - lower) / multiplier) + 1;
// }

// Function to count invalid IDs in a range
string countInvalidIds(long lower, long upper) {
    int minInvalid;
    int maxInvalid;

    int smallDigits = countDigits(lower);
    int largeDigits = countDigits(upper);

    string global_result = "";
    // If lower has odd digits, skip to next even digit count
    if (smallDigits % 2 != 0) {
        minInvalid = static_cast<int>(pow(10, smallDigits));
        smallDigits++;
    }
    if (largeDigits % 2 != 0 ){
        maxInvalid = static_cast<int>(pow(10, largeDigits - 1));
        largeDigits--;
    }
    minInvalid = getSmallestInvalid(lower);
    maxInvalid = getLargestInvalid(upper);
    cout << "\n\nMin Range: " << lower << "\t Max Range: " << upper << "\t Min Invalid" << minInvalid << "\t Max Invalid" << maxInvalid;
    cout << "\nSmallest invalid <= " << getSmallestInvalid(minInvalid)
             << "\t Largest invalid >=: " << getLargestInvalid(maxInvalid) << "\t Small Digits: "<< smallDigits << "\t Large Digits: " << largeDigits;

    // Process ranges by digit count (incrementing by 2 for even digits only)
    while (smallDigits < largeDigits) {
        int multiplier = getMultiplier(smallDigits);
        int nextMaxMirror = static_cast<int>(pow(10, smallDigits)) + static_cast<int>(pow(10, smallDigits / 2)) - multiplier;
        global_result += getInvalids(minInvalid, nextMaxMirror, multiplier);
        cout << "\nCounting invalid IDs from " << minInvalid << " to " << nextMaxMirror << " with multiplier " << multiplier << ": " << global_result;

        smallDigits += 2;
        minInvalid = static_cast<int>(pow(10, smallDigits - 1)) + static_cast<int>(pow(10, smallDigits / 2));
    }

    // Count remaining invalid IDs in the final range
    if (smallDigits == largeDigits && minInvalid <= maxInvalid) {
        int multiplier = getMultiplier(smallDigits);
        global_result += getInvalids(minInvalid, maxInvalid, multiplier);
        cout << "\nCounting invalid IDs from " << minInvalid << " to " << maxInvalid
             << " with multiplier " << multiplier << ": " << global_result;
    }
    return global_result;
}

int main() {
    string input;
    getline(cin, input);

    vector<pair<int, int>> ranges;
    stringstream ss(input);
    string rangeStr;
    string results;
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
