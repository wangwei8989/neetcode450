//
// Created by Wei on 2/7/24.
//

#ifndef NEETCODE150_MATH_GEOMETRY_H
#define NEETCODE150_MATH_GEOMETRY_H

#include "common.h"
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
class Solution {
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
