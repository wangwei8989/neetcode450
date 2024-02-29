//
// Created by Wei on 2/1/24.
//

#ifndef NEETCODE150_SLIDINGWINDOW_H
#define NEETCODE150_SLIDINGWINDOW_H

#include "common.h"
//121. Best Time to Buy and Sell Stock
class Solution121 {
public:
    int maxProfit(vector<int>& prices) {
        int min_price = prices.front();
        int ans = 0;
        for (int i=1; i<prices.size(); i++) {
            min_price = min(min_price, prices[i]);
            ans = max(ans, prices[i]-min_price);
        }
        return ans;
    }
};

//219. Contains Duplicate II
class Solution219 {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> set;
        for (int i = 0; i< nums.size(); i++) {
            if (set.count(nums[i])!=0) {
                return true;
            }

            set.insert(nums[i]);
            if (set.size()>k)
                set.erase(nums[i-k]);
        }
        return false;
    }
};

//3. Longest Substring Without Repeating Characters
class Solution3 {
public:
    int lengthOfLongestSubstring(string& s) {
        unordered_set<char> chars;
        int maxSize = 0;
        int i = 0, j = 0;
        while (j < s.size()){
            while (chars.find(s[j]) != chars.end()){
                chars.erase(s[i]);
                ++i;
            }
            maxSize = max(maxSize, j - i + 1);
            chars.insert(s[j]);
            ++j;
        }
        return maxSize;
    }
};

//424. Longest Repeating Character Replacement
class Solution424 {
public:
    int characterReplacement(string s, int k) {
        vector<int> count(26);
        int maxCount = 0;

        int i = 0;
        int j = 0;

        int result = 0;

        while (j < s.size()) {
            count[s[j] - 'A']++;
            maxCount = max(maxCount, count[s[j] - 'A']);
            if (j - i + 1 - maxCount > k) {
                count[s[i] - 'A']--;
                i++;
            }
            result = max(result, j - i + 1);
            j++;
        }

        return result;
    }
};

//567. Permutation in String
class Solution567 {
public:
    bool checkInclusion(string s1, string s2) {
        int m = s1.size();
        int n = s2.size();
        if (m > n) {
            return false;
        }

        vector<int> count(26);
        for (int i = 0; i < m; i++) {
            count[s1[i] - 'a']++;
            count[s2[i] - 'a']--;
        }
        if (isPermutation(count)) {
            return true;
        }

        for (int i = m; i < n; i++) {
            count[s2[i] - 'a']--;
            count[s2[i - m] - 'a']++;
            if (isPermutation(count)) {
                return true;
            }
        }

        return false;
    }
private:
    bool isPermutation(vector<int>& count) {
        for (int i = 0; i < 26; i++) {
            if (count[i] != 0) {
                return false;
            }
        }
        return true;
    }
};

//904. Fruit Into Baskets
class Solution904 {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int, int> map;
        typedef std::unordered_map<int, int> maptype;
        int left = 0;
        int right = 0;
        int ans = 0;
        while (right<fruits.size()) {
            map[fruits[right]] = right;
            if(map.size()>2) {
                ans = max(ans, right-left);
                auto it = min_element(map.begin(), map.end(),
                                      [](maptype::const_reference p, maptype::const_reference q){
                                          return p.second < q.second;
                                      });

                left = max(left, it->second+1);
                map.erase(it->first);
            }
            right++;
        }
        return max(ans, right-left);
    }
};

//1456. Maximum Number of Vowels in a Substring of Given Length
class Solution1456 {
public:
    bool isvowel(char ch) {
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
            return true;
        return false;
    }

    int maxVowels(string s, int k) {
        int cnt = 0;
        int left = 0;
        int max_cnt = cnt;

        for (int right=0; right<s.length(); right++) {
            if(isvowel(s[right])) {
                cnt++;
            }
            if (right>=k && isvowel(s[right-k])) {
                cnt--;
            }
            max_cnt = max(max_cnt, cnt);
        }
        return max_cnt;
    }
};

//209. Minimum Size Subarray Sum
class Solution209 {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0;
        int right = 0;
        int min_len = INT_MAX;
        int sum = 0;
        while ( right<nums.size()) {
            sum += nums[right];
            while (sum>=target) {
                min_len = min(min_len, right-left);
                sum -= nums[left++];
            }
            right++;
        }
        return min_len == INT_MAX ? 0:min_len+1;
    }
};

//76. Minimum Window Substring
class Solution76 {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> m;
        for (auto c: t) {
            m[c]++;
        }
        int left = 0;
        int right = 0;
        int minStart = 0;
        int minLength = INT_MAX;
        int counter = t.length();
        while (right < s.length()) {
            if (m[s[right]] > 0) {
                counter--;
            }
            m[s[right]]--;
            right++;
            while (counter == 0) {
                if (minLength > right - left) {
                    minLength = right - left;
                    minStart = left;
                }
                m[s[left]]++;
                if (m[s[left]] > 0) {
                    counter++;
                }
                left++;
            }
        }
        if (minLength != INT_MAX) {
            return s.substr(minStart, minLength);
        }
        return "";
    }
};

//1658. Minimum Operations to Reduce X to Zero
class Solution1658 {
public:
    int minOperations(vector<int>& nums, int x) {
        int left = 0;
        int right = 0;
        int sum = 0;
        int max_len = INT_MIN;
        int all = accumulate(nums.begin(), nums.end(), 0);
        while (right <= nums.size() && left<nums.size()) {
            if (sum == all - x) {
                max_len = max(max_len, right-left);
            }
            if (sum>=all-x && left<right) {
                sum -= nums[left++];
                continue;
            }

            sum += nums[right++];
        }
        return max_len==INT_MIN ? -1: nums.size() - max_len;
    }
};

//239. Sliding Window Maximum
class Solution239 {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;
        int left = 0;
        int right = 0;
        vector<int> ans;
        while (right < nums.size()) {
            while (!dq.empty() && nums[dq.back()] < nums[right]) {
                dq.pop_back();
            }
            dq.push_back(right);
            if (left > dq.front()) {
                dq.pop_front();
            }
            if (right + 1 >= k) {
                ans.push_back(nums[dq.front()]);
                left++;
            }
            right++;
        }
        return ans;
    }
};
#endif //NEETCODE150_SLIDINGWINDOW_H
