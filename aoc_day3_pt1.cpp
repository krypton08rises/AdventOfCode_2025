#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>
using namespace std;

int getBattery(const string& number) {
    int first = 0;  // first digit found 
    int second = 0; // Second  digit
    map<int, deque
    // Iterate through string from right to left (reverse chronological order)
    for (int i = number.length() - 1; i >= 0; i--) {
        int digit = number[i] - '0'; // Convert char to int
        
        if (!second) {
            second = digit;
        }
        else if (!first) {
            first = digit;
        }
        else if (digit >= first) {
            // Found new largest - shift first to second
            if (first > second && i!=0) {
                second = first;
            }
            first = digit;
        }
        // cout << "\ndigit: "<< digit << "\tFirst: " << first << "\tSecond: " << second; 
    }
    
    return first * 10 + second;
}

int main() {
    string line;
    vector<string> numbers;
    long long sum = 0;
    
    // Read input line by line
    while (getline(cin, line)) {
        // Remove whitespace
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
        
        if (!line.empty()) {
            numbers.push_back(line);
        }
    }
    
    // Process each number
    for (const auto& num : numbers) {
        int battery = getBattery(num);
        cout << endl << num << " -> " << battery << endl;
        sum += battery;
    }
    
    cout << "\nTotal sum: " << sum << endl;
    
    return 0;
}