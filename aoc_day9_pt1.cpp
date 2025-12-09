#include <bits/stdc++.h>

// Function to load aoc_day9.txt file
// x1,y1 \n x2,y2 \n ... save to vector<pair<int, int>>

std::vector<std::pair<int, int>> loadFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return std::vector<std::pair<int, int>>();
    }
    std::vector<std::pair<int, int>> points;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string token;

        int values[2], idx = 0;
        while (std::getline(ss, token, ',')) {
            values[idx++] = std::stoi(token);
        }
        if (idx == 2) {
            points.emplace_back(values[0], values[1]);
        }
    }
    file.close();
    return points;
}

// calculate max(( xi - xj + 1) * (yi - yj + 1)) for all points i, j
int calculateMaxArea(const std::vector<std::pair<int, int>>& points) {
    int maxArea = 0;
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = 0; j < points.size(); j++) {
            int area = (std::abs(points[i].first - points[j].first) +
                        std::abs(points[i].second - points[j].second) + 1);
            if (area > maxArea) {
                maxArea = area;
            }
        }
    }

    return maxArea;
}
int main() {
    const std::string filename = "data/aoc_day9_test.txt";
    auto points = loadFile(filename);
    int maxArea = calculateMaxArea(points);
    std::cout << "Maximum Area: " << maxArea << std::endl;
    return 0;
}
