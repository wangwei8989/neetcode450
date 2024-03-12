//
// Created by Wei on 2/7/24.
//

#ifndef NEETCODE150_MATH_GEOMETRY_H
#define NEETCODE150_MATH_GEOMETRY_H

#include "common.h"
//168. Excel Sheet Column Title
class Solution168 {
public:
    string convertToTitle(int columnNumber) {
        string ans;
        while (columnNumber > 0) {
            ans += 'A' + (columnNumber - 1) % 26;
            columnNumber = (columnNumber - 1) / 26;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

//1071. Greatest Common Divisor of Strings
class Solution1071 {
public:
    string gcdOfStrings(string str1, string str2) {
        if(str1.length() < str2.length()){
            swap(str1, str2);
        }

        string ans = "";
        ushort shortest_length = str2.length();
        ushort longest_length = str1.length();

        for(ushort i = shortest_length; i > 0; --i)
        {
            if (longest_length % i != 0 || shortest_length % i != 0) continue;

            for(ushort j = 0; j < longest_length; ++j)
            {
                ushort first_pointer = j % i;
                ushort second_pointer = j % shortest_length;

                if(str2[first_pointer] != str1[j] || str2[second_pointer] != str1[j])
                {
                    ans = "";
                    break;
                }

                if(first_pointer == j)
                    ans += str1[j];
            }

            if(ans != "")
                return ans;
        }

        return "";
    }
};

//1572. Matrix Diagonal Sum
class Solution1572 {
public:
    int diagonalSum(vector<vector<int>>& mat) {
        if (mat.empty())
            return 0;
        int m = mat.size();
        int result = 0;
        for (int i=0; i<m; i++) {
            result += mat[i][i];
        }
        for (int i=m-1; i>=0; i--) {
            result += mat[i][m-1-i];
        }

        if (m % 2 == 1) {
            result -= mat[m/2][m/2];
        }

        return result;
    }
};

//149. Max Points on a Line
class Solution149 {
public:
    int maxPoints(vector<vector<int>>& points) {
        int res = 1;
        for (int i=0; i<points.size(); ++i) {
            unordered_map<float, int> count;
            for (int j=i+1; j<points.size(); ++j) {
                float s = slope(points[i], points[j]);
                count[s] ++;
                res = max(res, count[s] + 1);
            }
        }
        return res;
    }
private:
    float slope(vector<int>& p1, vector<int>& p2) {
        if ((p2[0] - p1[0]) == 0)
            return INT_MAX; // aka edge case to handle a slope of infinity
        return (float) (p2[1] - p1[1]) / (float) (p2[0] - p1[0]);
    }
};

//48. Rotate Image
class Solution48 {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for(int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};

//54. Spiral Matrix
class Solution54 {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int top = 0;
        int bottom = matrix.size() - 1;
        int left = 0;
        int right = matrix[0].size() - 1;
        vector<int> result;
        while (left <= right && top <= bottom) {
            for (int i=left; i<=right; i++) {
                result.push_back(matrix[top][i]);
            }
            top++;
            for (int i=top; i<=bottom; i++) {
                result.push_back(matrix[i][right]);
            }
            right--;
            if (top<=bottom) {
                for (int i=right; i>=left; i--) {
                    result.push_back(matrix[bottom][i]);
                }
            }
            bottom--;
            if (left<=right) {
                for (int i=bottom; i>=top; i--) {
                    result.push_back(matrix[i][left]);
                }
            }
            left++;
        }
        return result;
    }
};

//73. Set Matrix Zeroes
class Solution73 {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        bool firstColZero = false;
        bool firstRowZero = false;
        int m = matrix.size();
        int n = matrix[0].size();

        for (int i=0; i<m; i++) {
            if (matrix[i][0] == 0) {
                firstColZero = true;
                break;
            }
        }
        for (int j=0; j<n; j++) {
            if (matrix[0][j] == 0) {
                firstRowZero = true;
                break;
            }
        }
        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++) {
                if(matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        for (int i=1; i<m; i++) {
            for (int j=1; j<n; j++) {
                if(matrix[0][j] == 0 || matrix[i][0] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }
        if (firstColZero) {
            for (int i=0; i<m; i++) {
                matrix[i][0] = 0;
            }
        }

        if (firstRowZero) {
            for (int j=0; j<n; j++) {
                matrix[0][j] = 0;
            }
        }
    }
};

//202. Happy Number
class Solution202 {
public:
    bool isHappy(int n) {
        unordered_set<int> s;
        do {
            s.insert(n);
            int temp = 0;
            while (n) {
                temp += pow(n % 10, 2);
                n /= 10;
            }
            if (temp == 1)
                return true;
            if (s.count(temp))
                return false;
            n = temp;
        } while(true);
    }
};

//66. Plus One
class Solution66 {
public:
    vector<int> plusOne(vector<int>& digits) {
        int carry = 0;
        int i = digits.size() - 1;
        do {
            digits[i] = digits[i] + carry + (i==digits.size() - 1 ? 1 : 0);
            if (digits[i] >= 10) {
                digits[i] = digits[i] % 10;
                carry = 1;
            } else {
                carry = 0;
            }
        } while(--i < digits.size() && carry != 0);
        if (carry != 0) {
            digits.insert(digits.begin(), 1);
        }
        return digits;
    }
};

//9. Palindrome Number
class Solution9 {
public:
    bool isPalindrome(int x) {
        if(x < 0) return false;

        long div = 1;
        while(x >= 10 * div)
            div *= 10;

        while(x) {
            int right = x % 10;
            int left = x / div;

            if(left != right) return false;

            x = (x % div) / 10;
            div = div / 100;
        }
        return true;
    }
};

//263. Ugly Number
class Solution263 {
public:
    bool isUgly(int n) {
        if(n <= 0)
            return false;

        for(int p: {2, 3, 5})
            while(n % p == 0)
                n = n / p;
        return n == 1;
    }
};

//1260. Shift 2D Grid
class Solution1260 {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        const int M = grid.size(), N = grid[0].size();

        auto posToVal = [&] (int r, int c) -> int {
            return r * N + c;};
        auto valToPos = [&] (int v) -> int* {
            return new int[] {v / N, v % N};};

        vector<vector<int>> res;
        for(int r = 0; r < M; r++) {
            vector<int> row;
            for(int c = 0; c < N; c++)
                row.push_back(0);
            res.push_back(row);
        }
        for(int r = 0; r < M; r++)
            for(int c = 0; c < N; c++) {
                int newVal = (posToVal(r, c) + k) % (M * N);
                int *newRC = valToPos(newVal);
                res[newRC[0]][newRC[1]] = grid[r][c];
            }
        return res;
    }
};

//13. Roman to Integer
class Solution13 {
public:
    int romanToInt(string s) {
        unordered_map<char, int> map{{'I',1}, {'V',5}, {'X',10}, {'L',50}, {'C',100}, {'D',500}, {'M',1000}};
        int sum = 0;
        char pre = s[0];
        char cur = ' ';
        for (int i=1; i<s.length(); i++) {
            cur = s[i];
            if (pre == ' ') {
                pre = cur;
            }
            else if (map[cur]>map[pre]) {
                sum += map[cur];
                sum -= map[pre];
                pre = ' ';
            }
            else {
                sum += map[pre];
                pre = cur;
            }
        }
        sum += pre==' ' ? 0 : map[pre];
        return sum;
    }
};

//12. Integer to Roman
class Solution12 {
public:
    string intToRoman(int num) {
        string ans;
        unordered_map<int, string> V2S{
                {1000, "M"},
                {900, "CM"},
                {500, "D"},
                {400, "CD"},
                {100, "C"},
                {90, "XC"},
                {50, "L"},
                {40, "XL"},
                {10, "X"},
                {9, "IX"},
                {5, "V"},
                {4, "IV"},
                {1, "I"}
        };
        for (auto mo: {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1}) {
            while (num >= mo) {
                ans += V2S[mo];
                num -= mo;
            }
        }
        return ans;
    }
};

//50. Pow(x, n)
class Solution50 {
public:
    double powBase(double x, int n) {
        if (n == 0)
            return 1.0;
        double y = powBase(x, n/2);
        return n&1 ? y * y * x : y * y;
    }
    double myPow(double x, int n) {
        return n<0 ? 1.0/powBase(x, n): powBase(x, n);
    }
};

//43. Multiply Strings
class Solution43 {
public:
    string multiply(string num1, string num2) {
        int m = num1.size();
        int n = num2.size();
        string result(m+n, '0');
        for (int i=m-1; i>=0; i--) {
            for (int j=n-1; j>=0; j--) {
                int sum = (num1[i] - '0') * (num2[j] - '0') + (result[i+j+1] - '0');
                result[i+j+1] = (sum % 10) + '0';
                result[i+j] += (sum / 10);
            }
        }
        for (int i=0; i<m+n; i++) {
            if (result[i] != '0')
                return result.substr(i);
        }
        return "0";
    }
};

//2013. Detect Squares
class DetectSquares {
    struct pair_hash{
        template <class T1, class T2>
        size_t operator() (const pair<T1, T2>& p) const {
            return (hash<T1> () (p.first)) ^ (hash<T2> () (p.second));
        }
    };
public:
    DetectSquares() = default;

    void add(vector<int> point) {
        points[{point[0], point[1]}]++;
    }

    int count(vector<int> point) {
        int px = point[0];
        int py = point[1];
        int result = 0;
        for (const auto &[p, cnt]: points) {
            int x, y;
            tie(x, y) = p;
            if (px != x && abs(px-x) == abs(py - y)) {
                auto it1 = points.find({x, py});
                auto it2 = points.find({px, y});
                if (it1 != points.end() && it2 != points.end()) {
                    result += cnt * points[{x, py}] * points[{px, y}];
                }
            }
        }
        return result;
    }

private:
    unordered_map<pair<int, int>, int, pair_hash> points;
};
#endif //NEETCODE150_MATH_GEOMETRY_H
