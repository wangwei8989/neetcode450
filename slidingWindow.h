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

//1343. Number of Sub-arrays of Size K and Average Greater than or Equal to Threshold
class Solution1343 {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int sum = 0;
        for(int i = 0; i < k;i++){
            sum += arr[i];
        }

        int res = 0;
        threshold *= k;
        if(sum >= threshold)
            res++;

        int left = 0;
        int right = k;
        int n = arr.size();
        while(right < n){
            sum -= arr[left++];
            sum += arr[right++];
            if(sum >= threshold)
                res++;
        }

        return res;
    }
};

//424. Longest Repeating Character Replacement
class Solution424 {
public:
    int characterReplacement(string s, int k) {
        int maxLength = 0;
        int maxCount = 0;
        unordered_map<char, int> freqMap;
        int left = 0;
        for (int right = 0; right < s.size(); ++right) {
            freqMap[s[right]]++;
            maxCount = max(maxCount, freqMap[s[right]]);
            if (right - left + 1 - maxCount > k) {
                freqMap[s[left]]--;
                left++;
            }
            maxLength = max(maxLength, right - left + 1);
        }

        return maxLength;
    }
};

//567. Permutation in String
class Solution567 {
public:
    bool checkInclusion(string s1, string s2) {
        int n1 = s1.length();
        int n2 = s2.length();
        if (n1 > n2)
            return false;

        vector<int> freq1(26, 0);
        vector<int> freq2(26, 0);
        for (char c : s1) {
            freq1[c - 'a']++;
        }
        for (int i = 0; i < n1; i++) {
            freq2[s2[i] - 'a']++;
        }
        for (int i = 0; i <= n2 - n1; i++) {
            if (freq1 == freq2) {
                return true;
            }
            freq2[s2[i] - 'a']--;
            if (i + n1 < n2) {
                freq2[s2[i + n1] - 'a']++;
            }
        }

        return false;
    }
};

//1838. Frequency of the Most Frequent Element
class Solution1838 {
public:
    int maxFrequency(vector<int>& nums, long long k) {
        sort(nums.begin(),nums.end());
        int left = 0;
        int right = 0;
        int res = 0;
        long long total = 0;
        int n = nums.size();
        while (right < n){
            total += nums[right];
            while (static_cast<long>((right-left+1)*nums[right]) > total + k){
                total -= nums[left];
                left++;
            }
            res = max(res, right-left+1);
            right++;
        }

        return res;
    }
};

//904. Fruit Into Baskets
class Solution904 {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int, int> map;
        int left = 0;
        int right = 0;
        int ans = 0;
        while (right < fruits.size()) {
            map[fruits[right]]++;
            while (map.size() > 2) {
                map[fruits[left]]--;
                if (map[fruits[left]] == 0) {
                    map.erase(fruits[left]);
                }
                left++;
            }
            right++;
            ans = max(ans, right - left);
        }

        return ans;
    }
};

//1456. Maximum Number of Vowels in a Substring of Given Length
class Solution1456 {
public:
    int maxVowels(string s, int k) {
        int cnt = 0;
        int left = 0;
        int right = 0;
        int max_cnt = 0;
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};

        while (right<s.length()) {
            if(vowels.count(s[right])) {
                cnt++;
            }
            if (right>=k && vowels.count(s[right-k])) {
                cnt--;
            }
            max_cnt = max(max_cnt, cnt);
            right++;
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
        unordered_map<char, int> targetMap;
        for (auto c: t) {
            targetMap[c]++;
        }
        int left = 0;
        int right = 0;
        int minStart = 0;
        int minLength = INT_MAX;
        int counter = t.length();
        while (right < s.length()) {
            if (targetMap[s[right]] > 0) {
                counter--;
            }
            targetMap[s[right]]--;
            right++;
            while (counter == 0) {
                if (minLength > right - left) {
                    minLength = right - left;
                    minStart = left;
                }
                targetMap[s[left]]++;
                if (targetMap[s[left]] > 0) {
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

//159. Longest Substring with At Most Two Distinct Characters
/*
Given a string s, return the length of the longest substring that contains at most two distinct characters.

 Example 1:
Input: s = "eceba"
Output: 3
Explanation: The substring is "ece" which its length is 3.

 Example 2:
Input: s = "ccaabbb"
Output: 5
Explanation: The substring is "aabbb" which its length is 5.

Constraints:
1 <= s.length <= 105
s consists of English letters.
 */
class Solution159 {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        int n = s.length();
        if (n < 3)
            return n;

        int left = 0;
        int right = 0;
        unordered_map<char, int> freqMap;
        int max_len = 2;
        int distinctCount = 0;

        while (right < n) {
            freqMap[s[right]]++;
            if (freqMap[s[right]] == 1)
                distinctCount++;

            while (distinctCount > 2) {
                freqMap[s[left]]--;
                if (freqMap[s[left]] == 0)
                    distinctCount--;
                left++;
            }
            max_len = max(max_len, ++right - left);
        }

        return max_len;
    }
};

//220. Contains Duplicate III
class Solution220 {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        set<long long> window;
        int left = 0;
        int right = 0;
        while (right < nums.size()) {
            if (right - left > indexDiff)
                window.erase(nums[left++]);
            //find x in window as abs(x-nums[right]) <= valueDiff
            auto it = window.lower_bound(static_cast<long long>(nums[right]) - valueDiff);
            if (it != window.end() && *it <= static_cast<long long>(nums[right]) + valueDiff)
                return true;
            window.insert(nums[right]);
        }

        return false;
    }
};

//438. Find All Anagrams in a String
class Solution438 {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> result;
        if (s.empty() || p.empty() || s.size() < p.size())
            return result;

        unordered_map<char, int> pFreq;
        for (char c : p) {
            pFreq[c]++;
        }

        int left = 0, right = 0;
        int count = p.size();

        while (right < s.size()) {
            // Expand the window
            if (pFreq[s[right++]]-- >= 1)
                count--;

            // Check if the window size matches with p
            if (count == 0)
                result.push_back(left);

            // Shrink the window
            if (right - left == p.size() && pFreq[s[left++]]++ >= 0)
                count++;
        }

        return result;
    }
};

//487. Max Consecutive Ones II
/*
 The problem is about finding the longest sequence of consecutive 1s in a binary array,
 under the condition that we are allowed to flip at most one 0 to 1. This task tests
 our ability to manipulate subarrays in a binary context and optimize our approach to
 account for small alterations in the array to achieve the desired outcome.

 example:
Input: [1,0,1,1,0]
Output: 4
Explanation:
Flip the first zero will get the the maximum number of consecutive 1s.
 After flipping, the maximum number of consecutive 1s is 4.
 */
class Solution487 {
public:
    int longestOnes(vector<int>& nums) {
        int left = 0;
        int right = 0;
        int zeroCount = 0;
        int maxLength = 0;

        while (right < nums.size()) {
            if (nums[right] == 0) {
                zeroCount++;
            }

            while (zeroCount > 1) {
                if (nums[left] == 0) {
                    zeroCount--;
                }
                left++;
            }

            maxLength = max(maxLength, right - left + 1);
            right++;
        }

        return maxLength;
    }
};

//713. Subarray Product Less Than K
class Solution713 {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k <= 1)
            return 0;
        int left = 0;
        int right = 0;
        long long product = 1;
        int ans = 0;
        while (right < nums.size()) {
            product *= nums[right++];
            while(product>=k) {
                product /= nums[left];
                left++;
            }
            ans += right - left;
        }

        return ans;
    }
};

//727. Minimum window subsequence
/*
Given strings S and T, find the minimum (contiguous) substring W of S, so that T is a subsequence of W.
If there is no such window in S that covers all characters in T, return the empty string "". If there are multiple such minimum-length windows, return the one with the left-most starting index.

Example :
Input:
S = "abcdebdde", T = "bde"
Output: "bcde"
Explanation:
There are many substrings with "bde" but the smallest amongst them is "bcde" and "bdde" of length 4. Out of these 2, "bcde" occurs first, Hence it is the answer.
 */
class Solution727 {
public:
    string minWindow(string S, string T) {
        int  start = -1;
        int minLen = INT_MAX;
        int i = 0;
        int j = 0;
        while (i < S.size()) {
            if (S[i] == T[j]) {
                if (++j == T.size()) {
                    int end = i + 1;
                    while (--j >= 0) {
                        while (S[i--] != T[j]);
                    }
                    ++i;
                    ++j;
                    if (end - i < minLen) {
                        minLen = end - i;
                        start = i;
                    }
                }
            }
            ++i;
        }
        return (start != -1) ? S.substr(start, minLen) : "";
    }
};

//978. Longest Turbulent Subarray
class Solution978 {
public:
    int maxTurbulenceSize(vector<int>& arr) {
        int ret = 1;
        int left = 0;
        int right = 0;
        while (right < arr.size() - 1) {
            if (left == right) {
                if (arr[left] == arr[left + 1]) {
                    left++;
                }
                right++;
            } else {
                if (arr[right - 1] < arr[right] && arr[right] > arr[right + 1]) {
                    right++;
                } else if (arr[right - 1] > arr[right] && arr[right] < arr[right + 1]) {
                    right++;
                } else {
                    left = right;
                }
            }
            ret = max(ret, right - left + 1);
        }
        return ret;
    }
};

//992. Subarrays with K Different Integers
class Solution992 {
public:
    int countGoodSubarrays(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        int left = 0;
        int right = 0;
        int uniqueCount = 0;
        int goodSubarrays = 0;

        while (right < nums.size()) {
            // Expand the window
            if (freq[nums[right]] == 0) {
                uniqueCount++;
            }
            freq[nums[right]]++;

            // Shrink the window until we have exactly k unique elements
            while (uniqueCount > k) {
                freq[nums[left]]--;
                if (freq[nums[left]] == 0) {
                    uniqueCount--;
                }
                left++;
            }

            // Count the subarrays
            if (uniqueCount == k) {
                goodSubarrays += (right - left + 1);
            }

            right++;
        }

        return goodSubarrays;
    }
};

//995. Minimum Number of K Consecutive Bit Flips
class Solution995 {
public:
    int minKBitFlips(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;
        int revCnt = 0;
        for (int i = 0; i < n; ++i) {
            if (i >= k && nums[i - k] > 1) {
                revCnt ^= 1;
            }
            if (nums[i] == revCnt) {
                if (i + k > n) {
                    return -1;
                }
                ++ans;
                revCnt ^= 1;
                nums[i] += 2;
            }
        }
        return ans;
    }
};

//1004. Max Consecutive Ones III
class Solution1004 {
public:
    int longestOnes(vector<int>& A, int K) {
        int left = 0;
        int right = 0;
        int cnt = 0;
        int maxlen = 0;
        while (right<A.size()) {
            if (A[right] == 0) {
                cnt++;
            }
            if (cnt>K) {
                if (A[left]==0)
                    cnt--;
                left++;
            }
            right++;
            maxlen = max(right-left, maxlen);
        }
        return maxlen;
    }
};

//1052. Grumpy Bookstore Owner
class Solution1052 {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int len = customers.size();
        int sum = 0;
        for (int i=0; i<len; i++) {
            sum += customers[i] * (1-grumpy[i]);
        }

        for (int i=0; i<minutes; i++) {
            sum += customers[i] * grumpy[i];
        }
        int max_sum = sum;

        for (int i=minutes; i<len; i++) {
            sum += customers[i] * grumpy[i];
            sum -= customers[i-minutes] * (grumpy[i-minutes]);
            max_sum = max(max_sum, sum);
        }

        return max_sum;
    }
};

//1100.Find K Length Substrings With No Repeated Characters
/*Given a string S, return the number of substrings of length K with no repeated characters.

Example 1:
Input: S = "havefunonleetcode", K = 5
Output: 6
Explanation:
There are 6 substrings they are : 'havef','avefu','vefun','efuno','etcod','tcode'.

Example 2:
Input: S = "home", K = 5
Output: 0
Explanation:
Notice K can be larger than the length of S. In this case is not possible to find any substring.

Note:
1 <= S.length <= 10^4
All characters of S are lowercase English letters.
1 <= K <= 10^4
 */
class Solution1100 {
public:
    int numKLenSubstrNoRepeats(string S, int K) {
        unordered_set<char> cur;
        int res = 0;
        int left = 0;
        int right = 0;
        while (right < S.length()) {
            while (cur.count(S[right])) {
                cur.erase(S[left++]);
            }
            cur.insert(S[right++]);
            if (right - left >= K) {
                res += 1;
            }
        }

        return res;
    }
};

//1151. Minimum Swaps to Group All 1's Together
/*Given a binary array data, return the minimum number of swaps required to group all 1’s present in the array together in any place in the array.

Example 1:
Input: [1,0,1,0,1]
Output: 1
Explanation:
There are 3 ways to group all 1's together:
[1,1,1,0,0] using 1 swap.
[0,1,1,1,0] using 2 swaps.
[0,0,1,1,1] using 1 swap.
The minimum is 1.

Example 2:
Input: [0,0,0,1,0]
Output: 0
Explanation:
Since there is only one 1 in the array, no swaps needed.

Example 3:
Input: [1,0,1,0,1,0,0,1,1,0,1]
Output: 3
Explanation:
One possible solution that uses 3 swaps is [0,0,0,0,0,1,1,1,1,1,1].

Note:
1 <= data.length <= 10^5
0 <= data[i] <= 1
 */
class Solution1151 {
public:
    int minSwaps(vector<int>& data) {
        const int k = count(data.begin(), data.end(), 1);
        int ones = 0;
        int maxOnes = 0;

        for (int i = 0; i < data.size(); ++i) {
            if (i >= k && data[i - k])
                --ones;
            if (data[i])
                ++ones;
            maxOnes = max(maxOnes, ones);
        }

        return k - maxOnes;
    }
};

//1176.Diet Plan Performance
/*
 A dieter consumes calories[i] calories on the i-th day. For every consecutive sequence of k days, they look at T, the total calories consumed during that sequence of k days:
If T < lower, they performed poorly on their diet and lose 1 point; If T > upper, they performed well on their diet and gain 1 point; Otherwise, they performed normally and there is no change in points. Return the total number of points the dieter has after all calories.length days.

Note : The total points could be negative.

Example 1:
Input: calories = [1,2,3,4,5], k = 1, lower = 3, upper = 3
Output: 0
Explaination: calories[0], calories[1] < lower and calories[3], calories[4] > upper, total points = 0.

 Example 2:
Input: calories = [3,2], k = 2, lower = 0, upper = 1
Output: 1
Explaination: calories[0] + calories[1] > upper, total points = 1.

 Example 3:
Input: calories = [6,5,0,0], k = 2, lower = 1, upper = 5
Output: 0
Explaination: calories[0] + calories[1] > upper, lower <= calories[1] + calories[2] <= upper, calories[2] + calories[3] < lower, total points = 0.

Constraints:
1 <= k <= calories.length <= 10^5
0 <= calories[i] <= 20000
0 <= lower <= upper
 */
class Solution1176 {
public:
    int dietPlanPerformance(vector<int>& calories, int k, int lower, int upper) {
        int startSum=0;
        int points=0;
        for( int i=0;i<k;i++)
            startSum += calories[i];
        if(startSum>upper)
            ++points;
        else if(startSum < lower)
            --points;
        for(int i=k; i<calories.size();i++)
        {
            startSum = startSum - calories[i-k]+calories[i];
            if(startSum>upper)
                ++points;
            else if(startSum < lower)
                --points;

        }
        return points;
    }
};

//1208. Get Equal Substrings Within Budget
class Solution1208 {
public:
    int equalSubstring(string s, string t, int maxCost) {
        int cost= 0;
        int left = 0;
        int right = 0;
        int maxlen  = 0;
        while (right < s.length()) {
            cost += abs(s[right] - t[right]);
            while (cost > maxCost) {
                cost -= abs(s[left]- t[left]);
                left++;
            }
            maxlen = max(maxlen, right + 1 - left);
            right++;
        }
        return maxlen;
    }
};

//1248. Count Number of Nice Subarrays
class Solution1248 {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int left = 0;
        int right = 0;
        int oddCount = 0;
        int n = nums.size();
        int result = 0;
        while (right < n) {
            if (nums[right] % 2 == 1) {
                oddCount++;
            }
            while (oddCount > k) {
                if (nums[left] % 2 == 1) {
                    oddCount--;
                }
                left++;
            }
            if (oddCount == k) {
                int leftEvenCount = 1;
                while (left < right && nums[left] % 2 == 0) {
                    leftEvenCount++;
                    left++;
                }
                int rightEvenCount = 1;
                while (right + 1 < n && nums[right + 1] % 2 == 0) {
                    rightEvenCount++;
                    right++;
                }
                result += leftEvenCount * rightEvenCount;
            }
            right++;
        }

        return result;
    }
};

//1358. Number of Substrings Containing All Three Characters
class Solution1358 {
    int cnt[3];
public:
    int numberOfSubstrings(string s) {
        int n = s.length();
        unordered_map<char, int> freq;
        int ans = 0;
        int left = 0;
        int right = 0;
        while (right < n) {
            freq[s[right]]++;
            while (freq['a'] && freq['b'] && freq['c']) {
                ans += n - right;
                freq[s[left]]--;
                left++;
            }
            right++;
        }

        return ans;
    }
};

//1423. Maximum Points You Can Obtain from Cards
class Solution1423 {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int len = cardPoints.size();
        int sum = accumulate(cardPoints.end() - k, cardPoints.end(), 0);
        int max_sum = sum;

        for (int i= len; i<len +k; i++) {
            sum += cardPoints[i%len];
            sum -= cardPoints[i-k];
            max_sum = max(max_sum, sum);
        }
        return max_sum;
    }
};

//1493. Longest Subarray of 1's After Deleting One Element
class Solution1493 {
public:
    int longestSubarray(vector<int>& nums) {
        int left =0;
        int right = 0;
        int zpos = 0;
        int max_len = 0;
        while (right<nums.size()) {
            if (nums[right]==0) {
                if(nums[zpos]==0 && right>zpos) {
                    max_len = max(max_len, right -1 - left);
                    left = zpos + 1;
                }
                zpos = right;
            }
            right++;
        }
        return max(max_len, right -1 - left);
    }
};

//1695. Maximum Erasure Value
class Solution1695 {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        unordered_map<int, int> freq;
        int score = 0;
        int maxScore = 0;
        int left = 0;
        int right = 0;
        while (right < nums.size()) {
            freq[nums[right]]++;
            score += nums[right];

            while (freq[nums[right]] > 1) {
                freq[nums[left]]--;
                score -= nums[left];
                left++;
            }
            maxScore = max(maxScore, score);
            right++;
        }

        return maxScore;
    }
};

//1871. Jump Game VII
class Solution1871 {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.length();
        if (s[n - 1] == '1')
            return false;

        deque<int> reachableIndexes;
        reachableIndexes.push_back(0);
        int right = 1;
        while (right < n) {
            if (s[right] == '0') {
                // Remove indices from the front of the deque if they are out of the valid range
                while (!reachableIndexes.empty() && reachableIndexes.front() < right - maxJump)
                    reachableIndexes.pop_front();

                // Check if there's a reachable index within the valid range
                for (auto& left : reachableIndexes) {
                    if (left + minJump <= right && left + maxJump >= right) {
                        if (right == n - 1)
                            return true;
                        reachableIndexes.push_back(right);
                        break; // Break to avoid pushing the same index multiple times
                    }
                }
            }
            right++;
        }

        return false;
    }
};

//1984. Minimum Difference Between Highest and Lowest of K Scores
// solution in twopoints.h


#endif //NEETCODE150_SLIDINGWINDOW_H
