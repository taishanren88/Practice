#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

int helper(const vector<vector<bool>>& maze, 
            vector<vector<int>>& dp,
            int currX, int currY)
{
    if (currY >= maze.size() || currY < 0 || currX >= maze[0].size() || currX < 0)
        return  maze.size() * maze[0].size();
    if (dp[currY][currX] != -1)
        return dp[currY][currX];

    if (maze[currY][currX])
        dp[currY][currX] = maze.size() * maze[0].size();
    else {
        dp[currY][currX] = -2;
        int right = currX + 1 < maze[0].size() && dp[currY][currX + 1] != -2 ?helper(maze, dp, currX + 1, currY) : 1000;
        int left = currX  -1 >= 0 && dp[currY][currX - 1 ] != -2 ?helper(maze, dp, currX - 1, currY) : 1000;
        int bottom = currY - 1 >= 0 && dp[currY -1][currX] != -2 ? helper(maze, dp, currX, currY - 1) : 1000;
        int top = currY + 1< maze.size() && dp[currY+1][currX] != -2 ? helper(maze, dp, currX, currY + 1) : 1000;
        dp[currY][currX] = 1 + min( min (right, left), min(top,bottom));
        
    }
    return dp[currY][currX];

}
int findLongest(const vector<vector<bool>>& maze, int startY, int startX, int endY,  int endX)
{
    vector<vector<int>> dp (maze.size(), vector<int>(maze[0].size(), -1));
    dp[startY][startX] = 0;
    return helper(maze, dp, endX, endY);
}
int main()
{
    vector<vector<bool>> vec = { 
                 {false, false, false, false}, 
                 {true, true, false, true},
                 {false, false, false, false},
                 {false, false, false, false}};
   assert(findLongest(vec, 3, 0, 0, 0) == 7);

  vector<vector<bool>> vec2 = { 
                   {false, false,  false,  false},
        {true,  true,   false,  true},
        {false, false,  false,  false},
        {false, false,  false,  false}};
    assert(findLongest(vec2, 0, 0, 3, 3) == 6); 

     vector<vector<bool>> vec3 =   {{false, false,  false,  false, false},
        {true,  true,   true,  false, false},
        {false, false,  false,  false, true},
        {false, true,  true,  true, false},
        {false, false,  false,  false, false}};
    assert(findLongest(vec3, 3, 4, 0, 0) == 15);

}