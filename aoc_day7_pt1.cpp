#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
    // Read input from file
    std::ifstream file("aoc_day7.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file aoc_day7_test.txt" << std::endl;
        return 1;
    }

    // Read the grid into a 2D vector
    std::vector<std::vector<char>> grid;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<char> row(line.begin(), line.end());
        grid.push_back(row);
    }
    file.close();

    if (grid.empty()) {
        std::cerr << "Error: Empty grid" << std::endl;
        return 1;
    }

    int num_rows = grid.size();
    int num_cols = grid[0].size();

    // Initialize boolean vector - all false except column with 'S'
    std::vector<bool> active(num_cols, false);

    // Find 'S' in the first row and mark it as true
    for (int col = 0; col < num_cols; col++) {
        if (grid[0][col] == 'S') {
            active[col] = true;
            break;
        }
    }
    int split_count = 0;
    // Process each subsequent row
    for (int row = 1; row < num_rows; row++) {
        std::vector<bool> new_active(num_cols, false);

        for (int col = 0; col < num_cols; col++) {
            // If we encounter '^' and that column is active
            if (grid[row][col] == '^' && active[col]) {
                split_count++;
                // Mark adjacent columns as true
                if (col - 1 >= 0) {
                    new_active[col - 1] = true;
                }
                if (col + 1 < num_cols) {
                    new_active[col + 1] = true;
                }
                // Current column becomes false (don't set new_active[col])
            } else if (active[col] && grid[row][col] != '^') {
                // If column was active but no '^', keep it active
                new_active[col] = true;
            }
        }

        active = new_active;
    }

    // Count the number of true values
    int count = 0;
    for (bool val : active) {
        if (val) count++;
    }

    std::cout << split_count << std::endl;

    return 0;
}
