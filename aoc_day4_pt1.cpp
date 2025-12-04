#include <iostream>
#include <vector> 
using namespace std;

bool checkSurrounding(vector<string> grid, int pos_x, int pos_y, int maxRows){
  int maxColumns=grid[0].size();  // Fixed: should be grid[0].size() for column count
  // cout << "\nFinding. the surrounding @ at location" << pos_x << "," << pos_y; 
  int sum=0; 
  for (int i=pos_x-1; i<=pos_x+1; i++){
    for (int j=pos_y-1; j<=pos_y+1; j++)
    {
      if (i==pos_x && j==pos_y) continue; 
      if (i<0 || i>=maxRows || j<0 || j>=maxColumns) continue;
      if (grid[i][j]=='@') {
        sum++;
        // cout << "\nFound @ at "<< i << "," << j;  
      }
    }
  }
  // cout << "Sum for this position: " << sum;  . 
  if (grid[pos_x][pos_y] == '@' && sum<4) return true;
  return false;
}

int main() {
    std::vector<std::string> grid;
    int result = 0; 
    std::string line;
      
    while (std::getline(std::cin, line)) {
        if (!line.empty()) {
            grid.push_back(line);
        }
    }
    
    int rows = grid.size();  // Fixed: added 'int' and semicolon
    int columns = grid[0].size();  // Added for clarity
      
    for (int r=0; r<rows; r++) {  // Fixed: moved 'r' inside scope
      for (int c=0; c<grid[r].length(); c++) {  // Fixed: initialize c=0, added braces
        if (checkSurrounding(grid, r, c, rows)) result++;  // Fixed: added 'int'
      }
    }
    
    cout << "Result: " << result << endl;  // Fixed: changed to result instead of sum
    return 0;
}