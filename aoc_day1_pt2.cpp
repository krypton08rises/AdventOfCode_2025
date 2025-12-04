#include<iostream>
#include<vector>
#include<fstream>
#include<string>

using namespace std;

std::vector<std::string> loadInput(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

int dial( const std::vector<std::string>& input) {
    int count = 0;

    int position = 50;
    int old_position = 50;
    for (const auto& line : input) {
        // cout << line[0];
        if (line[0] == 'L') {
            position -= std::stoi(line.substr(1));
        } else if (line[0] == 'R') {
            position += std::stoi(line.substr(1));
        }

        if (position < 0 && old_position == 0){
          count += (abs(position)/100);
        }
        else if (position < 0){
          count += (abs(position)/100) + 1;
        }
        else if (position==0){
          count+=1;
        }
        else {
          count+=(position/100);
        }

        position%=100;
        if (position < 0)
          position += 100;
        // cout << "\nline: " << line << "\tOld Position" << old_position << "\tposition: " << position << "\t Count: " << count;
        old_position = position;
    }
    return count;
}

int main() {
    std::cout << "Hello, Advent of Code Day 1!" << std::endl;
    // Loading input file:
    std::string line;
    std::vector<std::string> all_lines;

    // Read lines until an empty line is encountered
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            break; // Exit the loop if the line is empty
        }
        all_lines.push_back(line); // Store the line in a vector
    }
    std::cout << "\nYou entered the following lines:" << std::endl;

    int result = dial(all_lines);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
