#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

unsigned long long getBattery(const string& number) {
    int n = number.length();
    int toKeep = 12;
    int toRemove = n - toKeep;
    
    vector<char> result;
    
    for (int i = 0; i < n; i++) {
        // While we can still remove digits AND current digit is larger than top of stack
        // Pop smaller digits to make room for larger ones
        while (!result.empty() && 
               toRemove > 0 && 
               result.back() < number[i]) {
            result.pop_back();
            toRemove--;
        }
        
        result.push_back(number[i]);
    }
    
    // If we still need to remove digits, remove from the end
    while (toRemove > 0) {
        result.pop_back();
        toRemove--;
    }
    
    // Convert to number
    string resultStr(result.begin(), result.end());
    return stoull(resultStr);
}

int main() {
    string line;
    vector<string> numbers;
    unsigned long long sum = 0;
    
    while (getline(cin, line)) {
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (!line.empty()) {
            numbers.push_back(line);
        }
    }
    
    for (const auto& num : numbers) {
        unsigned long long battery = getBattery(num);
        cout << num << " -> " << battery << endl;
        sum += battery;
    }
    
    cout << "\nTotal sum: " << sum << endl;
    
    return 0;
}        unsigned long long battery = getBattery(num);

