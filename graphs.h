//
// Created by Wei on 1/12/24.
//

#ifndef NEETCODE150_GRAPHS_H
#define NEETCODE150_GRAPHS_H

#include "common.h"
//953. Verifying an Alien Dictionary
class Solution953 {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        unordered_map<char, int> charToIndex;
        for (int i = 0; i < order.size(); ++i) {
            charToIndex[order[i]] = i;
        }

        for (int i = 1; i < words.size(); ++i) {
            if (!isSorted(words[i - 1], words[i], charToIndex)) {
                return false;
            }
        }

        return true;
    }

private:
    bool isSorted(const string& word1, const string& word2, const unordered_map<char, int>& charToIndex) {
        int n = min(word1.size(), word2.size());
        for (int j = 0; j < n; ++j) {
            char c1 = word1[j];
            char c2 = word2[j];
            if (c1 != c2) {
                return charToIndex.at(c1) < charToIndex.at(c2);
            }
        }
        return word1.size() <= word2.size();
    }
};

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
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution133 {
public:
    unordered_map<Node*, Node*> seen;
    Node* cloneGraph(Node* node) {
        if (node == nullptr)
            return nullptr;
        if (seen.count(node)!=0) {
            return seen[node];
        }

        Node* cloneNode = new Node(node->val);
        seen[node] = cloneNode;

        for (auto neighbor:node->neighbors) {
            //emplace_back() can be more efficient when constructing objects with complex constructors,
            //as it avoids the overhead of creating temporary objects.
            cloneNode->neighbors.emplace_back(cloneGraph(neighbor));
        }
        return cloneNode;
    }
};

//695. Max Area of Island
class Solution695 {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int maxArea = 0;
        int m = grid.size();
        int n = grid[0].size();
        for (int i=0; i<grid.size(); i++) {
            for (int j=0; j<grid[0].size(); j++) {
                if (grid[i][j] == 1) {
                    int count = 0;
                    dfs(grid, count, i, j, m, n);
                    maxArea = max(maxArea, count);
                }
            }
        }
        return maxArea;
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

//286. Walls and gates
/*You are given an m x n grid rooms initialized with these three possible values.
 -1 A wall or an obstacle.
 0 A gate.
 INF Infinity means an empty room.
 We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
 Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.
*/
class Solution286 {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        int rows = rooms.size();
        int cols = rooms[0].size();

        queue<pair<int, int>> q;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
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

                if (x < 0 || x >= rows || y < 0 || y >= cols || rooms[x][y] != INT_MAX) {
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

//994. Rotting Oranges
class Solution994 {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        queue<pair<int, int>> rotten;
        int fresh = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 2)
                    rotten.push({i, j});
                else if (grid[i][j] == 1)
                    ++fresh;
            }
        }

        int minutes = 0;
        vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        while (!rotten.empty() && fresh > 0) {
            int size = rotten.size();
            while (size--) {
                auto& [x, y] = rotten.front();
                rotten.pop();

                for (auto& dir : directions) {
                    int nx = x + dir[0];
                    int ny = y + dir[1];
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1) {
                        grid[nx][ny] = 2;
                        rotten.push({nx, ny});
                        --fresh;
                    }
                }
            }
            ++minutes;
        }

        return fresh == 0 ? minutes : -1;
    }
};

//1905. Count Sub Islands
class Solution1905 {
public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        const int ROWS = grid1.size(), COLS = grid1[0].size();
        unordered_set<int> visited;

        function<bool(int, int)> dfs = [&] (int r, int c) -> bool {
            if (    r < 0
                    || c < 0
                    || r == ROWS
                    || c == COLS
                    || grid2[r][c] == 0
                    || visited.count(r*COLS + c)
                    )
                return true;

            visited.insert(r*COLS + c);
            bool res = true;
            if(grid1[r][c] == 0)
                res = false;

            res = dfs(r - 1, c) && res;
            res = dfs(r + 1, c) && res;
            res = dfs(r, c - 1) && res;
            res = dfs(r, c + 1) && res;
            return res;
        };

        int count = 0;
        for(int r = 0; r < ROWS; r++)
            for(int c = 0; c < COLS; c++)
                if (grid2[r][c] && !visited.count(r*COLS + c) && dfs(r, c))
                    count += 1;
        return count;
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

private:
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

//1466. Reorder Routes to Make All Paths Lead to the City Zero
class Solution1466 {
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        unordered_map<int, vector<vector<int>> > map;
        unordered_set<int> visited;

        for (auto& road: connections) {
            map[road[0]].emplace_back(road);
            map[road[1]].emplace_back(road);
        }

        int result = 0;
        queue<int> cities;
        cities.emplace(0);
        while (!cities.empty()) {
            auto& city = cities.front();
            visited.emplace(city);

            auto& roads = map[city];
            for (auto& road: roads) {
                if (road[1] != city && visited.count(road[1]) == 0) {
                    result++;
                    swap(road[0], road[1]);
                }
                if (visited.count(road[0]) == 0)
                    cities.emplace(road[0]);
            }

            cities.pop();
        }
        return result;
    }
};

//909. Snakes and Ladders
class Solution909 {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size();
        int target = n * n;
        unordered_set<int> visited;

        auto getCoordinates = [&](int square) -> pair<int, int> {
            int row = (square - 1) / n;
            int col = (square - 1) % n;
            if (row % 2 != 0) {
                col = n - 1 - col;
            }
            return {n - 1 - row, col};
        };

        int start = 1;
        queue<pair<int, int>> q;
        q.push({start, 0});

        while (!q.empty()) {
            auto [square, moves] = q.front();
            q.pop();

            if (square == target) {
                return moves;
            }

            if (visited.count(square)) {
                continue;
            }
            visited.insert(square);

            for (int roll = 1; roll <= 6; ++roll) {
                int nextSquare = min(square + roll, target);
                auto [row, col] = getCoordinates(nextSquare);

                if (board[row][col] != -1) {
                    nextSquare = board[row][col];
                }

                if (!visited.count(nextSquare)) {
                    q.push({nextSquare, moves + 1});
                }
            }
        }

        return -1;
    }
};

//752. Open the Lock
class Solution752 {
public:
    int openLock(vector<string>& deadends, string target) {
        set<string> deads(deadends.begin(), deadends.end());

        queue<string> Queue;
        if (!deads.count("0000")) {
            deads.insert("0000");
            Queue.emplace("0000");
        }

        int turns = 0;
        while (!Queue.empty()) {
            int size = Queue.size();
            while (size-- > 0) {
                string& str = Queue.front();
                if (str == target)
                    return turns;

                for (int i = 0; i < 4; i++) {
                    string temp = str;
                    temp[i] = (str[i] - 1)=='/'? '9' : (str[i] - 1);
                    if (!deads.count(temp)) {
                        deads.insert(temp);
                        Queue.emplace(temp);
                    }

                    temp[i] = (str[i] + 1)==':'? '0': (str[i] + 1);
                    if (!deads.count(temp)) {
                        deads.insert(temp);
                        Queue.emplace(temp);
                    }
                }
                Queue.pop();
            }
            turns++;
        }
        return -1;
    }
};

//802. Find Eventual Safe States
class Solution802 {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> res;
        visited = vector<int>(n, -1);
        for (int i=0; i<n; i++) {
            if (dfs(i, graph)) {
                continue;
            }
            res.emplace_back(i);
        }
        return res;
    }

private:
    vector<int> visited;
    bool dfs(int i, vector<vector<int>>& graph) {
        if (visited[i]!=-1)
            return visited[i];

        visited[i] = 1;
        for (auto x:graph[i]) {
            if (dfs(x, graph)) {
                return true;
            }
        }

        visited[i] = 0;
        return false;
    }
};

//207. Course Schedule
class Solution207 {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        unordered_map<int, vector<int>> m;
        for (auto& pre: prerequisites) {
            m[pre[0]].push_back(pre[1]);
        }

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
        for (auto pre: prerequisites) {
            m[pre[0]].push_back(pre[1]);
        }
        unordered_set<int> visited;
        unordered_set<int> cycle;

        vector<int> result;
        for (int course = 0; course < numCourses; course++) {
            if (!dfs(course, m, visited, cycle, result)) {
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
    bool dfs(int course, unordered_map<int, vector<int>>& m, unordered_set<int>& visited,
             unordered_set<int>& cycle, vector<int>& result) {

        if (cycle.find(course) != cycle.end()) {
            return false;
        }
        if (visited.find(course) != visited.end()) {
            return true;
        }
        cycle.insert(course);
        for (int i = 0; i < m[course].size(); i++) {
            int nextCourse = m[course][i];
            if (!dfs(nextCourse, m, visited, cycle, result)) {
                return false;
            }
        }
        cycle.erase(course);
        visited.insert(course);
        result.push_back(course);
        return true;
    }
};

//261. Graph Valid Tree
/*
Given n nodes labeled from 0 to n-1 and a list of undirected edges (each edge is a pair of nodes),
write a function to check whether these edges make up a valid tree.
Example 1:
Input: n = 5, and edges = [[0,1], [0,2], [0,3], [1,4]]
Output: true
Example 2:
Input: n = 5, and edges = [[0,1], [1,2], [2,3], [1,3], [1,4]]
Output: false
 */
class Solution261 {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        visited.resize(n);
        fill (visited.begin(), visited.end(), -1);
        graph.resize(n);

        for (auto& edge : edges) {
            graph[edge[0]].emplace_back(edge[1]);
            graph[edge[1]].emplace_back(edge[0]);
        }

        for (int i=0; i<n; i++) {
            if (dfs(-1, i))
                return false;
        }

        for (auto v : visited) {
            if (v != -1)
                return false;
        }

        return true;
    }

private:
    vector<int> visited;
    vector<vector<int>> graph;

    bool dfs(int pre, int cur) {
        if (visited[cur] == 1)
            return true;
        if (visited[cur] == 0)
            return false;

        visited[cur] = 1;
        for (auto next: graph[cur]) {
            if (pre == next)
                continue;
            if (dfs(cur, next))
                return true;
        }
        visited[cur] = 0;
        return false;
    }
};

//1462. Course Schedule IV
class Solution1462 {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<vector<bool>> reachable(numCourses, vector<bool>(numCourses, false));

        for (const auto& pre : prerequisites) {
            reachable[pre[0]][pre[1]] = true;
        }

        // Apply Floyd-Warshall algorithm to compute the transitive closure
        for (int k = 0; k < numCourses; ++k) {
            for (int i = 0; i < numCourses; ++i) {
                for (int j = 0; j < numCourses; ++j) {
                    reachable[i][j] = reachable[i][j] || (reachable[i][k] && reachable[k][j]);
                }
            }
        }

        vector<bool> answer;
        for (const auto& query : queries) {
            answer.push_back(reachable[query[0]][query[1]]);
        }

        return answer;
    }
};

//1958. Check if Move is Legal
class Solution1958 {
public:
    bool checkMove(vector<vector<char>>& board, int rMove, int cMove, char color) {
        const int ROWS = board.size();
        const int COLS = board[0].size();
        vector<vector<int>> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0},
                                          {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

        board[rMove][cMove] = color;
        function<bool(int, int, char, vector<int>&)> legal =
                [&] (int row, int col, char color, vector<int>& direction) -> bool {
            row += direction[0];
            col += direction[1];
            int length = 1;

            while (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
                length += 1;
                if (board[row][col] == '.')
                    return false;
                if (board[row][col] == color)
                    return length >= 3;
                row += direction[0];
                col += direction[1];
            }
            return false;
        };

        for (auto& d: directions) {
            if ( legal(rMove, cMove, color, d) )
                return true;
        }
        return false;
    }
};

//934. Shortest Bridge
class Solution934 {
public:
    int shortestBridge(vector<vector<int>>& A) {
        const int n = A.size();
        vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        queue<pair<int, int>> q;

        function<void(int, int)> markIsland = [&] (int row, int col) -> void {
            A[row][col] = -1;
            q.emplace(row * n + col, 0);
            for (auto d: directions) {
                int next_row = row + d[0];
                int next_col = col + d[1];
                if (next_row >= 0 && next_row < n && next_col >= 0 && next_col < n &&
                    A[next_row][next_col] == 1) {
                    markIsland(next_row, next_col);
                }
            }
        };

        // mark island of one group as -1
        bool found = false;
        for (int i = 0; i < n && !found; ++i) {
            for (int j = 0; j < n && !found; ++j) {
                if (A[i][j] == 1) {
                    markIsland(i, j);
                    found = true;
                }
            }
        }

        while (!q.empty()) {
            auto& [index, flips] = q.front();
            int row = index / n;
            int col = index % n;

            for (auto& d: directions) {
                int next_row = row + d[0];
                int next_col = col + d[1];

                if (next_row >= 0 && next_row < n && next_col >= 0 && next_col < n) {
                    if (A[next_row][next_col] == 1)
                        return flips;
                    if (A[next_row][next_col] == -1)
                        continue;
                    q.emplace(next_row * n + next_col, flips + 1);
                    A[next_row][next_col] = -1;
                }
            }

            q.pop();
        }
        return -1;
    }
};

//1091. Shortest Path in Binary Matrix
class Solution1091 {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        const int n = grid.size();
        if (grid[0][0] != 0 || grid[n-1][n-1] != 0)
            return -1;

        vector<vector<int>> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0},
                                          {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
        queue<pair<int, int>> q;
        q.emplace(0, 1);

        while (!q.empty()) {
            auto& [index, flips] = q.front();
            int row = index / n;
            int col = index % n;
            if (row == n - 1 && col == n - 1)
                return flips;

            for (auto& d: directions) {
                int next_row = row + d[0];
                int next_col = col + d[1];
                if (next_row >= 0 && next_row < n && next_col >= 0 && next_col < n &&
                    grid[next_row][next_col] == 0) {
                    q.emplace(next_row * n + next_col, flips + 1);
                    grid[next_row][next_col] = 1;
                }
            }

            q.pop();
        }

        return -1;
    }
};

//323. Number of Connected Components in an Undirected Graph
/*
 Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes),
 write a function to find the number of connected components in an undirected graph.

 Example 1:
     0          3
     |          |
     1 --- 2    4
Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], return 2.
 Example 2:
     0           4
     |           |
     1 --- 2 --- 3
Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [3, 4]], return 1.

Note:
You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.
*/
class Solution323 {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<int> parents;
        vector<int> ranks(n, 1);
        iota(parents.begin(), parents.end(), 0);

        int result = n;
        for (int i = 0; i < edges.size(); i++) {
            int n1 = edges[i][0];
            int n2 = edges[i][1];
            result -= doUnion(parents, ranks, n1, n2);
        }
        return result;
    }

private:
    int doFind(vector<int>& parents, int n) {
        int p = parents[n];
        while (p != parents[p]) {
            parents[p] = parents[parents[p]];
            p = parents[p];
        }
        return p;
    }

    int doUnion(vector<int>& parents, vector<int>& ranks, int n1, int n2) {
        int p1 = doFind(parents, n1);
        int p2 = doFind(parents, n2);
        if (p1 == p2) {
            return 0;
        }

        if (ranks[p1] > ranks[p2]) {
            parents[p2] = p1;
            ranks[p1] += ranks[p2];
        } else {
            parents[p1] = p2;
            ranks[p2] += ranks[p1];
        }

        return 1;
    }
};

//684. Redundant Connection
class Solution684 {
    unordered_map<int, unordered_set<int>> graph;
    unordered_set<int> visited;
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        vector<int> res;
        for (auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];

            if (graph.count(u) && graph.count(v)) {
                visited.clear();
                if (dfs(u, v)) {
                    return edge;
                }
            }

            graph[u].emplace(v);
            graph[v].emplace(u);
        }
        return res;
    }

private:
    bool dfs(int s, int t) {
        if (s==t) {
            return true;
        }

        visited.emplace(s);
        for (auto& adj: graph[s]) {
            if (!visited.count(adj) && dfs(adj, t)) {
                return true;
            }
        }

        return false;
    }
};

//721. Accounts Merge
class Solution721 {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, string> email_to_name;
        unordered_map<string, string> parent;

        // Initialize union-find structure
        for (const auto& account : accounts) {
            string name = account[0];
            for (int i = 1; i < account.size(); ++i) {
                email_to_name[account[i]] = name;
                parent[account[i]] = account[i]; // each email points to itself
            }
        }

        // Find the root of an email
        function<string(string)> find = [&](string email) -> string {
            if (parent[email] != email) {
                parent[email] = find(parent[email]); // path compression
            }
            return parent[email];
        };

        // Union two emails
        auto unite = [&](string email1, string email2) {
            parent[find(email1)] = find(email2);
        };

        // Perform union operation for all emails in the same account
        for (const auto& account : accounts) {
            string first_email = account[1];
            for (int i = 2; i < account.size(); ++i) {
                unite(first_email, account[i]);
            }
        }

        // Collect emails belonging to the same root
        unordered_map<string, set<string>> unions;
        for (const auto& account : accounts) {
            for (int i = 1; i < account.size(); ++i) {
                string root_email = find(account[i]);
                unions[root_email].insert(account[i]);
            }
        }

        // Build the result
        vector<vector<string>> merged_accounts;
        for (const auto& pair : unions) {
            vector<string> emails(pair.second.begin(), pair.second.end());
            emails.insert(emails.begin(), email_to_name[pair.first]);
            merged_accounts.push_back(emails);
        }

        return merged_accounts;
    }
};

//1162. As Far from Land as Possible
class Solution1162 {
public:
    int maxDistance(vector<vector<int>>& grid) {
        queue<pair<int, int>> q;
        int n= grid.size();

        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (grid[i][j] == 1) {
                    q.emplace(i, j);
                }
            }
        }

        vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        int result = 0;
        while (!q.empty()) {
            auto& [row, col] = q.front();

            for (auto& d: directions) {
                int next_row = row + d[0];
                int next_col = col + d[1];
                if (next_row >= 0 && next_row < n && next_col >= 0 && next_col < n
                    && grid[next_row][next_col] == 0) {
                        grid[next_row][next_col] = grid[row][col] + 1;
                        result = max(result, grid[next_row][next_col]);
                        q.emplace(next_row, next_col);
                }
            }

            q.pop();
        }
        return result - 1;
    }
};

//1129. Shortest Path with Alternating Colors
class Solution1129 {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        vector<vector<pair<int, int>>> graph(n); // pair(node, color), color: 0 - red, 1 - blue
        for (const auto& edge : redEdges) {
            graph[edge[0]].emplace_back(edge[1], 0); // Red edge
        }
        for (const auto& edge : blueEdges) {
            graph[edge[0]].emplace_back(edge[1], 1); // Blue edge
        }

        vector<vector<int>> distances(n, vector<int>(2, -1)); // distances[node][color]
        distances[0][0] = distances[0][1] = 0; // Starting node

        queue<tuple<int, int, int>> q; // (node, distance, last color)
        q.emplace(0, 0, -1); // Starting with node 0 and no color (-1)

        while (!q.empty()) {
            auto [node, dist, lastColor] = q.front();
            q.pop();
            for (const auto& [nextNode, edgeColor] : graph[node]) {
                if (edgeColor != lastColor && distances[nextNode][edgeColor] == -1) {
                    distances[nextNode][edgeColor] = dist + 1;
                    q.emplace(nextNode, dist + 1, edgeColor);
                }
            }
        }

        vector<int> result(n, -1);
        for (int i = 0; i < n; ++i) {
            if (distances[i][0] != -1 && distances[i][1] != -1) {
                result[i] = min(distances[i][0], distances[i][1]);
            } else if (distances[i][0] != -1) {
                result[i] = distances[i][0];
            } else if (distances[i][1] != -1) {
                result[i] = distances[i][1];
            }
        }
        return result;
    }
};

//2477. Minimum Fuel Cost to Report to the Capital
class Solution2477 {
public:
    long long minimumFuelCost(vector<vector<int>>& roads, int seats) {
        int n = roads.size() + 1;
        vector<vector<int>> graph(n);

        // Build the adjacency list
        for (const auto& road : roads) {
            graph[road[0]].push_back(road[1]);
            graph[road[1]].push_back(road[0]);
        }

        long long fuelCost = 0;

        // DFS function to calculate fuel cost
        function<int(int, int)> dfs = [&](int node, int parent) {
            int representatives = 1;

            for (int neighbor : graph[node]) {
                if (neighbor == parent) continue;
                representatives += dfs(neighbor, node);
            }

            if (node != 0) { // If not the capital city, add fuel cost for this subtree
                fuelCost += (representatives + seats - 1) / seats;
            }

            return representatives;
        };

        // Start DFS from the capital city (node 0)
        dfs(0, -1);

        return fuelCost;
    }
};

//2492. Minimum Score of a Path Between Two Cities
class Solution2492 {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        // Adjacency list representation of the graph
        vector<vector<pair<int, int>>> graph(n + 1);
        for (const auto& road : roads) {
            int u = road[0], v = road[1], dist = road[2];
            graph[u].emplace_back(v, dist);
            graph[v].emplace_back(u, dist);
        }

        queue<int> q;
        vector<bool> visited(n + 1, false);
        q.push(1);
        visited[1] = true;

        int minScore = INT_MAX;

        while (!q.empty()) {
            int city = q.front();
            q.pop();

            for (const auto& neighbor : graph[city]) {
                int nextCity = neighbor.first;
                int distance = neighbor.second;

                minScore = min(minScore, distance);

                if (!visited[nextCity]) {
                    visited[nextCity] = true;
                    q.push(nextCity);
                }
            }
        }

        return minScore;
    }
};

//1020. Number of Enclaves
class Solution1020 {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int ROWS = grid.size();
        int COLS = grid[0].size();
        vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        function<void(int, int)> bfs = [&](int r, int c) {
            queue<pair<int, int>> q;
            q.emplace(r, c);
            grid[r][c] = 0; // Mark as visited
            while (!q.empty()) {
                auto [row, col] = q.front();
                q.pop();
                for (auto& dir : directions) {
                    int nextRow = row + dir[0];
                    int nextCol = col + dir[1];
                    if (nextRow >= 0 && nextRow < ROWS && nextCol >= 0 && nextCol < COLS &&
                        grid[nextRow][nextCol] == 1) {
                        grid[nextRow][nextCol] = 0; // Mark as visited
                        q.emplace(nextRow, nextCol);
                    }
                }
            }
        };
        for (int i=0; i<ROWS; i++) {
            if (grid[i][0] == 1)
                bfs(i, 0);
            if (grid[i][COLS-1] == 1)
                bfs(i, COLS-1);
        }
        for (int j=0; j<COLS; j++) {
            if (grid[0][j] == 1)
                bfs(0, j);

            if (grid[ROWS-1][j] == 1)
                bfs(ROWS-1, j);
        }

        int count = 0;
        for (int i=0; i<ROWS; i++) {
            for (int j=0; j<COLS; j++) {
                if (grid[i][j] == 1)
                    count++;
            }
        }
        return count;
    }
};

//1254. Number of Closed Islands
class Solution1254 {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int ROWS = grid.size();
        int COLS = grid[0].size();
        vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        function<void(int, int)> bfs = [&] (int r, int c) {
            queue<pair<int, int>> q;
            q.emplace(r, c);
            grid[r][c] = 1;
            while (!q.empty()) {
                auto [row, col] = q.front();
                q.pop();
                for (auto dir: directions) {
                    int nextRow = dir[0] + row;
                    int nextCol = dir[1] + col;
                    if (nextRow >= 0 && nextRow < ROWS && nextCol >= 0 && nextCol < COLS &&
                        grid[nextRow][nextCol] == 0) {
                        grid[nextRow][nextCol] = 1;
                        q.emplace(nextRow, nextCol);
                    }
                }
            }
        };

        for (int i=0; i<ROWS; i++) {
            if (grid[i][0] == 0)
                bfs(i, 0);
            if (grid[i][COLS-1] == 0)
                bfs(i, COLS-1);
        }
        for (int j=0; j<COLS; j++) {
            if (grid[0][j] == 0)
                bfs(0, j);
            if (grid[ROWS-1][j] == 0)
                bfs(ROWS-1, j);
        }

        int count = 0;
        for (int i=0; i<ROWS; i++) {
            for (int j=0; j<COLS; j++) {
                if (grid[i][j]==0) {
                    count++;
                    bfs(i, j);
                }
            }
        }
        return count;
    }
};

//1557. Minimum Number of Vertices to Reach All Nodes
class Solution1557 {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        vector<int> inDegree(n, 0);
        for (const auto& edge : edges) {
            inDegree[edge[1]]++;
        }

        vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (inDegree[i] == 0) {
                result.push_back(i);
            }
        }

        return result;
    }
};

//785. Is Graph Bipartite?
/*graph coloring approach*/
class Solution785 {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> colors(n, -1);

        for (int i = 0; i < n; ++i) {
            if (colors[i] == -1) {
                if (!bfsCheck(graph, colors, i)) {
                    return false;
                }
            }
        }
        return true;
    }

private:
    bool bfsCheck(const vector<vector<int>>& graph, vector<int>& colors, int start) {
        queue<int> q;
        q.push(start);
        colors[start] = 0;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            int currentColor = colors[node];

            for (int neighbor : graph[node]) {
                if (colors[neighbor] == -1) {
                    colors[neighbor] = 1 - currentColor;
                    q.push(neighbor);
                } else if (colors[neighbor] == currentColor) {
                    // If the neighbor has the same color, the graph is not bipartite
                    return false;
                }
            }
        }
        return true;
    }
};

//399. Evaluate Division
class Solution399 {
    unordered_map<string, vector<pair<string, double>>> graph;
    unordered_map<string, bool> visited;
    double queryAns;

public:
    bool dfs(string startNode, string endNode, double runningProduct){
        if(graph.find(startNode) == graph.end() || graph.find(endNode) == graph.end()) {
            return false;
        }

        if(startNode == endNode && graph.find(startNode)!=graph.end()) {
            queryAns = runningProduct;
            return true;
        }

        bool tempAns = false;
        visited[startNode] = true;

        for(int i = 0; i < graph[startNode].size(); i++){
            if(!visited[graph[startNode][i].first]){
                tempAns = dfs(graph[startNode][i].first, endNode, runningProduct*graph[startNode][i].second);
                if(tempAns){
                    break;
                }
            }
        }
        visited[startNode] = false;

        return tempAns;
    }

    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int n = equations.size(), m = queries.size();
        vector<double> ans(m);

        for(int i = 0; i < n ; i++){

            graph[equations[i][0]].push_back({equations[i][1], values[i]});
            graph[equations[i][1]].push_back({equations[i][0], 1/values[i]});
            visited[equations[i][0]] = false;
            visited[equations[i][1]] = false;

        }

        for(int i = 0; i < m ; i++){
            queryAns = 1;
            bool pathFound = dfs(queries[i][0], queries[i][1], 1);
            if(pathFound) ans[i] = queryAns;
            else ans[i] = -1;

        }
        return ans;
    }
};

//2101. Detonate the Maximum Bombs
class Solution2101 {
public:
    int maximumDetonation(vector<vector<int>>& bombs) {
        int n = bombs.size();
        vector<vector<int>> graph(n);

        // Build the graph
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && inRange(bombs[i], bombs[j])) {
                    graph[i].push_back(j);
                }
            }
        }

        int maxDetonated = 0;
        // Perform BFS or DFS from each bomb
        for (int i = 0; i < n; ++i) {
            vector<bool> visited(n, false);
            int count = bfs(graph, i, visited);
            maxDetonated = max(maxDetonated, count);
        }

        return maxDetonated;
    }

private:
    bool inRange(const vector<int>& bomb1, const vector<int>& bomb2) {
        long long x1 = bomb1[0], y1 = bomb1[1], r1 = bomb1[2];
        long long x2 = bomb2[0], y2 = bomb2[1];
        long long dx = x1 - x2, dy = y1 - y2;
        return dx * dx + dy * dy <= r1 * r1;
    }

    int bfs(const vector<vector<int>>& graph, int start, vector<bool>& visited) {
        queue<int> q;
        q.push(start);
        visited[start] = true;
        int count = 0;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            count++;

            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        return count;
    }
};

//1857. Largest Color Value in a Directed Graph
class Solution1857 {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.size();
        vector<int> indegrees(n, 0);
        vector<vector<int>> graph(n, vector<int>());
        for (vector<int>& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            indegrees[edge[1]]++;
        }

        queue<int> zero_indegree;
        for (int i = 0; i < n; i++) {
            if (indegrees[i] == 0) {
                zero_indegree.push(i);
            }
        }

        vector<vector<int>> counts(n, vector<int>(26, 0));
        for (int i = 0; i < n; i++) {
            counts[i][colors[i] - 'a']++;
        }

        int max_count = 0;
        int visited = 0;
        while (!zero_indegree.empty()) {
            int u = zero_indegree.front();
            zero_indegree.pop();
            visited++;
            for (int v : graph[u]) {
                for (int i = 0; i < 26; i++) {
                    counts[v][i] = max(counts[v][i], counts[u][i] + (colors[v] - 'a' == i ? 1 : 0));
                }
                indegrees[v]--;
                if (indegrees[v] == 0) {
                    zero_indegree.push(v);
                }
            }
            max_count = max(max_count, *max_element(counts[u].begin(), counts[u].end()));
        }
        return visited == n ? max_count : -1;
    }
};

//1553. Minimum Number of Days to Eat N Oranges
class Solution1153_bfs {
public:
    int minDays(int n) {
        queue<int> q;
        unordered_set<int> visited;

        q.emplace(n);
        visited.emplace(n);
        int count = 0;

        while (!q.empty()) {
            count++;
            int size = q.size();
            while (size--) {

                int num = q.front();
                if (num == 0)
                    return count - 1;
                q.pop();

                if ((num & 1) == 0 && visited.find(num / 2) == visited.end()) {
                    q.emplace(num / 2);
                    visited.emplace(num / 2);
                }
                if (num % 3 == 0 && visited.find(num / 3) == visited.end()) {
                    q.emplace(num / 3);
                    visited.emplace(num / 3);
                }
                if (visited.find(num - 1) == visited.end()) {
                    q.emplace(num - 1);
                    visited.emplace(num - 1);
                }
            }
        }

        return n;
    }
};

class Solution1553_dfs_greedy_memo {
public:
    int minDays(int n) {
        memo[0] = 0;
        //this is also base case, o.w. memo[1] will be calculated as 2!
        memo[1] = 1;
        return dfs(n);
    }

private:
    unordered_map<int, int> memo;
    int dfs(int n){
        if(memo.find(n) != memo.end()){
            return memo[n];
        }

        int days = min(n%2+dfs(n/2), n%3+dfs(n/3));

        return memo[n] = days+1;
    };
};

//127. Word Ladder
class Solution127 {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        queue<string> q;
        q.emplace(beginWord);
        dict.erase(beginWord);
        int result = 1;

        while (!q.empty()) {
            result++;

            int size = q.size();
            while (size--) {
                string word(q.front());
                q.pop();

                if (word == endWord) {
                    return result;
                }

                for (int j = 0; j < word.size(); j++) {
                    char c = word[j];
                    for (int k = 0; k < 26; k++) {
                        word[j] = k + 'a';
                        if (dict.find(word) != dict.end()) {
                            q.emplace(word);
                            dict.erase(word);
                        }
                        word[j] = c; //backtracking
                    }
                }
            }
        }

        return 0;
    }
};

class Solution127_optimal {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (dict.size()==0 || dict.count(endWord)==0)
            return 0;
        unordered_set<string> leftSet;
        unordered_set<string> rightSet;
        leftSet.emplace(beginWord);
        rightSet.emplace(endWord);

        int count = 1;
        while (!leftSet.empty() && !rightSet.empty()) {
            count++;

            unordered_set<string> tempSet;
            for (auto& word:leftSet) {
                for (int i=0; i<word.length(); i++) {
                    string tempWord(word);
                    for (int j=0; j<26; j++) {
                        tempWord[i] = 'a'+j;
                        if (rightSet.count(tempWord))
                            return count;
                        if (dict.count(tempWord)) {
                            tempSet.emplace(tempWord);
                            dict.erase(tempWord);
                        }
                    }
                }
            }
            leftSet = tempSet;
            if (leftSet.size() > rightSet.size()) {
                swap(leftSet, rightSet);
            }
        }
        return 0;
    }
};


//****************************************** advanced graph ****************************************//
//1631. Path With Minimum Effort
/*
 Dijkstra's algorithm relies on always selecting the shortest path from the set of currently
 available paths. A priority queue ensures that the paths with the minimum distance are always
 explored first, which is crucial for Dijkstra's correctness.
*/
class Solution1631 {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int ROWS = heights.size();
        int COLS = heights[0].size();
        vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        vector<vector<int>> memo(ROWS, vector<int>(COLS, INT_MAX));
        memo[0][0] = 0;

        /*as declare pq like this, the lower effort will have the higher priority.
         if the effort are equal, then the row will be compared, and then the col*/
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<> > pq;
        pq.emplace(0, 0, 0);
        while (!pq.empty()) {
            auto [effort, row, col] = pq.top();
            if (row == ROWS - 1 && col == COLS - 1)
                return effort;
            pq.pop();

            for (auto dir: directions) {
                int nextRow = row + dir[0];
                int nextCol = col + dir[1];
                if (nextRow >= 0 && nextRow < ROWS && nextCol >= 0 && nextCol < COLS) {
                    int newEffort = max(effort, abs(heights[nextRow][nextCol] - heights[row][col]));
                    if (newEffort < memo[nextRow][nextCol]) {
                        memo[nextRow][nextCol] = newEffort;
                        pq.emplace(newEffort, nextRow, nextCol);
                    }
                }
            }
        }

        return -1;
    }
};

//332. Reconstruct Itinerary
//Keep going forward until you get stuck
class Solution332 {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string, deque<string>> graph;
        for (const auto& ticket : tickets) {
            graph[ticket[0]].push_back(ticket[1]);
        }

        for (auto& pair : graph) {
            sort(pair.second.begin(), pair.second.end());
        }

        vector<string> itinerary;
        function<void(const string&)> dfs = [&](const string& departure){
            while (!graph[departure].empty()) {
                string next_destination = graph[departure].front(); // Take the smallest lexical order destination
                graph[departure].pop_front();
                dfs(next_destination);
            }
            itinerary.push_back(departure);
        };

        dfs("JFK");
        return vector<string>(itinerary.rbegin(), itinerary.rend());
    }
};

//1584. Min Cost to Connect All Points
/*
 MST problem, Prim's, greedily pick node not in MST & has smallest edge cost
 Add to MST, & for all its neighbors, try to update min dist values, repeat
 */
class Solution1584 {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        int edgesUsed = 0;
        // track visited nodes
        vector<bool> inMST(n);
        vector<int> minDist(n, INT_MAX);
        minDist[0] = 0;
        int result = 0;

        while (edgesUsed < n) {
            int currMinEdge = INT_MAX;
            int currNode = -1;

            // greedily pick lowest cost node not in MST
            for (int i = 0; i < n; i++) {
                if (!inMST[i] && currMinEdge > minDist[i]) {
                    currMinEdge = minDist[i];
                    currNode = i;
                }
            }

            result += currMinEdge;
            edgesUsed++;
            inMST[currNode] = true;

            // update adj nodes of curr node
            for (int i = 0; i < n; i++) {
                int cost = abs(points[currNode][0] - points[i][0])
                           + abs(points[currNode][1] - points[i][1]);

                if (!inMST[i] && minDist[i] > cost) {
                    minDist[i] = cost;
                }
            }
        }

        return result;
    }
};

//743. Network Delay Time
class Solution743 {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> graph(n + 1); // 1-indexed graph
        vector<int> signalReceiveTime(n + 1, INT_MAX); // Initialize times to infinity
        vector<bool> visited(n + 1, false); // Mark nodes as visited

        // Build the graph
        for (const auto& time : times) {
            int u = time[0];
            int v = time[1];
            int w = time[2];
            graph[u].push_back({v, w});
        }

        // Priority queue for Dijkstra's algorithm: {node, time}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Start with the source node k
        pq.push({0, k});
        signalReceiveTime[k] = 0; // time from source to itself is 0

        // Dijkstra's algorithm
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            // If node u has been visited before, skip it
            if (visited[u])
                continue;

            visited[u] = true;

            // Relax all outgoing edges from node u
            for (const auto& edge : graph[u]) {
                int v = edge.first;
                int w = edge.second;
                if (!visited[v] && signalReceiveTime[u] + w < signalReceiveTime[v]) {
                    signalReceiveTime[v] = signalReceiveTime[u] + w;
                    pq.push({signalReceiveTime[v], v});
                }
            }
        }

        // Find the maximum time from the source node
        int maxTime = *max_element(signalReceiveTime.begin() + 1, signalReceiveTime.end());
        return (maxTime == INT_MAX) ? -1 : maxTime;
    }
};

//1514. Path with Maximum Probability
class Solution1514 {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        // Build the adjacency list representation of the graph
        unordered_map<int, vector<pair<int, double>>> graph;
        for (int i = 0; i < edges.size(); ++i) {
            int u = edges[i][0], v = edges[i][1];
            double p = succProb[i];
            graph[u].push_back({v, p});
            graph[v].push_back({u, p});
        }

        // Priority queue for Dijkstra's algorithm: {-probability, node}
        priority_queue<pair<double, int>> pq;
        vector<double> prob(n, 0.0); // Store the maximum probability to reach each node
        prob[start] = 1.0; // Probability to reach start node is 1

        // Start with the start node
        pq.push({1.0, start});

        // Dijkstra's algorithm
        while (!pq.empty()) {
            auto [curProb, u] = pq.top();
            pq.pop();

            // If the current probability is smaller than the current node's probability, skip it
            if (curProb < prob[u])
                continue;

            // Check if we reached the end node
            if (u == end)
                return curProb;

            // Relax all outgoing edges from the current node
            for (const auto& [v, p] : graph[u]) {
                if (curProb * p > prob[v]) {
                    prob[v] = curProb * p;
                    pq.push({prob[v], v});
                }
            }
        }

        // If no path is found from start to end
        return 0.0;
    }
};

//778. Swim in Rising Water
class Solution778 {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> distance(n, vector<int>(n, INT_MAX)); // distance matrix
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq; // min-heap

        // Directions for exploring adjacent cells
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        // Initialize start cell
        distance[0][0] = grid[0][0];
        pq.emplace(distance[0][0], 0, 0);

        // Dijkstra's algorithm
        while (!pq.empty()) {
            auto [elevation, i, j] = pq.top();
            pq.pop();

            // Check if reached bottom right cell
            if (i == n - 1 && j == n - 1)
                return elevation;

            // Explore adjacent cells
            for (const auto& dir : directions) {
                int ni = i + dir.first;
                int nj = j + dir.second;
                if (ni >= 0 && ni < n && nj >= 0 && nj < n) {
                    int newElevation = max(elevation, grid[ni][nj]);
                    if (newElevation < distance[ni][nj]) {
                        distance[ni][nj] = newElevation;
                        pq.emplace(newElevation, ni, nj);
                    }
                }
            }
        }

        // If no path found to bottom right cell
        return -1;
    }
};

//269. Alien Dictionary
/*
There is a new alien language which uses the latin alphabet. However, the order among letters
 are unknown to you. You receive a list of non-empty words from the dictionary, where words
 are sorted lexicographically by the rules of this new language. Derive the order of letters
 in this language.

Example 1:
Input:
[
  "wrt",
  "wrf",
  "er",
  "ett",
  "rftt"
]
Output: "wertf"

Example 2:
Input:
[
  "z",
  "x"
]
Output: "zx"

Example 3:
Input:
[
  "z",
  "x",
  "z"
]
Output: ""
Explanation: The order is invalid, so return "".

Note:
You may assume all letters are in lowercase.
You may assume that if a is a prefix of b, then a must appear before b in the given dictionary.
If the order is invalid, return an empty string.
There may be multiple valid order of letters, return any one of them is fine.
 */
class Solution269 {
public:
    string alienOrder(vector<string>& words) {
        unordered_map<char, vector<char>> graph;
        unordered_map<char, int> indegree;

        // Initialize indegrees to 0
        for (const string& word : words) {
            for (char ch : word) {
                indegree[ch] = 0;
            }
        }

        // Construct the graph and calculate indegrees
        for (int i = 0; i < words.size() - 1; ++i) {
            const string& word1 = words[i];
            const string& word2 = words[i + 1];
            int len = min(word1.size(), word2.size());

            // Compare characters in adjacent words
            for (int j = 0; j < len; ++j) {
                char from = word1[j];
                char to = word2[j];
                if (from != to) {
                    graph[from].push_back(to);
                    indegree[to]++;
                    break; // Stop comparing once the first differing character is found
                }
            }
        }

        // Perform topological sort
        queue<char> q;
        for (const auto& entry : indegree) {
            if (entry.second == 0) {
                q.push(entry.first);
            }
        }

        string order;
        while (!q.empty()) {
            char curr = q.front();
            q.pop();
            order += curr;

            for (char neighbor : graph[curr]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        // Check for cycle
        if (order.size() != indegree.size()) {
            return "";
        }

        return order;
    }
};

//787. Cheapest Flights Within K Stops
//Single-Source Shortest Path：Bellman-Ford Algorithm
class Solution787 {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        int MAX = 1e6+1;
        vector<int> dist(n, MAX);

        dist[src] = 0;
        for(vector<int>& flight : flights){
            //whether use flight[0] as middle point
            if(flight[0] == src)
                dist[flight[1]] = flight[2];
        }

        while(K-- > 0){
            vector<int> tmp(dist);
            for(vector<int>& flight : flights){
                //whether use flight[0] as middle point
                /*
                tmp cannot depend on itself!
                it must be calculated from "dist"(from previous iteration!)
                */
                tmp[flight[1]] = min(tmp[flight[1]], dist[flight[0]] + flight[2]);
            }
            swap(tmp, dist);
        }

        return dist[dst] == MAX ? -1 : dist[dst];
    }
};

//2421. Number of Good Paths
class Solution2421 {
    int findParent(vector<int>& parent, int a) {
        if (a == parent[a]) {
            return a;
        }
        parent[a] = findParent(parent, parent[a]);
        return parent[a];
    }

public:
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size();
        vector<int> parent(n);
        vector<int> maxElement(vals);
        vector<int> count(n, 1);

        iota(parent.begin(), parent.end(), 0);

        //ensures that we process edges in the order of increasing maximum node values.
        sort(edges.begin(), edges.end(), [&vals](const vector<int>& a, const vector<int>& b) {
            return max(vals[a[0]], vals[a[1]]) < max(vals[b[0]], vals[b[1]]);
        });

        //each node is a trivial good path
        int ans = n;
        for (const auto& it : edges) {
            int a = findParent(parent, it[0]);
            int b = findParent(parent, it[1]);
            if (maxElement[a] > maxElement[b]) {
                parent[b] = a;
            } else if (maxElement[a] < maxElement[b]){
                parent[a] = b;
            }
            else {
                parent[b] = a;
                ans += count[a] * count[b];
                count[a] += count[b];
            }
        }

        return ans;
    }
};

//1579. Remove Max Number of Edges to Keep Graph Fully Traversable
class Solution1579 {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        DSU dsu_alice(n + 1), dsu_bob(n + 1);
        int required_edges = 0;

        // First, add all type 3 edges
        for (const auto& edge : edges) {
            if (edge[0] == 3) {
                if (dsu_alice.unite(edge[1], edge[2])) {
                    dsu_bob.unite(edge[1], edge[2]);
                    ++required_edges;
                }
            }
        }

        for (const auto& edge : edges) {
            if (edge[0] == 1) {
                if (dsu_alice.unite(edge[1], edge[2])) {
                    ++required_edges;
                }
            } else if (edge[0] == 2) {
                if (dsu_bob.unite(edge[1], edge[2])) {
                    ++required_edges;
                }
            }
        }

        // Check if both Alice and Bob can traverse the entire graph
        if (isFullyTraversable(dsu_alice, n) && isFullyTraversable(dsu_bob, n)) {
            return edges.size() - required_edges;
        } else {
            return -1;
        }
    }

private:
    bool isFullyTraversable(DSU& dsu, int n) {
        int root = dsu.find(1);
        for (int i = 2; i <= n; ++i) {
            if (dsu.find(i) != root) {
                return false;
            }
        }
        return true;
    }
};

//1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree
class Solution1489 {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        for (int i = 0; i < m; ++i) {
            edges[i].push_back(i);  // Add index to edge
        }
        sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
            return a[2] < b[2];  // Sort edges by weight
        });

        // Find MST weight
        int mstWeight = 0;
        DSU dsu(n);
        for (auto& edge : edges) {
            if (dsu.unite(edge[0], edge[1])) {
                mstWeight += edge[2];
            }
        }

        vector<int> criticalEdges, pseudoCriticalEdges;
        for (int i = 0; i < m; ++i) {
            // Check if edge is critical
            int weightWithoutEdge = 0;
            DSU dsuWithoutEdge(n);
            for (int j = 0; j < m; ++j) {
                if (i != j && dsuWithoutEdge.unite(edges[j][0], edges[j][1])) {
                    weightWithoutEdge += edges[j][2];
                }
            }
            if (dsuWithoutEdge.find(edges[i][0]) != dsuWithoutEdge.find(edges[i][1]) || weightWithoutEdge > mstWeight) {
                criticalEdges.push_back(edges[i][3]);
                continue;
            }

            // Check if edge is pseudo-critical
            DSU dsuWithEdge(n);
            dsuWithEdge.unite(edges[i][0], edges[i][1]);
            int mstWeightWithEdge = edges[i][2];
            for (int j = 0; j < m; ++j) {
                if (i != j && dsuWithEdge.unite(edges[j][0], edges[j][1])) {
                    mstWeightWithEdge += edges[j][2];
                }
            }
            if (mstWeightWithEdge == mstWeight) {
                pseudoCriticalEdges.push_back(edges[i][3]);
            }
        }

        return {criticalEdges, pseudoCriticalEdges};
    }
};

#endif //NEETCODE150_GRAPHS_H
