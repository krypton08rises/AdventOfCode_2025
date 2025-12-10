#include <bits/stdc++.h>

// Function to load aoc_day9.txt file
// x1,y1 \n x2,y2 \n ... save to vector<pair<int, int>>

std::vector<std::pair<unsigned long, unsigned long>> loadFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return std::vector<std::pair<unsigned long, unsigned long>>();
    }
    std::vector<std::pair<unsigned long, unsigned long>> points;
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
unsigned long calculateMaxArea(const std::vector<std::pair<unsigned long, unsigned long>>& points) {
    unsigned long maxArea = 0;
    for (size_t i = 0; i < points.size()-1; i++) {
        for (size_t j = i+1; j < points.size(); j++) {
            unsigned long area = (std::abs((long)points[i].first - (long)points[j].first) + 1) *
                        (std::abs((long)points[i].second - (long)points[j].second) + 1);
            if (area > maxArea) {
                maxArea = area;
                std::cout << "New max area " << maxArea << " found between points ("
                     << points[i].first << "," << points[i].second << ") and ("
                     << points[j].first << "," << points[j].second << ")" << std::endl;
            }
        }
    }

    return maxArea;
}

// function to check if a single x has more than 2 y values and vice versa
bool hasMultipleYsOrXs(
    const std::unordered_map<unsigned long, std::vector<unsigned long>>& x_to_ys,
    const std::unordered_map<unsigned long, std::vector<unsigned long>>& y_to_xs
) {
    bool flag = false;
    for (const auto& [x, ys] : x_to_ys) {
        if (ys.size() > 2) {
            // print points with this x
            std::cout << "X value " << x << " has Y values: ";
            for (const auto& y : ys) {
                std::cout << y << " ";
            }
            std::cout << std::endl;
            flag = true;
        }
    }
    for (const auto& [y, xs] : y_to_xs) {
        if (xs.size() > 2) {
            // print points with this y
            std::cout << "Y value " << y << " has X values: ";
            for (const auto& x : xs) {
                std::cout << x << " ";
            }
            std::cout << std::endl;
            flag = true;
        }
    }
    return flag;
}


int main() {
    const std::string filename = "data/aoc_day9.txt";
    auto points = loadFile(filename);
    int maxArea = calculateMaxArea(points);
    std::cout << "Maximum Area: " << maxArea << std::endl;

    // assert that no single x has more than 2 y values and vice versa
    std::unordered_map<unsigned long, std::vector<unsigned long>> x_to_ys;
    std::unordered_map<unsigned long, std::vector<unsigned long>> y_to_xs;
    for (const auto& [x, y] : points) {
        x_to_ys[x].push_back(y);
        y_to_xs[y].push_back(x);
    }
    if (hasMultipleYsOrXs(x_to_ys, y_to_xs)) {
        std::cout << "Error: A single x has more than 2 y values or a single y has more than 2 x values." << std::endl;
     }

    return 0;
}
