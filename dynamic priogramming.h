//
// Created by Wei on 12/11/23.
//

#ifndef NEETCODE150_DYNAMIC_PRIOGRAMMING_H
#define NEETCODE150_DYNAMIC_PRIOGRAMMING_H

#include "common.h"

//10. Regular Expression Matching
class Solution10_dp {
public:
    bool isMatch(const string& s, const string& p) {
        int m = s.length();
        int n = p.length();

        // Create a 2D DP table
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

        // Empty pattern matches empty string
        dp[0][0] = true;

        // Handle patterns with '*' at the beginning
        for (int j = 1; j <= n; ++j) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }

        // Fill in the DP table
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == s[i - 1] || p[j - 1] == '.') {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 2] || (dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
                }
            }
        }

        return dp[m][n];
    }
};

//70. climb stairs
class Solution {
public:
    int climbStairs(int n) {
        int pre = 1;
        int cur = 1;
        for (int i=2; i<=n; i++) {
            pre += cur;
            swap(pre, cur);
        }
        return cur;
    }
};

//746. Min Cost Climbing Stairs
class Solution746 {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int pre = 0;
        int cur = 0;
        for (int i=2; i<=cost.size(); i++) {
            pre = min(pre + cost[i-2], cur + cost[i-1]);
            swap(pre, cur);
        }
        return cur;
    }
};

//198. House Robber
class Solution198 {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0)
            return 0;
        if (n == 1)
            return nums[0];
        int pre = nums[0];
        int cur = max(nums[1], nums[0]);
        for (int i=2; i<n; i++) {
            pre = max(pre + nums[i], cur);
            swap(pre, cur);
        }
        return cur;
    }
};

//213. House Robber II
class Solution213 {
public:
    int rob_base(vector<int>::iterator begin, vector<int>::iterator end) {
        int left = 0;
        int right = 0;
        for (auto itor = begin; itor<end; itor++) {
            left = max(left + *itor, right);
            swap(left, right);
        }
        return right;
    }

    int rob(vector<int>& nums) {
        int length = nums.size();
        if (length==0)
            return 0;
        if (length == 1)
            return nums[0];

        return max(rob_base(nums.begin(), nums.end()-1), rob_base(nums.begin()+1, nums.end()));
    }
};

//5. Longest Palindromic Substring


#endif //NEETCODE150_DYNAMIC_PRIOGRAMMING_H
