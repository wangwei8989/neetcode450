//
// Created by Wei on 2/11/24.
//

#ifndef NEETCODE150_DP_H
#define NEETCODE150_DP_H

#include "common.h"
//70. Climbing Stairs
class Solution70 {
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

//509. Fibonacci Number
class Solution509 {
public:
    int fib(int N) {
        if (N<2)
            return N;
        int pre= 0;
        int cur = 1;
        for (int i=2; i<=N; i++) {
            pre+=cur;
            swap(pre,cur);
        }
        return cur;
    }
};

//1137. N-th Tribonacci Number
class Solution1137 {
public:
    int tribonacci(int n) {
        vector<int> ans = {0,1,1};
        if (n<3)
            return ans[n];
        for (int i=3; i<=n; i++) {
            tie(ans[0], ans[1], ans[2]) = make_tuple(ans[1], ans[2], ans[0]+ans[1]+ans[2]);
        }
        return ans[2];
    }
};

//746. Min Cost Climbing Stairs
class Solution746 {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        int pre = 0;
        int cur = 0;
        for (int i=2; i<=n; i++) {
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

//740. Delete and Earn
class Solution740 {
public:
    int deleteAndEarn(vector<int>& nums) {
        int n = *max_element(nums.begin(), nums.end());
        vector<int> trans(n+1, 0);
        for (auto &num: nums) {
            trans[num] += num;
        }

        int pre = trans[0];
        int cur = trans[1];
        for (int i=2; i<=n; i++) {
            pre = max(pre + trans[i], cur);
            swap(pre, cur);
        }
        return cur;
    }
};

//5. Longest Palindromic Substring
class Solution5 {
public:
    string longestPalindrome(string s) {
        if (s.empty())
            return "";
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n));
        string ans;

        for (int distance=0; distance<n; distance++) {
            for (int left=0; left+distance<n; left++) {
                int right = left+distance;
                if (distance==0){
                    dp[left][right] = true;
                }
                else if (distance==1) {
                    dp[left][right] = (s[left]==s[right]);
                }
                else {
                    dp[left][right] = (dp[left+1][right-1] && s[left]==s[right]);
                }
                if (dp[left][right] && distance+1>ans.size()) {
                    ans = s.substr(left, distance+1);
                }
            }
        }
        return ans;
    }
};

//647. Palindromic Substrings
class Solution647 {
public:
    int countSubstrings(string s) {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n));
        int total = 0;

        for (int distance=0; distance<n; distance++) {
            for (int left=0; left+distance<n; left++) {
                int right=left+distance;
                if (distance==0){
                    dp[left][right] = true;
                }
                else if (distance==1) {
                    dp[left][right] = (s[left]==s[right]);
                }
                else {
                    dp[left][right] = (dp[left+1][right-1] && s[left]==s[right]);

                }
                if (dp[left][right])
                    total++;
            }
        }
        return total;
    }
};

//91. Decode Ways
class Solution91 {
public:
    int numDecodings(string s) {
        if (s[0] == '0') {
            return 0;
        }

        int n = s.size();
        vector<int> dp(n + 1);
        dp[0] = 1;
        dp[1] = 1;

        for (int i = 2; i <= n; i++) {
            int ones = stoi(s.substr(i - 1, 1));
            if (ones >= 1 && ones <= 9) {
                dp[i] += dp[i - 1];
            }
            int tens = stoi(s.substr(i - 2, 2));
            if (tens >= 10 && tens <= 26) {
                dp[i] += dp[i - 2];
            }
        }

        return dp[n];
    }
};

//322. Coin Change
class Solution322 {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount+1, amount + 1);
        dp[0] = 0;
        for (int i=0; i<amount + 1; i++) {
            for (int j=0; j<coins.size(); j++) {
                if (i >= coins[j])
                    dp[i] = min(dp[i], dp[i-coins[j]] + 1);
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};

//152. Maximum Product Subarray
/*
1.If the previous part of the array had a big positive product, adding the current number might make it even bigger.
2.it's better to start a new subarray with just the current number if it's large enough on its own.
3.If the previous subarray had a negative product, multiplying it with the current number might make it the largest positive product.
*/
class Solution152 {
public:
    int maxProduct(vector<int>& nums) {
        vector<int> maxans(nums), minans(nums);
        for (int i=1; i<nums.size(); i++) {
            maxans[i] = max(maxans[i-1] * nums[i], max(nums[i], minans[i-1]* nums[i]));
            minans[i] = min(maxans[i-1] * nums[i], min(nums[i], minans[i-1]* nums[i]));
        }
        return *max_element(maxans.begin(), maxans.end());
    }
};

//139. Word Break
class Solution139 {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<bool> dp(n+1, false);
        dp[0] = true;
        unordered_set<string> words(wordDict.begin(), wordDict.end());
        for (int i=1; i<=n; i++) {
            for (int j=i-1; j>=0; j--) {
                if (dp[j] && words.count(s.substr(j, i-j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }
};

//300. Longest Increasing Subsequence
class Solution300 {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n,1);
        for (int i=0; i<n; i++) {
            for (int j=0; j<i; j++) {
                if (nums[i] > nums[j])
                    dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};

//673. Number of Longest Increasing Subsequence
class Solution673 {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1);
        vector<int> count(n, 1);

        for (int i=1; i<n; i++) {
            for (int j=0; j<i; j++) {
                if (nums[j] < nums[i]) {
                    if (dp[j]+1 > dp[i]) {
                        dp[i] = dp[j] + 1;
                        count[i] = count[j];
                    } else if (dp[j]+1 == dp[i]) {
                        count[i] += count[j];
                    }
                }
            }
        }

        int maxlen = *max_element(dp.begin(), dp.end());

        int ans = 0;
        for (int i=0; i<n; i++) {
            if (dp[i]==maxlen)
                ans +=count[i];
        }

        return ans;
    }
};

//416. Partition Equal Subset Sum
class Solution416 {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum & 1) {
            return false;
        }
        sum >>= 1;
        bitset<10000> dp;
        dp.set(0);
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            for (int j = sum; j >= num; --j) {
                if (dp[j-num]) {
                    dp.set(j);
                }

            }
        }
        return dp[sum];
    }
};

//120. Triangle
class Solution120  {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Initialize DP array with the values of the last row
        for (int i = 0; i < n; ++i) {
            dp[n - 1][i] = triangle[n - 1][i];
        }

        // Bottom-up approach to calculate minimum path sum
        for (int i = n - 2; i >= 0; --i) {
            for (int j = 0; j <= i; ++j) {
                dp[i][j] = triangle[i][j] + min(dp[i + 1][j], dp[i + 1][j + 1]);
            }
        }

        // Minimum path sum will be stored at the top of the DP array
        return dp[0][0];
    }
};


//256. Paint House
/*
There are a row of n houses, each house can be painted with one of the three colors: red, blue or green. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.
The cost of painting each house with a certain color is represented by a n x 3 cost matrix. For example, costs[0][0] is the cost of painting house 0 with color red; costs[1][2] is the cost of painting house 1 with color green, and so on... Find the minimum cost to paint all houses.
Note:
All costs are positive integers.
Example:
Input: [[17,2,17],[16,16,5],[14,3,19]]
Output: 10
Explanation: Paint house 0 into blue, paint house 1 into green, paint house 2 into blue.
             Minimum cost: 2 + 5 + 3 = 10.
*/
class Solution256 {
public:
    int minCost(vector<vector<int>>& costs) {
        int r = 0, g = 0, b = 0;
        for (auto& cost : costs) {
            int _r = r, _g = g, _b = b;
            r = min(_g, _b) + cost[0];
            g = min(_r, _b) + cost[1];
            b = min(_r, _g) + cost[2];
        }
        return min(r, min(g, b));
    }
};

//377. Combination Sum IV
class Solution377 {
public:
    int combinationSum4(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        //the dp can not be declared as vector<int> or vector<long long>,
        //because signed integers overflow is undefined behavior, while unsigned integers wrap around and is well defined.
        vector<unsigned int> dp(target + 1);
        dp[0] = 1;
        for (int i = 1; i <= target; i++) {
            for (int& num : nums) {
                if (num <= i ) {
                    dp[i] += dp[i - num];
                }
                else
                    break;
            }
        }
        return dp[target];
    }
};

//279. Perfect Squares
class Solution279 {
public:
    int numSquares(int n) {
        vector<int> PerfectSquares;
        for (int i = 1; i * i <= n; i++)
        {
            PerfectSquares.push_back(i * i);
        }

        int Max = n + 1;
        vector<int> dp(n + 1, Max);
        dp[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            for (auto &square: PerfectSquares)
            {
                if (i >= square)
                {
                    dp[i] = min(dp[i], dp[i - square] + 1);
                }
            }
        }

        return dp[n] > n ? -1 : dp[n];
    }
};

//2369. Check if There is a Valid Partition For The Array
class Solution2369 {
public:
    bool validPartition(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return false;

        vector<bool> dp(n, false);

        // Case for two equal elements
        if (nums[0] == nums[1]) dp[1] = true;

        for (int i = 2; i < n; ++i) {
            // Check for partition ending with two equal elements
            if (nums[i] == nums[i - 1]) {
                dp[i] = dp[i] || dp[i - 2];
            }
            // Check for partition ending with three equal elements
            if (i >= 2 && nums[i] == nums[i - 1] && nums[i] == nums[i - 2]) {
                dp[i] = dp[i] || (i >= 3 ? dp[i - 3] : true);
            }
            // Check for partition ending with three consecutive increasing elements
            if (i >= 2 && nums[i] == nums[i - 1] + 1 && nums[i] == nums[i - 2] + 2) {
                dp[i] = dp[i] || (i >= 3 ? dp[i - 3] : true);
            }
        }

        return dp[n - 1];
    }
};

//1856. Maximum Subarray Min-Product
class Solution1856 {
public:
    int maxSumMinProduct(vector<int>& nums) {
        int n = nums.size();
        vector<long long> prefix(n + 1, 0);

        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        // Monotonic stack to find left boundaries
        vector<int> left(n, -1);
        stack<int> st;
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && nums[st.top()] >= nums[i]) {
                st.pop();
            }
            if (!st.empty()) {
                left[i] = st.top();
            }
            st.push(i);
        }

        // Clear the stack to reuse for right boundaries
        while (!st.empty()) {
            st.pop();
        }

        // Monotonic stack to find right boundaries
        vector<int> right(n, n);
        for (int i = n - 1; i >= 0; --i) {
            while (!st.empty() && nums[st.top()] >= nums[i]) {
                st.pop();
            }
            if (!st.empty()) {
                right[i] = st.top();
            }
            st.push(i);
        }

        long long maxMinProduct = 0;
        for (int i = 0; i < n; ++i) {
            long long sum = prefix[right[i]] - prefix[left[i] + 1];
            long long minProduct = nums[i] * sum;
            maxMinProduct = max(maxMinProduct, minProduct);
        }

        return maxMinProduct % MOD;
    }
};

//983. Minimum Cost For Tickets
class Solution983 {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        vector<int> dp(366, 0);
        set<int> travel_days(days.begin(), days.end());

        for (int i = 1; i <= 365; ++i) {
            if (travel_days.find(i) == travel_days.end()) {
                dp[i] = dp[i - 1];
            } else {
                dp[i] = min({
                                dp[i - 1] + costs[0],
                                dp[max(i - 7, 0)] + costs[1],
                                dp[max(i - 30, 0)] + costs[2]
                            });
            }
        }

        return dp[365];
    }
};

//343. Integer Break
class Solution343 {
public:
    int integerBreak(int n) {
        vector<int> dp(n+1);
        dp[1] = 1;
        for (int i=2; i<=n; i++) {
            for (int j = 1; j < i ; j++) {
                dp[i] = max(dp[i], max(j * (i-j), j * dp[i-j]));
            }
        }
        return dp[n];
    }
};

//691. Stickers to Spell Word
class Solution691 {
public:
    int minStickers(vector<string>& stickers, string target) {
        int n = target.size();
        int targetMask = (1 << n) - 1;

        vector<unordered_map<char, int>> stickerCount(stickers.size());
        for (int i = 0; i < stickers.size(); ++i) {
            for (char c : stickers[i]) {
                stickerCount[i][c]++;
            }
        }

        vector<int> dp(1 << n, -1);
        dp[0] = 0;

        queue<int> q;
        q.push(0);

        while (!q.empty()) {
            int mask = q.front();
            q.pop();

            for (int i = 0; i < stickers.size(); ++i) {
                int newMask = mask;
                auto &count = stickerCount[i];
                vector<int> remainingCount(26, 0);

                for (int j = 0; j < n; ++j) {
                    if ((mask >> j) & 1) continue;
                    char c = target[j];
                    if (count.find(c) != count.end() && count[c] > remainingCount[c - 'a']) {
                        newMask |= (1 << j);
                        remainingCount[c - 'a']++;
                    }
                }

                if (dp[newMask] == -1 || dp[newMask] > dp[mask] + 1) {
                    dp[newMask] = dp[mask] + 1;
                    q.push(newMask);
                }
            }
        }

        return dp[targetMask];
    }
};

//1035. Uncrossed Lines
class Solution1035 {
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();

        // DP table where dp[i][j] represents the LCS of nums1[0..i-1] and nums2[0..j-1]
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // Fill the DP table
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        // The result is in dp[m][n]
        return dp[m][n];
    }
};

//2140. Solving Questions With
class Solution2140 {
public:
    long long mostPoints(vector<vector<int>>& questions) {
        int n = questions.size();
        vector<long long> dp(n + 1, 0);

        for (int i = n - 1; i >= 0; --i) {
            int points = questions[i][0];
            int brainpower = questions[i][1];
            dp[i] = max(points + (i + brainpower + 1 < n ? dp[i + brainpower + 1] : 0), dp[i + 1]);
        }

        return dp[0];
    }
};

//2466. Count Ways To Build Good Strings
class Solution2466 {
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        vector<int> dp(high + 1, 0);
        dp[0] = 1; // There is one way to form an empty string.

        for (int length = 0; length <= high; ++length) {
            if (dp[length] > 0) {
                if (length + zero <= high) {
                    dp[length + zero] = (dp[length + zero] + dp[length]) % MOD;
                }
                if (length + one <= high) {
                    dp[length + one] = (dp[length + one] + dp[length]) % MOD;
                }
            }
        }

        int result = 0;
        for (int length = low; length <= high; ++length) {
            result = (result + dp[length]) % MOD;
        }

        return result;
    }
};

//837. New 21 Game
class Solution837 {
public:
    double new21Game(int n, int k, int maxPts) {
        if (k == 0 || n >= k + maxPts) {
            return 1.0;
        }

        vector<double> dp(n + 1, 0.0);
        dp[0] = 1.0;
        double windowSum = 1.0, result = 0.0;

        for (int i = 1; i <= n; ++i) {
            dp[i] = windowSum / maxPts;
            if (i < k) {
                windowSum += dp[i];
            } else {
                result += dp[i];
            }
            if (i - maxPts >= 0) {
                windowSum -= dp[i - maxPts];
            }
        }

        return result;
    }
};

//1626. Best Team With No Conflicts
class Solution1626 {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size();
        vector<pair<int, int>> players(n);
        for (int i = 0; i < n; ++i) {
            players[i] = {ages[i], scores[i]};
        }

        // Sort players by age, and then by score
        sort(players.begin(), players.end());

        // Initialize dp array
        vector<int> dp(n, 0);
        int maxScore = 0;

        for (int i = 0; i < n; ++i) {
            dp[i] = players[i].second;  // The score of the player itself
            for (int j = 0; j < i; ++j) {
                // No conflict if scores[j] <= scores[i]
                if (players[j].second <= players[i].second) {
                    dp[i] = max(dp[i], dp[j] + players[i].second);
                }
            }
            maxScore = max(maxScore, dp[i]);
        }

        return maxScore;
    }
};

//1406. Stone Game III
class Solution1406 {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<int> dp(n + 1, 0);

        for (int i = n - 1; i >= 0; --i) {
            int maxScore = INT_MIN;
            int curScore = 0;
            for (int k = 1; k <= 3 && i + k <= n; ++k) {
                curScore += stoneValue[i + k - 1];
                maxScore = max(maxScore, curScore - dp[i + k]);
            }
            dp[i] = maxScore;
        }

        if (dp[0] > 0) {
            return "Alice";
        } else if (dp[0] < 0) {
            return "Bob";
        } else {
            return "Tie";
        }
    }
};

//1964. Find the Longest Valid Obstacle Course at Each Position
class Solution1964 {
public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
        int n = obstacles.size();
        vector<int> dp(n);
        // Vector to store the indices of the obstacles in the longest increasing subsequence
        vector<int> lis;

        for (int i = 0; i < n; ++i) {
            auto it = upper_bound(lis.begin(), lis.end(), obstacles[i]);
            dp[i] = it - lis.begin() + 1;

            if (it == lis.end()) {
                lis.push_back(obstacles[i]);
            } else { 
                *it = obstacles[i];
            }
        }

        return dp;
    }
};

//1359. Count All Valid Pickup and Delivery Options
/*Intuition:
    The total number of all permutation obviously eauqls to 2n!.
    For each pair, the order is determined, so we need to divide by 2.
    So the final result is (2n)!/(2^n)
 */
class Solution1359 {
public:
    int countOrders(int n) {
        vector<int> dp(n + 1);
        dp[1] = 1;

        for (int i = 2; i <= n; ++i) {
            // factorial(2n) = 2n * (2n - 1) * factorial(2(n-1))
            dp[i] = (static_cast<long long>(dp[i - 1]) * i * (2 * i - 1)) % MOD;
        }

        return dp[n];
    }
};

/************************************2-D dynamic programming********************************/
//62. Unique Paths
class Solution62 {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 1));
        for (int i=1; i<m; i++) {
            for (int j=1; j<n; j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};

//63. Unique Paths II
class Solution63 {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<vector<int>> dp(m, vector<int>(n,0));
        for (int i=0; i<m; i++) {
            if (obstacleGrid[i][0])
                break;
            dp[i][0] = 1;
        }

        for (int i=0; i<n; i++) {
            if (obstacleGrid[0][i])
                break;
            dp[0][i] = 1;
        }


        for (int i=1; i<m; i++) {
            for (int j=1; j<n; j++) {
                if (obstacleGrid[i][j])
                    continue;
                if (!obstacleGrid[i-1][j])
                    dp[i][j] += dp[i-1][j];
                if (!obstacleGrid[i][j-1])
                    dp[i][j] += dp[i][j-1];
            }
        }

        return dp[m-1][n-1];
    }
};

//1143. Longest Common Subsequence
class Solution1143 {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length();
        int n= text2.length();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for (int i=1; i<=m; i++) {
            for (int j=1; j<=n; j++) {
                if (text1[i-1] == text2[j-1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        return dp[m][n];
    }
};

//516. Longest Palindromic Subsequence
class Solution516 {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n));

        for (int length=0; length<n; length++) {
            for (int left=0; left+length<n; left++) {
                int right=left+length;
                if (length==0) {
                    dp[left][right]=1;
                }
                else if (s[left]==s[right]) {
                    if (length==1)
                        dp[left][right] = 2;
                    else
                        dp[left][right] = dp[left+1][right-1] + 2;
                }
                else {
                    dp[left][right] = max(dp[left][right-1], dp[left+1][right]);
                }
            }
        }
        return dp[0][n-1];
    }
};

//1049. Last Stone Weight II
class Solution1049 {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int totalWeight = accumulate(stones.begin(), stones.end(), 0);
        // Target weight is to try splitting stones into two groups with equal weight
        int targetWeight = totalWeight >> 1;
        vector<int> dp(targetWeight + 1, 0);

        // DP approach to find the closest sum to the targetWeight
        for (auto& stone : stones) {
            // Traverse dp array backwards for this pass, to avoid using a stone twice
            for (int j = targetWeight; j >= stone; --j) {
                // Update dp[j] to the higher of the two values;
                // either the current dp[j] or the sum of stone and dp[j - stone] if we include the stone
                dp[j] = max(dp[j], dp[j - stone] + stone);
            }
        }

        // The answer is the total weight minus twice the optimized closest sum to half of the total weight
        // This represents the minimal possible weight difference between two groups
        return totalWeight - dp[targetWeight] * 2;
    }
};

//309. Best Time to Buy and Sell Stock with Cooldown
class Solution309 {
public:
    int maxProfit(vector<int>& prices) {
        int buy = -prices[0], sell = 0, lock = 0;
        for (auto& p : prices)
        {
            buy = max(buy, lock - p);
            lock = max(sell, buy + p);
            swap(lock, sell);
        }
        return sell;
    }
};

//877. Stone Game
class Solution877 {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>> dp(n+1, vector<int>(n+1));
        for (int len = 0; len < n; len++) {
            for (int left = 0; left+len < n; left++) {
                if (len == 0) {
                    dp[left][left] = piles[left];
                    continue;
                }

                int right = left + len;
                dp[left][right] = max(piles[left] - dp[left+1][right], piles[right] - dp[left][right-1]);
            }
        }
        return dp[0][n-1] > 0;
    }
};

//64. Minimum Path Sum
class Solution64 {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m));
        dp[0][0] = grid[0][0];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }
                dp[i][j] = grid[i][j] + min( ((i>0) ? dp[i-1][j] : INT_MAX),
                                             ((j>0) ? dp[i][j-1] : INT_MAX));
            }
        }
        return dp[n-1][m-1];
    }
};

//329. Longest Increasing Path in a Matrix
class Solution329 {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        int result = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result = max(result, dfs(matrix, -1, i, j, m, n));
            }
        }

        return result;
    }
private:
    // {(i, j) -> longest increasing path at (i, j)}
    map<pair<int, int>, int> dp;

    int dfs(vector<vector<int>>& matrix, int prev, int i, int j, int m, int n) {
        if (i < 0 || i >= m || j < 0 || j >= n || matrix[i][j] <= prev) {
            return 0;
        }
        if (dp.find({i, j}) != dp.end()) {
            return dp[{i, j}];
        }

        int result = 1;
        result = max(result, 1 + dfs(matrix, matrix[i][j], i - 1, j, m, n));
        result = max(result, 1 + dfs(matrix, matrix[i][j], i + 1, j, m, n));
        result = max(result, 1 + dfs(matrix, matrix[i][j], i, j - 1, m, n));
        result = max(result, 1 + dfs(matrix, matrix[i][j], i, j + 1, m, n));
        dp[{i, j}] = result;

        return dp[{i, j}];
    }
};

//221. Maximal Square
class Solution221 {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int rows = matrix.size(), cols = matrix[0].size();

        vector<vector<int>> dp (rows+1, vector<int>(cols+1, 0));
        int maxi = 0;
        for(int i = rows-1 ; i >= 0; --i) {
            for(int j = cols-1 ; j >=0 ; --j) {
                if(matrix[i][j] == '1') {
                    int right = dp[i][j+1], dia = dp[i+1][j+1], bottom = dp[i+1][j];

                    dp[i][j] = 1 + min(right, min(dia, bottom));
                    maxi = max(maxi, dp[i][j]);
                }
                else {
                    dp[i][j] = 0;
                }
            }
        }
        return maxi*maxi;
    }
};

//474. Ones and Zeroes
class Solution474 {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (auto& str: strs) {
            int zeros = count(str.begin(), str.end(), '0');
            int ones = str.size() - zeros;

            for (int i = m; i >= zeros; --i) {
                for (int j = n; j >= ones; --j) {
                    dp[i][j] = max(dp[i][j], dp[i-zeros][j-ones] + 1);
                }
            }
        }

        return dp[m][n];
    }
};

//115. Distinct Subsequences
class Solution115 {
public:
    int numDistinct(string s, string t) {
        int m = s.length();
        int n = t.length();
        if (m < n) {
            return 0;
        }
        vector<vector<unsigned long long>> dp(m + 1, vector<unsigned long long>(n + 1));
        for (int i = 0; i <= m; i++) {
            dp[i][n] = 1;
        }
        for (int i = m - 1; i >= 0; i--) {
            char sChar = s[i];
            for (int j = n - 1; j >= 0; j--) {
                char tChar = t[j];
                if (sChar == tChar) {
                    dp[i][j] = dp[i + 1][j + 1] + dp[i + 1][j];
                } else {
                    dp[i][j] = dp[i + 1][j];
                }
            }
        }
        return dp[0][0];
    }
};

//72. Edit Distance
class Solution72 {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // Initialize first row and first column
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = i;
        }
        for (int j = 0; j <= n; ++j) {
            dp[0][j] = j;
        }

        // Fill dp array
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                /* if chars at i & j same, no operations needed,
                 * else 3 cases: (1) replace (i - 1, j - 1), (2) delete (i - 1, j), (3) insert (i, j - 1) */
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                }
            }
        }

        return dp[m][n];
    }
};

//1220. Count Vowels Permutation
class Solution1220 {
    int countVowelPermutation(int n) {
        vector<vector<unsigned>> dp(n, vector<unsigned>(5, 0));

        for (int j = 0; j < 5; ++j) {
            dp[0][j] = 1;
        }

        for (int i = 1; i < n; ++i) {
            dp[i][0] = dp[i - 1][1]; // 'a' can only be followed by 'e'
            dp[i][1] = (dp[i - 1][0] + dp[i - 1][2]) % MOD; // 'e' can be followed by 'a' or 'i'
            dp[i][2] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][3] + dp[i - 1][4]) % MOD; // 'i' cannot be followed by 'i'
            dp[i][3] = (dp[i - 1][2] + dp[i - 1][4]) % MOD; // 'o' can be followed by 'i' or 'u'
            dp[i][4] = dp[i - 1][0]; // 'u' can only be followed by 'a'
        }

        int total = 0;
        for (int j = 0; j < 5; ++j) {
            total = (total + dp[n - 1][j]) % MOD;
        }

        return total;
    }
};

//312. Burst Balloons
class Solution312_bottomUp {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        nums.insert(nums.begin(), 1);
        nums.push_back(1);

        for (int len=1; len<=n; len++) {
            for (int left=1; left+len-1<=n; left++) {
                int right = left+len-1;
                //divide and conquer
                for (int k=left; k<=right; k++) {
                    int curr = nums[left-1]* nums[k]* nums[right+1];
                    int remaining = dp[left][k-1] + ((k+1>n) ? 0 : dp[k+1][right]);
                    dp[left][right] = max(dp[left][right], curr + remaining);
                }
            }
        }
        return dp[1][n];
    }
};

class Solution312_topDown {
public:
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.insert(nums.end(), 1);
        int n = nums.size();

        // cache results of dp
        vector<vector<int>> memo(n, vector<int>(n, 0));

        // 1 & n - 2 since we can't burst our fake balloons
        return dp(nums, memo, 1, n - 2);
    }
private:
    int dp(vector<int>& nums, vector<vector<int>>& memo, int left, int right) {
        if (right - left < 0) {
            return 0;
        }

        if (memo[left][right] > 0) {
            return memo[left][right];
        }

        int result = 0;
        for (int i = left; i <= right; i++) {
            int curr = nums[left - 1] * nums[i] * nums[right + 1];
            int remaining = dp(nums, memo, left, i - 1) + dp(nums, memo, i + 1, right);
            result = max(result, curr + remaining);
        }

        memo[left][right] = result;
        return result;
    }
};

//1866. Number of Ways to Rearrange Sticks With K Sticks Visible
class Solution1866 {
public:
    int rearrangeSticks(int n, int k) {
        vector<vector<unsigned>> dp(n + 1, vector<unsigned>(k + 1, 0));
        dp[0][0] = 1;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= k && j<=i; ++j) {
                dp[i][j] = (dp[i - 1][j - 1] + static_cast<long long>(dp[i - 1][j] * (i - 1))) % MOD;
            }
        }

        return dp[n][k];
    }
};

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

//2218. Maximum Value of K Coins From Piles
class Solution2218 {
public:
    int maxValueOfCoins(vector<vector<int>>& a, int k) {
        int n = a.size();
        for (auto& b : a)
            for (int i=1; i<b.size(); ++i)
                b[i] += b[i-1];
        vector<vector<int>> f(n+1, vector<int>(k+1, 0));
        for (int i=1; i<=n; ++i) {
            for (int j=1; j<=k; ++j){
                f[i][j] = f[i-1][j];
                for (int x=1; x<=min<int>(a[i-1].size(), j); ++x)
                    f[i][j] = max(f[i][j], f[i-1][j-x]+a[i-1][x-1]);
            }
        }
        return f[n][k];
    }
};

class Solution2218_memo {
public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        vector<vector<int>> mem(piles.size(), vector<int>(k + 1));
        return maxValueOfCoins(piles, 0, k, mem);
    }

private:
    // Returns the maximum value of picking k coins from piles[i..n)
    int maxValueOfCoins(const vector<vector<int>>& piles, int i, size_t k,
                        vector<vector<int>>& mem) {
        if (i == piles.size() || k == 0)
            return 0;
        if (mem[i][k])
            return mem[i][k];

        // Pick no coins from the current pile.
        int res = maxValueOfCoins(piles, i + 1, k, mem);
        int val = 0;  // the coins picked from the current pile

        // Try to pick 1, 2, ..., k coins from the current pile.
        for (int j = 0; j < min(piles[i].size(), k); ++j) {
            val += piles[i][j];
            res = max(res, val + maxValueOfCoins(piles, i + 1, k - j - 1, mem));
        }

        return mem[i][k] = res;
    }
};

//1639. Number of Ways to Form a Target String Given a Dictionary
class Solution1639 {
public:
    int numWays(vector<string>& words, string target) {
        int m = target.size();
        int n = words[0].size();
        vector<vector<int>> cnt(n, vector<int>(26));
        for (auto& w : words) {
            for (int j = 0; j < n; ++j) {
                ++cnt[j][w[j] - 'a'];
            }
        }
        vector<vector<int>> f(m, vector<int>(n, -1));
        function<int(int, int)> dfs = [&](int i, int j) -> int {
            if (i >= m) {
                return 1;
            }
            if (j >= n) {
                return 0;
            }
            if (f[i][j] != -1) {
                return f[i][j];
            }
            int ans = dfs(i, j + 1);
            ans = (ans + 1LL * dfs(i + 1, j + 1) * cnt[j][target[i] - 'a']) % MOD;
            return f[i][j] = ans;
        };
        return dfs(0, 0);
    }
};

//879. Profitable Schemes
class Solution879 {
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        int m = group.size();
        vector<vector<vector<int>>> f(m, vector<vector<int>>(n+1, vector<int>(minProfit+1, -1)));
        function<int(int, int, int)> dfs = [&](int i, int j, int k) -> int {
            if (i >= m) {
                return k == minProfit ? 1 : 0;
            }
            if (f[i][j][k] != -1) {
                return f[i][j][k];
            }
            int ans = dfs(i + 1, j, k);
            if (j + group[i] <= n) {
                ans += dfs(i + 1, j + group[i], min(k + profit[i], minProfit));
            }
            ans %= MOD;
            return f[i][j][k] = ans;
        };
        return dfs(0, 0, 0);
    }
};

//1547. Minimum Cost to Cut a Stick
class Solution1547_brute {
public:
    int minCost(int n, vector<int> &cuts) {
        sort(cuts.begin(), cuts.end());
        vector<vector<int>> dp(n, vector<int>(n+1, 0));
        for (int length=2; length<=n; length++) {
            for (int left=0; left+length<=n; left++) {
                int right = left + length;
                int minCost = INT_MAX;
                for (auto &cut: cuts) {
                    if (cut >= right)
                        break;
                    if (cut > left) {
                        minCost = min(minCost, dp[left][cut] + dp[cut][right] + right - left);
                    }
                }
                dp[left][right] = (minCost == INT_MAX) ? 0 : minCost;
            }
        }
        return dp[0][n];
    }
};

class Solution1547 {
public:
    int minCost(int n, vector<int> &cuts) {
        cuts.push_back(0);
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());
        int m = cuts.size();
        vector<vector<int>> dp(m, vector<int>(m,0));
        for (int length=2; length<m; length++) {
            for (int left=0; left + length<m; left++) {
                int right = left + length;
                int mincost = INT_MAX;
                for (int cutIndex=0; cutIndex<m; cutIndex++) {
                    if (cutIndex >= right)
                        break;
                    if (cutIndex > left) {
                        mincost = min(mincost, dp[left][cutIndex] + dp[cutIndex][right]);
                    }
                }
                dp[left][right] = ((mincost == INT_MAX) ? 0 : mincost) + cuts[right] - cuts[left];
                //cout << "dp[" << left << "][" << right << "]:" << dp[left][right] << endl;
            }
        }
        return dp[0][m-1];
    }
};
#endif //NEETCODE150_DP_H
