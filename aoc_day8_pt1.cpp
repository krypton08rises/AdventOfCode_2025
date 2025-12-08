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


//Estimate distance between two 3D points
double estimateDistance(int x1, int y1, int z1, int x2,
                        int y2, int z2) {
    return std::sqrt(std::pow(x2 - x1, 2) +
                     std::pow(y2 - y1, 2) +
                     std::pow(z2 - z1, 2));
}

// Refactor script to be more modular

std::vector<std::vector<int>> findClusters(
    const std::vector<std::tuple<int, int, double>>& distances,
    int numPoints, int maxConnections) {

    std::vector<std::vector<int>> clusters;
    int connections_made = 0;
    for (const auto& [i, j, dist] : distances) {
        if (connections_made >= maxConnections) {
            break;
        }
        connections_made++;
        int cluster_i = -1;
        int cluster_j = -1;
        for (int k = 0; k < clusters.size(); k++) {
            if (std::find(clusters[k].begin(), clusters[k].end(), i)!= clusters[k].end()) {
                cluster_i = k;
            }
            if (std::find(clusters[k].begin(), clusters[k].end(), j)!= clusters[k].end()) {
                cluster_j = k;
            }
        }
        if (cluster_i == -1 && cluster_j == -1) {
            clusters.push_back({i, j});
        } else if (cluster_i != -1 && cluster_j == -1) {
            clusters[cluster_i].push_back(j);
        } else if (cluster_i == -1 && cluster_j != -1) {
            clusters[cluster_j].push_back(i);
        } else if (cluster_i != cluster_j) {
            clusters[cluster_i].insert(clusters[cluster_i].end(),
                clusters[cluster_j].begin(), clusters[cluster_j].end());
            clusters.erase(clusters.begin() + cluster_j);
        }
    }
    return clusters;
}


int main() {
    const std::string filename = "aoc_day8.txt";
    auto [x, y, z] = loadFile(filename);
    // time each module
    std::vector<std::tuple<int, int, double>> distances;
    auto start = std::chrono::high_resolution_clock::now();
    // map index to distance between two indexes
    // estimate distance between all points...
    for (int i=0; i<x.size(); i++) {
        for (int j=i+1; j<x.size(); j++) {
            double dist = estimateDistance(x[i], y[i], z[i],
                                           x[j], y[j], z[j]);
            distances.push_back(std::make_tuple(i, j, dist));
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Distance estimation took " << elapsed.count() * 1e3 << " milliseconds." << std::endl;

    // sort distances vector by distance value
    std::sort(distances.begin(), distances.end(), [](const auto& a, const auto& b) {
        return std::get<2>(a) < std::get<2>(b);
    });

    // Connect closest points and form clusters until 10 shortest connections are made
    // if two clusters are already connected, skip, if they're part of 2 different clusters, merge the clusters
    // sort the clusters by number of points in each cluster in descending order and take the product of the 3 largest clusters..

    std::vector<std::vector<int>> clusters;
    start = std::chrono::high_resolution_clock::now();
    clusters = findClusters(distances, x.size(), 10);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Clustering took " << elapsed.count() * 1e6 << " microseconds." << std::endl;
    // sort clusters by size
    std::sort(clusters.begin(), clusters.end(), [](const auto& a, const auto& b) {
        return a.size() > b.size();
    });
    // print size of 3 largest clusters
    for (int i = 0; i < std::min(3, (int)clusters.size()); i++) {
        std::cout << "Cluster " << i << " size: " << clusters[i].size() << std::endl;
    }
    // print product of sizes of 3 largest clusters
    long long product = 1;
    for (int i = 0; i < std::min(3, (int)clusters.size()); i++) {
        product *= clusters[i].size();
    }
    std::cout << "Product of sizes of 3 largest clusters: " << product << std::endl;

    return 0;
}
