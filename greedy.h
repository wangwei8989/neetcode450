//
// Created by Wei on 1/22/24.
//

#ifndef NEETCODE150_GREEDY_H
#define NEETCODE150_GREEDY_H

#include "common.h"

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

//918. Maximum Sum Circular Subarray
class Solution918 {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int maxst = nums[0];
        int pre = nums[0];
        int n = nums.size();
        for (int i=1; i<nums.size(); i++) {
            pre = max(pre, 0) + nums[i];
            maxst = max(maxst, pre);
        }
        pre = 0;
        int minst = nums[0];
        for (int i=1; i<nums.size(); i++) {
            pre = min(pre, 0) + nums[i];
            minst = min(pre, minst);
        }
        return max(maxst, accumulate(nums.begin(), nums.end(), 0) - minst);
    }
};

//978. Longest Turbulent Subarray
class Solution978_greedy {
public:
    int maxTurbulenceSize(const std::vector<int>& arr) {
        int n = arr.size();

        if (n <= 1)
            return n;

        int maxLength = 1;
        int curLength = 1;
        int prevCmp = 0;  // 0 represents equal, -1 represents decreasing, 1 represents increasing

        for (int i = 1; i < n; ++i) {
            int cmp = arr[i] > arr[i - 1] ? 1 : (arr[i] < arr[i - 1] ? -1 : 0);

            if (cmp == 0) {
                curLength = 1;
            } else if (cmp * prevCmp == -1) {
                curLength++;
            } else {
                curLength = 2;
            }

            maxLength = std::max(maxLength, curLength);
            prevCmp = cmp;
        }

        return maxLength;
    }
};

//55. Jump Game
class Solution55 {
public:
    bool canJump(vector<int>& nums) {
        int maxReach = 0;
        int n = nums.size();

        for (int i = 0; i < n; ++i) {
            // Check if the current position is reachable
            if (i > maxReach) {
                return false;
            }

            // Update the maximum reach if needed
            maxReach = max(maxReach, i + nums[i]);

            // If the maximum reach is beyond or at the last index, return true
            if (maxReach >= n - 1) {
                return true;
            }
        }

        return false;
    }
};

//45. Jump Game II
class Solution45 {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return 0; // Already at the end
        }

        int jumps = 0;
        int currentEnd = 0;
        int farthest = 0;

        for (int i = 0; i < n - 1; ++i) {
            farthest = std::max(farthest, i + nums[i]);

            if (i == currentEnd) {
                ++jumps;
                currentEnd = farthest;

                if (currentEnd >= n - 1) {
                    break; // Reached the end
                }
            }
        }

        return jumps;
    }
};

//1871. Jump Game VII
class Solution1871_greedy {
public:
    bool canReach(string s, int minJump, int maxJump) {
        if (s.back() == '1')
            return false;
        if (minJump == 1) {
            int i = 0;
            while (i<s.length() && s[i] == '0')
                i++;
            return helper(s, i-1, minJump, maxJump);
        }
        else {
            return helper(s, 0, minJump, maxJump);
        }
    }

private:
    unordered_map<int, bool> visited;
    bool helper(const string& s, int i, int minJump, int maxJump) {
        if (i==s.length()-1 && s[i]=='0')
            return true;
        for (int distance= maxJump; distance >= minJump; distance--) {
            if (i+distance<=s.length()-1 && s[i+distance] == '0') {
                if (visited.find(i+distance) == visited.end()) {
                    visited[i+distance] = helper(s, i+distance, minJump, maxJump);
                }
                if (visited[i+distance])
                    return true;
            }
        }
        return false;
    }
};

//846. Hand of Straights
class Solution846 {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        int n = hand.size();

        if (n % groupSize != 0) {
            return false;
        }

        // map {card value -> count}
        map<int, int> m;
        for (int i = 0; i < n; i++) {
            m[hand[i]]++;
        }

        while (!m.empty()) {
            int curr = m.begin()->first;
            for (int i = 0; i < groupSize; i++) {
                if (m[curr + i] == 0) {
                    return false;
                }
                m[curr + i]--;
                if (m[curr + i] < 1) {
                    m.erase(curr + i);
                }
            }
        }

        return true;
    }
};

//1899. Merge Triplets to Form Target Triplet
class Solution1899 {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        bool a = false, b = false, c = false;
        for (const auto &arr: triplets) {
            if (arr[0] > target[0] || arr[1] > target[1] || arr[2] > target[2])
                continue;
            if (arr[0] == target[0])
                a = true;
            if (arr[1] == target[1])
                b = true;
            if (arr[2] == target[2])
                c = true;
        }
        return a && b && c;
    }
};

//763. Partition Labels
class Solution763 {
public:
    vector<int> partitionLabels(string s) {
        unordered_map<char, int> m;
        vector<int> ans;
        int left = 0;
        int right = 0;
        for (int i=0; i<s.length(); i++) {
            if (m.count(s[i])==0) {
                m[s[i]] = s.find_last_of(s[i]);
            }
            right = max(right, m[s[i]]);
            if (i==right) {
                ans.push_back(right - left + 1);
                left = right + 1;
            }
        }
        return ans;
    }
};

//678. Valid Parenthesis String
class Solution678 {
public:
    bool checkValidString(string s) {
        int n = s.size();

        int balanced = 0;
        for(int i=0; i<n; i++) {
            if(s[i] == '(' || s[i] == '*')
                balanced++;
            else
                balanced--;

            if(balanced < 0)
                return false;
        }

        if(balanced == 0)
            return true;

        balanced = 0;
        for(int i=n-1; i>=0; i--) {
            if(s[i] == ')' || s[i] == '*')
                balanced++;
            else
                balanced--;

            if(balanced < 0)
                return false;
        }

        return true;
    }
};

//1921. Eliminate Maximum Number of Monsters
class Solution1921 {
public:
    int eliminateMaximum(vector<int>& dist, vector<int>& speed) {
        vector<double> time;
        int n = dist.size();
        for (int i=0; i<n; i++) {
            time.push_back(static_cast<double>(dist[i]) / speed[i]);
        }
        sort(time.begin(), time.end());
        int ans = 1;
        int tick = 1;
        for (int i=1; i<n; i++) {
            if (time[i]<=tick)
                return ans;
            tick++;
            ans++;
        }
        return ans;
    }
};

//122. Best Time to Buy and Sell Stock II
class Solution122 {
public:
    int maxProfit(vector<int>& prices) {
        int buy = INT_MIN, sell = 0;
        // 因为需要多次买卖，所以每天都要尝试是否能获得更多利润
        for (auto& p : prices)
        {
            buy = max(buy, sell - p);
            sell = max(sell, buy + p);
        }
        return sell;
    }
};

//134. Gas Station
class Solution134 {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();

        int totalGas = 0;
        int currentGas = 0;
        int startStation = 0;

        for (int i = 0; i < n; ++i) {
            totalGas += gas[i] - cost[i];
            currentGas += gas[i] - cost[i];

            // If you can't reach the next station, update the start station
            if (currentGas < 0) {
                currentGas = 0;
                startStation = i + 1;
            }
        }

        // If the total gas is negative, there is no solution
        return (totalGas >= 0) ? startStation % n : -1;
    }
};

//409. Longest Palindrome
class Solution409 {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> map;
        for (auto c:s) {
            map[c]++;
        }

        int cnt = 0;
        int odd = 0;
        for (auto &[c, n]: map) {
            //if (!(n&1)) {
            cnt += n/2 *2;
            //}
            //else {
            //    odd++;
            //}
            if (n % 2 == 1 and cnt % 2 == 0)
                ++cnt;
        }
        return cnt;
    }
};

//561. Array Partition
class Solution561 {
public:
    int arrayPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int result =0;
        for (int i=0; i<nums.size(); i+=2) {
            result += nums[i];
        }
        return result;
    }
};

//1055.Shortest-Way-to-Form-String
/*
 From any string, we can form a subsequence of that string by deleting some number of characters (possibly no deletions).
Given two strings source and target, return the minimum number of subsequences of source such that their concatenation equals target. If the task is impossible, return -1.

Example 1:
Input: source = "abc", target = "abcbc"
Output: 2
Explanation: The target "abcbc" can be formed by "abc" and "bc", which are subsequences of source "abc".

Example 2:
Input: source = "abc", target = "acdbc"
Output: -1
Explanation: The target string cannot be constructed from the subsequences of source string due to the character "d" in target string.

Example 3:
Input: source = "xyz", target = "xzyxz"
Output: 3
Explanation: The target string can be constructed as follows "xz" + "y" + "xz".

Constraints:
Both the source and target strings consist of only lowercase English letters from "a"-"z".
The lengths of source and target string are between 1 and 1000.
 */
class Solution1055 {
public:
    int shortestWay(string source, string target) {
        int ans = 0;

        for (int i = 0; i < target.length();) {
            const int prevIndex = i;
            for (int j = 0; j < source.length(); ++j)
                if (i < target.length() && source[j] == target[i])
                    ++i;
            // All chars in source didn't match target[i]
            if (i == prevIndex)
                return -1;
            ++ans;
        }

        return ans;
    }
};

#endif //NEETCODE150_GREEDY_H
