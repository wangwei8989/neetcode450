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

#endif //NEETCODE150_GREEDY_H
