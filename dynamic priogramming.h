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

//53. Maximum Subarray
class Solution53 {
public:
    int maxSubArray(vector<int>& nums) {
        int ans = nums[0];
        int pre = nums[0];
        for (int i=1; i<nums.size(); i++) {
            pre = max(pre, 0) + nums[i];
            ans = max(ans, pre);
        }

        return ans;
    }
};


#endif //NEETCODE150_DYNAMIC_PRIOGRAMMING_H
