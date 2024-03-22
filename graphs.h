//
// Created by Wei on 1/12/24.
//

#ifndef NEETCODE150_GRAPHS_H
#define NEETCODE150_GRAPHS_H

#include "common.h"
//200. Number of Islands
class Solution200 {
public:
    int numIslands(vector<vector<char>>& grid) {
        int result = 0;
        int m = grid.size();
        int n = grid[0].size();
        for (int i=0; i<grid.size(); i++) {
            for (int j=0; j<grid[0].size(); j++) {
                if (grid[i][j] == '1') {
                    result++;
                    dfs(grid, i, j, m, n);
                }
            }
        }
        return result;
    }

private:
    void dfs(vector<vector<char>>& grid, int i, int j, const int& m, const int& n) {
        if (i>=m || i<0 || j>=n ||j<0 || grid[i][j] != '1') {
            return;
        }
        grid[i][j] = '0';
        dfs(grid, i+1, j, m, n);
        dfs(grid, i-1, j, m, n);
        dfs(grid, i, j-1, m, n);
        dfs(grid, i, j+1, m, n);
    }
};

//133. Clone Graph
//solved in dfs.h

//695. Max Area of Island
class Solution695 {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int result = 0;
        int m = grid.size();
        int n = grid[0].size();
        for (int i=0; i<grid.size(); i++) {
            for (int j=0; j<grid[0].size(); j++) {
                if (grid[i][j] == 1) {
                    int count = 0;
                    dfs(grid, count, i, j, m, n);
                    result = max(result, count);
                }
            }
        }
        return result;
    }

private:
    void dfs(vector<vector<int>>& grid, int& count, int i, int j, const int& m, const int& n) {
        if (i>=m || i<0 || j>=n ||j<0 || grid[i][j] != 1) {
            return;
        }
        count++;
        grid[i][j] = 0;
        dfs(grid, count, i+1, j, m, n);
        dfs(grid, count, i-1, j, m, n);
        dfs(grid, count, i, j-1, m, n);
        dfs(grid, count, i, j+1, m, n);
    }
};

//417. Pacific Atlantic Water Flow
class Solution417 {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int m = heights.size();
        int n = heights[0].size();
        vector<vector<bool>> pacific(m, vector<bool>(n, false));
        vector<vector<bool>> atlantic(m, vector<bool>(n, false));

        for (int i=0; i<m; i++) {
            dfs(heights, pacific, i, 0, m, n);
            dfs(heights, atlantic, i, n-1, m, n);
        }
        for (int j=0; j<n; j++) {
            dfs(heights, pacific, 0, j, m, n);
            dfs(heights, atlantic, m-1, j, m, n);
        }

        vector<vector<int>> result;
        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++) {
                if (pacific[i][j] && atlantic[i][j])
                    result.push_back({i,j});
            }
        }
        return result;
    }
    void dfs(vector<vector<int>>& heights, vector<vector<bool>>& visited,
             int i, int j, const int& m, const int& n) {
        visited[i][j] = true;
        int height = heights[i][j];
        if (i>0 && !visited[i-1][j] && heights[i-1][j] >= height)
            dfs(heights, visited, i-1, j, m, n);
        if (j>0 && !visited[i][j-1] && heights[i][j-1] >= height)
            dfs(heights, visited, i, j-1, m, n);
        if (i<m-1 && !visited[i+1][j] && heights[i+1][j] >= height)
            dfs(heights, visited, i+1, j, m, n);
        if (j<n-1 && !visited[i][j+1] && heights[i][j+1] >= height)
            dfs(heights, visited, i, j+1, m, n);
    }
};

//130. Surrounded Regions
class Solution130 {
public:
    void solve(vector<vector<char>>& board) {
        int m = board.size();
        int n = board[0].size();

        // marking escaped cells along the border
        for (int i = 0; i < m; i++) {
            dfs(board,i,0,m,n);
            dfs(board,i,n-1,m,n);
        }

        for (int j = 0; j < n; j++) {
            dfs(board,0,j,m,n);
            dfs(board,m-1,j,m,n);
        }

        // flip cells to correct final states
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
                if (board[i][j] == 'E') {
                    board[i][j] = 'O';
                }
            }
        }
    }
private:
    void dfs(vector<vector<char>>& board, int i, int j, int m, int n) {
        if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] != 'O') {
            return;
        }

        board[i][j] = 'E';

        dfs(board, i - 1, j, m, n);
        dfs(board, i + 1, j, m, n);
        dfs(board, i, j - 1, m, n);
        dfs(board, i, j + 1, m, n);
    }
};

//994. Rotting Oranges
class Solution994 {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int, int>> q;
        int fresh = 0;
        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++) {
                if (grid[i][j] == 2)
                    q.push({i,j});
                if (grid[i][j] == 1)
                    fresh++;
            }
        }

        int result = -1;
        while (!q.empty()) {
            result++;
            int size = q.size();
            for (int count=0; count<size; count++) {
                auto& [x, y] = q.front();
                q.pop();
                if (grid[x][y] == 1)
                    fresh--;
                grid[x][y] = 2;
                if (x>0 && grid[x-1][y] == 1)
                    q.push({x-1, y});
                if (x<m-1 && grid[x+1][y] == 1)
                    q.push({x+1, y});
                if (y>0 && grid[x][y-1] == 1)
                    q.push({x, y-1});
                if (y<n-1 && grid[x][y+1] == 1)
                    q.push({x, y+1});
            }
        }
        if (fresh != 0)
            return -1;
        return result;
    }
};

//286. Walls and gates
class Solution286 {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        int m = rooms.size();
        int n = rooms[0].size();

        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (rooms[i][j] == 0) {
                    q.push({i, j});
                }
            }
        }

        while (!q.empty()) {
            int row = q.front().first;
            int col = q.front().second;
            q.pop();

            for (int i = 0; i < 4; i++) {
                int x = row + dirs[i][0];
                int y = col + dirs[i][1];

                if (x < 0 || x >= m || y < 0 || y >= n || rooms[x][y] != INT_MAX) {
                    continue;
                }

                rooms[x][y] = rooms[row][col] + 1;
                q.push({x, y});
            }
        }
    }
private:
    vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
};

//207. Course Schedule
class Solution207 {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // map each course to prereq list
        unordered_map<int, vector<int>> m;
        for (int i = 0; i < prerequisites.size(); i++) {
            m[prerequisites[i][0]].push_back(prerequisites[i][1]);
        }
        // all courses along current DFS path
        unordered_set<int> visited;

        for (int course = 0; course < numCourses; course++) {
            if (!dfs(course, m, visited)) {
                return false;
            }
        }
        return true;
    }
private:
    bool dfs(int course, unordered_map<int, vector<int>>& m, unordered_set<int>& visited) {
        if (visited.find(course) != visited.end()) {
            return false;
        }
        if (m[course].empty()) {
            return true;
        }
        visited.insert(course);
        for (int i = 0; i < m[course].size(); i++) {
            int nextCourse = m[course][i];
            if (!dfs(nextCourse, m, visited)) {
                return false;
            }
        }
        m[course].clear();
        visited.erase(course);
        return true;
    }
};

//210. Course Schedule II
class Solution210 {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        unordered_map<int, vector<int>> m;
        // build adjacency list of prereqs
        for (int i = 0; i < prerequisites.size(); i++) {
            m[prerequisites[i][0]].push_back(prerequisites[i][1]);
        }
        unordered_set<int> visit;
        unordered_set<int> cycle;

        vector<int> result;
        for (int course = 0; course < numCourses; course++) {
            if (!dfs(course, m, visit, cycle, result)) {
                return {};
            }
        }
        return result;
    }
private:
    // a course has 3 possible states:
    // visited -> course added to result
    // visiting -> course not added to result, but added to cycle
    // unvisited -> course not added to result or cycle
    bool dfs(int course, unordered_map<int, vector<int>>& m, unordered_set<int>& visit,
             unordered_set<int>& cycle, vector<int>& result) {

        if (cycle.find(course) != cycle.end()) {
            return false;
        }
        if (visit.find(course) != visit.end()) {
            return true;
        }
        cycle.insert(course);
        for (int i = 0; i < m[course].size(); i++) {
            int nextCourse = m[course][i];
            if (!dfs(nextCourse, m, visit, cycle, result)) {
                return false;
            }
        }
        cycle.erase(course);
        visit.insert(course);
        result.push_back(course);
        return true;
    }
};

//684. Redundant Connection




#endif //NEETCODE150_GRAPHS_H
