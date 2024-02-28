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

//680. Valid Palindrome II
class Solution680 {
private:
    bool validPalindromeUtil(string s, int i, int j) {
        while(i < j)
            if(s[i] == s[j]) {
                i++;
                j--;
            } else
                return false;
        return true;
    }
public:
    bool validPalindrome(string s) {
        int i = 0, j = s.length() - 1;

        while(i < j)
            if(s[i] == s[j]) {
                i++;
                j--;
            } else
                return validPalindromeUtil(s, i + 1, j) || validPalindromeUtil(s, i, j - 1);
        return true;
    }
};

//1984. Minimum Difference Between Highest and Lowest of K Scores
class Solution1984 {
public:
    int minimumDifference(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int left = 0;
        int right = k - 1;
        int ans = INT_MAX;
        while (right < nums.size()) {
            ans = min(ans, nums[right] - nums[left]);
            right++;
            left++;
        }
        return ans;
    }
};

//1768. Merge Strings Alternately
class Solution1768 {
public:
    string mergeAlternately(string word1, string word2)
    {
        int i=0;
        string final="";

        while(i < word1.size() && i < word2.size())
            final = final + word1[i] + word2[i++];

        while(i < word1.size())
            final += word1[i++];
        while(i < word2.size())
            final += word2[i++];

        return final;
    }
};

//344. Reverse String
class Solution344 {
public:
    void reverseString(vector<char>& s) {
        int left = 0;
        int right = s.size() - 1;
        while (left < right) {
            swap(s[left++], s[right--]);
        }
    }
};

//88. Merge Sorted Array
class Solution88 {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = 0;
        int j = 0;
        if (n == 0) {
            return;
        }
        if (m == 0) {
            while (i < n)
                nums1[i++] = nums2[j++];
            return;
        }
        while (i < m) {
            if (nums1[i] > nums2[j]) {
                swap(nums1[i], nums2[j]);
                sort(nums2.begin(), nums2.end());
            }
            i++;
        }
        while (i < m + n) {
            nums1[i++] = nums2[j++];
        }
        return;
    }
};

//283. Move Zeroes
class Solution283 {
public:
    void moveZeroes(vector<int>& nums) {
        int left = 0;

        for(int i = 0; i < nums.size(); i++){
            if(nums[i] != 0){
                nums[left++] = nums[i];
            }
        }

        for(left; left < nums.size(); left ++){
            nums[left] = 0;
        }
    }
};

//26. Remove Duplicates from Sorted Array
class Solution26 {
public:
    int removeDuplicates(vector<int>& nums) {
        int left = 0;
        int right = 1;
        while (right < nums.size()) {
            if (nums[right] != nums[left])
                nums[++left] = nums[right];
            right++;
        }
        return left+1;
    }
};

//80. Remove Duplicates from Sorted Array II
class Solution80 {
public:
    int removeDuplicates(vector<int>& nums) {
        int len = nums.size();
        if (len <= 2)
            return len;
        int left = 2;
        int right = 2;
        while (right < nums.size()) {
            if (nums[right] != nums[left-2])
                nums[left++] = nums[right];
            right++;
        }
        return left;
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

//18. 4Sum
class Solution18 {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());

        vector<vector<int> > res;
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            for (int j = i + 1; j < n; j++) {
                if (j > (i + 1) && nums[j] == nums[j - 1])
                    continue;
                int l = j + 1, r = n - 1;
                while (l < r) {
                    long sm = (long)nums[i] + (long)nums[j] + (long)nums[l] + (long)nums[r];
                    if (sm == target) {
                        res.push_back(vector<int>{nums[i], nums[j], nums[l], nums[r]});
                        l += 1;
                        while (l < r && nums[l] == nums[l - 1])
                            l += 1;
                    }
                    else if (sm > target)
                        r -= 1;
                    else
                        l += 1;
                }
            }
        }
        return res;
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

//1498. Number of Subsequences That Satisfy the Given Sum Condition

//189. Rotate Array
class Solution189 {
public:
    void rotate(vector<int>& nums, int k) {
        k %= nums.size();
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
};

//881. Boats to Save People


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
