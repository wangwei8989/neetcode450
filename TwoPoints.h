//
// Created by Wei on 1/31/24.
//

#ifndef NEETCODE150_TWOPOINTS_H
#define NEETCODE150_TWOPOINTS_H

#include "common.h"
//125. Valid Palindrome
class Solution125 {
public:
    bool isPalindrome(string s) {
        int left = 0;
        int right = s.size() - 1;

        while (left < right) {
            while (!isalnum(s[left]) && left < right) {
                left++;
            }
            while (!isalnum(s[right]) && left < right) {
                right--;
            }
            if (tolower(s[left]) != tolower(s[right])) {
                return false;
            }
            left++;
            right--;
        }

        return true;
    }
};

//167. Two Sum II - Input Array Is Sorted
class Solution167 {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0;
        int right = numbers.size() - 1;
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum == target)
                return vector<int>({left+1, right+1});
            else if (sum < target) {
                left++;
            }
            else {
                right--;
            }
        }
        return vector<int>();
    }
};

//15. 3Sum
class Solution15 {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;

        int n = nums.size();
        if (n < 3) {
            return result;
        }

        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 2; i++) {
            if (nums[i] > 0) {
                break;
            }
            if (i > 0 && nums[i - 1] == nums[i]) {
                continue;
            }

            int j = i + 1;
            int k = n - 1;

            while (j < k) {
                int sum = nums[i] + nums[j] + nums[k];

                if (sum < 0) {
                    j++;
                } else if (sum > 0) {
                    k--;
                } else {
                    result.push_back({nums[i], nums[j], nums[k]});

                    while (j < k && nums[j] == nums[j + 1]) {
                        j++;
                    }
                    j++;

                    while (j < k && nums[k - 1] == nums[k]) {
                        k--;
                    }
                    k--;
                }
            }
        }

        return result;
    }
};

//11. Container With Most Water
class Solution11 {
public:
    int maxArea(vector<int>& height) {
        int i = 0;
        int j = height.size() - 1;

        int curr = 0;
        int result = 0;

        while (i < j) {
            curr = (j - i) * min(height[i], height[j]);
            result = max(result, curr);

            if (height[i] <= height[j]) {
                i++;
            } else {
                j--;
            }
        }

        return result;
    }
};

//42. Trapping Rain Water
class Solution42 {
public:
    int trap(vector<int>& height) {
        int i = 0;
        int j = height.size() - 1;

        int maxLeft = height[i];
        int maxRight = height[j];

        int result = 0;

        while (i < j) {
            if (maxLeft <= maxRight) {
                i++;
                maxLeft = max(maxLeft, height[i]);
                result += maxLeft - height[i];
            } else {
                j--;
                maxRight = max(maxRight, height[j]);
                result += maxRight - height[j];
            }
        }

        return result;
    }
};


#endif //NEETCODE150_TWOPOINTS_H
