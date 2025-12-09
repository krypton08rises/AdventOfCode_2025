#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>


// Function to load aoc_day8.txt file
// numbers in format x1, y1, z1\n x2, y2, z2\n ... save to 3 vector<
std::tuple<std::vector<int>, std::vector<int>, std::vector<int>> loadFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return std::make_tuple(std::vector<int>(), std::vector<int>(), std::vector<int>());
    }

    std::vector<int> x, y, z;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string token;
        int values[3], idx = 0;
        while (std::getline(ss, token, ',')) {
            values[idx++] = std::stoi(token);
        }
        if (idx == 3) {
            x.push_back(values[0]);
            y.push_back(values[1]);
            z.push_back(values[2]);
        }
    }
    file.close();
    return std::make_tuple(x, y, z);
}
//Use KD-tree for distance estimation?
//Estimate distance between two 3D points
double estimateDistance(int x1, int y1, int z1, int x2,
                        int y2, int z2) {
    return std::sqrt(std::pow(x2 - x1, 2) +
                        std::pow(y2 - y1, 2) +
                        std::pow(z2 - z1, 2));
}
