//
// Created by Wei on 1/12/24.
//

#ifndef NEETCODE150_BACKTRACK_H
#define NEETCODE150_BACKTRACK_H
#include "common.h"

//78. Subsets
class Solution78 {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> currentSubset;
        backtrack(nums, 0, currentSubset, result);
        return result;
    }

private:
    void backtrack(const vector<int>& nums, int start, vector<int>& currentSubset,
                   vector<vector<int>>& result) {
        // Add the current subset to the result
        result.push_back(currentSubset);

        // Explore all possible choices for the next element in the subset
        for (int i = start; i < nums.size(); ++i) {
            // Choose the current element
            currentSubset.push_back(nums[i]);

            // Explore further with the chosen element
            backtrack(nums, i + 1, currentSubset, result);

            // Unchoose the current element (backtrack)
            currentSubset.pop_back();
        }
    }
};

//39. Combination Sum
class Solution39 {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        //sort the candidates array before backtrack can be more efficient.
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> result;
        vector<int> subSet;
        backtrack(candidates, target, 0, result, subSet);
        return result;
    }

private:
    void backtrack(const vector<int>& candidates, int target, int start,
                   vector<vector<int>>& result, vector<int>& subSet) {
        if (target == 0) {
            result.push_back(subSet);
            return;
        }

        for (int i = start; i < candidates.size() && candidates[i] <= target; ++i) {
            subSet.push_back(candidates[i]);
            backtrack(candidates, target - candidates[i], i, result, subSet);
            subSet.pop_back();
        }
    }
};

//77. Combinations
class Solution77 {
public:
    void dfs(int n, int k, vector<int>& path, vector<vector<int>>& res) {
        int i= path.empty() ? 1 :path.back() + 1;
        for (; i<=n; i++) {
            path.emplace_back(i);
            if (path.size() == k) {
                res.emplace_back(path);
            }
            else {
                dfs(n, k, path, res);
            }
            path.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> path;
        dfs(n, k, path, res);
        return res;
    }
};

//47. Permutations II
class Solution47 {
    vector<vector<int>> res;
    bitset<8> used;
public:
    void dfs(vector<int> path, vector<int>& nums) {
        if (path.size() == nums.size()) {
            res.emplace_back(path);
            return;
        }
        for (int i=0; i<nums.size(); i++) {
            if (used[i])
                continue;
            if (i>0 && nums[i]==nums[i-1] && !used[i-1])
                continue;
            used.set(i);
            path.emplace_back(nums[i]);
            dfs(path, nums);
            path.pop_back();
            used.reset(i);
        }

    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<int> path;
        sort(nums.begin(), nums.end());
        dfs(path, nums);
        return res;
    }
};

//473. Matchsticks to Square
class Solution473 {
    bitset<15> used;
public:
    bool dfs(vector<int>& matchsticks, int step, int edge, int begin, int tempsum) {
        if (step == 4)
            return true;
        if (tempsum == edge) {
            return dfs(matchsticks, step+1, edge, 0, 0);
        }
        for (int i=begin; i<matchsticks.size(); i++) {
            if (used[i])
                continue;
            if (tempsum+matchsticks[i]>edge)
                break;
            used.set(i);
            if (dfs(matchsticks, step, edge, begin+1, tempsum+matchsticks[i]))
                return true;
            used.reset(i);
            while(i+1<matchsticks.size() && matchsticks[i]== matchsticks[i+1])
                i++;
        }
        return false;
    }

    bool makesquare(vector<int>& matchsticks) {
        if (matchsticks.size()<4)
            return false;
        int sum = accumulate(matchsticks.begin(), matchsticks.end(), 0);
        if (sum % 4!=0)
            return false;
        int edge = sum / 4;
        sort(matchsticks.begin(), matchsticks.end());
        return dfs(matchsticks, 0, edge, 0, 0);
    }
};

//52. N-Queens II
class Solution52 {
public:

    int totalNQueens(int n) {
        vector<bool> mainline(2*n -1);
        vector<bool> subline(2*n -1);
        vector<bool> col(n);
        //vector<vector<int>> paths;
        int cnt = 0;
        vector<int> path;

        dfs_help(0, path, mainline, subline, col, n, cnt);

        return cnt;
    }

    void dfs_help(int row, vector<int>& path, vector<bool>& mainline, vector<bool>& subline, vector<bool>& col, int& n, int& cnt) {
        if (row == n) {
            //paths.push_back(path);
            cnt++;
            return;
        }

        for (int j=0; j<n; j++) {
            if (!mainline[row-j + n-1] && !subline[row+j] && !col[j]) {
                mainline[row-j + n-1] = true;
                subline[row+j] = true;
                col[j] = true;
                path.push_back(j);
                dfs_help(row+1, path, mainline, subline, col, n, cnt);
                mainline[row-j + n-1] = false;
                subline[row+j] = false;
                col[j] = false;
                path.pop_back();
            }
        }
    }
};

//46. Permutations
class Solution46 {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        dfs(nums, 0, result);
        return result;
    }
private:
    void dfs(vector<int>& nums, int start, vector<vector<int>>& result) {
        if (start == nums.size()) {
            result.push_back(nums);
            return;
        }
        for (int i = start; i < nums.size(); i++) {
            swap(nums[i], nums[start]);
            dfs(nums, start + 1, result);
            swap(nums[i], nums[start]);
        }
    }
};

//90. Subsets II
class Solution90 {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> curr;
        vector<vector<int>> result;
        dfs(nums, 0, curr, result);
        return result;
    }
private:
    void dfs(const vector<int>& nums, int start, vector<int>& curr, vector<vector<int>>& result) {
        result.push_back(curr);
        for (int i = start; i < nums.size(); i++) {
            if (i > start && nums[i] == nums[i - 1]) {
                continue;
            }
            curr.push_back(nums[i]);
            dfs(nums, i + 1, curr, result);
            curr.pop_back();
        }
    }
};

//40. Combination Sum II
class Solution40 {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> result;
        vector<int> subSet;
        backtrack(candidates, target, 0, result, subSet);
        return result;
    }

private:
    void backtrack(const vector<int>& candidates, int target, int start,
                   vector<vector<int>>& result, vector<int>& subSet) {
        if (target == 0) {
            result.push_back(subSet);
            return;
        }

        for (int i = start; i < candidates.size() && candidates[i] <= target; ++i) {
            if (i > start && candidates[i] == candidates[i - 1]) {
                continue;
            }
            subSet.push_back(candidates[i]);
            backtrack(candidates, target - candidates[i], i+1, result, subSet);
            subSet.pop_back();
        }
    }
};

//79. Word Search
class Solution79 {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == word[0]) {
                    if (dfs(board, word, 0, i, j, m, n)) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
private:
    bool dfs(vector<vector<char>>& board, string word,
             int index, int i, int j, int m, int n) {

        if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] != word[index]) {
            return false;
        }
        if (index == word.size() - 1) {
            return true;
        }

        board[i][j] = '#';

        if (dfs(board, word, index + 1, i - 1, j, m, n)
            || dfs(board, word, index + 1, i + 1, j, m, n)
            || dfs(board, word, index + 1, i, j - 1, m, n)
            || dfs(board, word, index + 1, i, j + 1, m, n)) {
            return true;
        }

        board[i][j] = word[index];
        return false;
    }
};

//131. Palindrome Partitioning
class Solution131 {
public:
    vector<vector<string>> partition(string s) {
        vector<string> curr;
        vector<vector<string>> result;
        dfs(s, 0, curr, result);
        return result;
    }
private:
    void dfs(string s, int start, vector<string>& curr, vector<vector<string>>& result) {
        if (start == s.size()) {
            result.push_back(curr);
            return;
        }
        for (int i = start; i < s.size(); i++) {
            if (isPalindrome(s, start, i)) {
                string str = s.substr(start, i - start + 1);
                curr.push_back(str);
                dfs(s, i + 1, curr, result);
                curr.pop_back();
            }
        }
    }
    bool isPalindrome(string s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
};

//17. Letter Combinations of a Phone Number
class Solution17 {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) {
            return {};
        }

        unordered_map<char, string> m = {
                {'2', "abc"},
                {'3', "def"},
                {'4', "ghi"},
                {'5', "jkl"},
                {'6', "mno"},
                {'7', "pqrs"},
                {'8', "tuv"},
                {'9', "wxyz"}
        };
        string curr = "";
        vector<string> result;

        dfs(digits, 0, m, curr, result);
        return result;
    }
private:
    void dfs(string digits, int index, unordered_map<char, string>& m, string& curr, vector<string>& result) {
        if (index == digits.size()) {
            result.push_back(curr);
            return;
        }
        string str = m[digits[index]];
        for (int i = 0; i < str.size(); i++) {
            curr.push_back(str[i]);
            dfs(digits, index + 1, m, curr, result);
            curr.pop_back();
        }
    }
};

//51. N-Queens
class Solution51 {
private:
    unordered_set<int> cols;     //for Columns
    unordered_set<int> negDiag;  //for negative diagnals R-C
    unordered_set<int> posDiag;  //for positive diagnals R+C

    void backtrack(int n, int row, vector<vector<string>>& res, vector<string>& board){
        if(row==n){
            res.push_back(board);
            return ;
        }

        for(int col = 0; col < n; col++){   //Shifting through each col
            if( cols.find(col) != cols.end() or //if queen alread placed in this col
                negDiag.find(row - col) != negDiag.end() or //if queen in negDiag
                posDiag.find(row + col) != posDiag.end()    //if queen in posDiag
                    )
                continue;

            cols.insert(col);
            negDiag.insert(row - col);
            posDiag.insert(row + col);
            board[row][col] = 'Q';

            backtrack(n, row +1, res, board);

            cols.erase(col);
            negDiag.erase(row - col);
            posDiag.erase(row + col);
            board[row][col] = '.';
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<string> board(n, string(n,'.'));
        backtrack(n, 0, res, board);
        return res;
    }
};

//37. Sudoku Solver
class Solution37 {
    vector<set<int>> row;
    vector<set<int>> col;
    vector<set<int>> box;
    vector<pair<int, int>> dots;
public:
    bool dfs(vector<pair<int, int>>::iterator itor, vector<pair<int, int>>::iterator end,
             vector<vector<char>>& board) {
        if (itor == end) {
            return true;
        }

        int i= (*itor).first;
        int j = (*itor).second;
        for (int num=1; num<=9; num++) {
            if (row[i].count(num) || col[j].count(num) || box[(i/3)*3 + j/3].count(num))
                continue;
            row[i].insert(num);
            col[j].insert(num);
            box[(i/3)*3 + j/3].insert(num);
            board[i][j] = '0' + num;
            if (dfs(itor+1,end, board))
                return true;
            row[i].erase(num);
            col[j].erase(num);
            box[(i/3)*3 + j/3].erase(num);
        }
        return false;
    }

    void solveSudoku(vector<vector<char>>& board) {
        row.resize(9);
        col.resize(9);
        box.resize(9);

        for (int i =0; i<9; i++) {
            for (int j =0; j<9; j++) {
                if (board[i][j] != '.') {
                    row[i].insert(board[i][j] - '0');
                    col[j].insert(board[i][j] - '0');
                    box[(i/3)*3 + j/3].insert(board[i][j] - '0');
                }
                else {
                    dots.emplace_back(i,j);
                }
            }
        }

        dfs(dots.begin(),dots.end(), board);
    }
};

//89. Gray Code
class Solution89 {
public:
    vector<int> grayCode(int n) {
        if (n==0)
            return vector<int> ();
        vector<int> ans{0,1};

        for (int i=2; i<=n; i++) {
            vector<int> tmp = ans;
            reverse(tmp.begin(), tmp.end());
            for (auto num : tmp) {
                ans.push_back((1 << (i-1)) | num);
            }
        }

        return ans;
    }
};

//357. Count Numbers with Unique Digits
class Solution357 {
public:
    int countNumbersWithUniqueDigits(int n) {
        if (n == 0) return 1;
        int a = 1, b = 9;
        for (int i = 2; i <= n; ++i) {
            a += b;
            b *= (11 - i);
        }
        return b+a;
    }
};

//494. Target Sum
class Solution494 {
public:
    long findTargetSumWays_dfs(vector<int>::iterator begin,
                               vector<int>::iterator end, long S) {
        if (begin + 1 == end) {
            if (S == 0 && *begin== 0)
                return 2;
            else if (S == *begin || S == -*begin)
                return 1;
            else
                return 0;
        }

        return findTargetSumWays_dfs(begin+1, end, S+*begin) +
               findTargetSumWays_dfs(begin+1, end, S-*begin);
    }

    int findTargetSumWays(vector<int>& nums, int S) {
        return findTargetSumWays_dfs(nums.begin(), nums.end(), S);
    }

};

//784. Letter Case Permutation
class Solution784 {
public:
    void dfs_helper(int step, string S, string& path, vector<string>& result) {
        while (step<S.length() && isdigit(S[step])) {
            path.push_back(S[step++]);
        }
        if (step == S.length()) {
            result.push_back(path);
            return;
        }

        path.push_back(islower(S[step]) ? S[step]: tolower(S[step]));
        dfs_helper(step+1, S, path, result);
        while (isdigit(path.back()))
            path.pop_back();
        path.pop_back();

        path.push_back(islower(S[step]) ? toupper(S[step]): S[step]);
        dfs_helper(step+1, S, path, result);
        while (isdigit(path.back()))
            path.pop_back();
        path.pop_back();
    }
    vector<string> letterCasePermutation(string S) {
        vector<string> result;
        string path;
        dfs_helper(0, S, path, result);
        return result;
    }
};

//1079. Letter Tile Possibilities
class Solution1079 {
public:
    int dfs(unordered_map<char, int> &map) {
        int ans = 0;
        for (auto &it: map) {
            if (it.second==0)
                continue;
            ans++;
            it.second--;
            ans += dfs(map);
            it.second++;
        }
        return ans;
    }

    int numTilePossibilities(string tiles) {
        unordered_map<char,int> map;
        for(auto ch: tiles) {
            map[ch]++;
        }
        return dfs(map);
    }
};

//1593. Split a String Into the Max Number of Unique Substrings

class Solution1593 {
public:
    int maxUniqueSplit(string s) {
        dfs(s, 0);
        return ans;
    }

    void dfs(string& s, int pos) {
        if (s.size() - pos + us.size() <= ans) return;
        if (pos == s.size()) {
            ans = max(ans, (int)us.size());
            return;
        }

        string temp;
        for (int i = pos; i < s.size(); i++) {
            temp += s[i];
            if (us.find(temp) == us.end()) {
                us.insert(temp);
                dfs(s, i + 1);
                us.erase(temp);
            }
        }
    }
private:
    int ans = 0;
    unordered_set<string> us;
};

#endif //NEETCODE150_BACKTRACK_H
