/**
In a 2 dimensional array grid, each value grid[i][j] represents the height of a building located there. We are allowed to increase the height of any number of buildings, by any amount (the amounts can be different for different buildings). Height 0 is considered to be a building as well. 

At the end, the "skyline" when viewed from all four directions of the grid, i.e. top, bottom, left, and right, must be the same as the skyline of the original grid. A city's skyline is the outer contour of the rectangles formed by all the buildings when viewed from a distance. See the following example.

What is the maximum total sum that the height of the buildings can be increased?

Example:
Input: grid = [[3,0,8,4],[2,4,5,7],[9,2,6,3],[0,3,1,0]]
Output: 35
Explanation: 
The grid is:
[ [3, 0, 8, 4], 
  [2, 4, 5, 7],
  [9, 2, 6, 3],
  [0, 3, 1, 0] ]

The skyline viewed from top or bottom is: [9, 4, 8, 7]
The skyline viewed from left or right is: [8, 7, 9, 3]

The grid after increasing the height of buildings without affecting skylines is:

gridNew = [ [8, 4, 8, 7],
            [7, 4, 7, 7],
            [9, 4, 8, 7],
            [3, 3, 3, 3] ]

Notes:

1 < grid.length = grid[0].length <= 50.
All heights grid[i][j] are in the range [0, 100].
All buildings in grid[i][j] occupy the entire grid cell: that is, they are a 1 x 1 x grid[i][j] rectangular prism.
**/

/**
class Solution {
public:
    int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
        vector<int> tb = vector<int>((int)grid[0].size());
        vector<int> lr = vector<int>((int)grid.size());
        vector<vector<int> > increased_grid((int)grid.size(), vector<int>((int)grid[0].size()));
        int answer=0;
        
        //first find out the skyline 
        for(int j = 0; j < grid[0].size(); j++){
            int max = 0;
            for(int i = 0; i < grid.size(); i++){
                max = grid[i][j]>max?grid[i][j]:max;
            }
            tb[j] = max;
        }
        
        for(int i = 0; i < grid.size(); i++){
            int max = 0;
            for(int j = 0; j < grid[0].size(); j++){
                max = grid[i][j]>max?grid[i][j]:max;
            }
            lr[i] = max;
        }
        
        //build the increased skyline
        for(int i = 0; i < increased_grid.size(); i++){
            for(int j = 0; j < increased_grid[0].size(); j++){
                increased_grid[i][j] = tb[i]<lr[j]?tb[i]:lr[j];
                answer+=(increased_grid[i][j]-grid[i][j]);
            }
        }
        
        return answer;
    }
};
**/

//optimized
class Solution {
public:
    int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
        vector<int> tb = vector<int>((int)grid[0].size(), 0);
        vector<int> lr = vector<int>((int)grid.size(), 0);
        int answer=0;
        
        //first find out the skyline 
        for(int i = 0; i < grid.size(); i++){
            for(int j = 0; j < grid[0].size(); j++){
                lr[i] = max(grid[i][j], lr[i]); //compare through j, left-right
                tb[j] = max(grid[i][j], tb[j]); //compare through i, top-bottom
            }
        }
        
        //build the increased skyline
        for(int i = 0; i < grid.size(); i++){
            for(int j = 0; j < grid[0].size(); j++){
                answer+=(min(tb[i], lr[j])-grid[i][j]);
            }
        }
        
        return answer;
    }
};
