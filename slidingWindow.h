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
        int n = arr.size();
        for(int i=0;i<k;i++){
            sum += arr[i];
        }
        int left = 0;
        int right = k;
        int res = 0;
        if(sum/k >= threshold) res++;
        while(right < n){
            sum -= arr[left++];
            sum += arr[right++];
            if(sum/k >= threshold) res++;
        }
        return res;
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

//1838. Frequency of the Most Frequent Element
class Solution1838 {
public:
    int maxFrequency(vector<int>& nums, long long k) {
        sort(nums.begin(),nums.end());
        int l=0;
        int r=0;
        int res=0;
        long long total=0;
        int n=nums.size();
        while(r<n){
            total += nums[r];

            while(static_cast<long>((r-l+1)*nums[r]) > total+k){
                total -= nums[l];
                l++;
            }

            res=max(res,r-l+1);
            r++;
        }
        return res;
    }
};

//904. Fruit Into Baskets
class Solution904 {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int, int> map;
        typedef unordered_map<int, int> maptype;
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
        if (n < 3) return n;

        int left = 0;
        int right = 0;

        std::unordered_map<char, int> hashmap;

        int max_len = 2;

        while (right < n) {
            if (hashmap.size() < 3) {
                hashmap[s[right]] = right++;
            }

            if (hashmap.size() == 3) {
                auto del_it = std::min_element(hashmap.begin(), hashmap.end(),
                                               [](const auto& a, const auto& b) { return a.second < b.second; });
                hashmap.erase(del_it->first);
                left = del_it->second + 1;
            }

            max_len = max(max_len, right - left);
        }

        return max_len;
    }
};

//220. Contains Duplicate III
class Solution220 {
public:
    long long size;
    bool containsNearbyAlmostDuplicate(vector <int> & nums, int k, int t) {
        unordered_map<int, long long> m;
        size = t + 1L;
        for (int i = 0; i < nums.size(); i++) {
            int idx = getIdx(nums[i]);
            if (m.find(idx) != m.end())
                return true;
            int l = idx - 1, r = idx + 1;
            if (m.find(l) != m.end() && abs(nums[i] - m[l]) <= t)
                return true;
            if (m.find(r) != m.end() && abs(nums[i] - m[r]) <= t)
                return true;
            m[idx] = nums[i];
            if (i >= k)
                m.erase(getIdx(nums[i - k]));
        }
        return false;
    }
    int getIdx(long long u) {
        return u >= 0 ? u / size : ((u + 1) / size) - 1;
    }
};

//340-longest-substring-with-at-most-k-distinct-characters
/*
Given a string, find the length of the longest substring T that contains at most k distinct characters.
Example:
 Given s = “eceba” and k = 2,
T is "ece" which its length is 3.
 */
class Solution340 {
public:
    int lengthOfLongestSubstringKDistinct(std::string s, int k) {
        if (k == 0) return 0;
        std::unordered_map<char, int> map;
        int left = 0, right = 0;
        int max_len = 0, n = s.length();
        while (right < n) {
            map[s[right]] = right;
            if (map.size() > k) {
                int left_most = INT_MAX;
                for (auto& pair : map) {
                    left_most = std::min(left_most, pair.second);
                }
                map.erase(s[left_most]);
                left = left_most + 1;
            }
            right++;
            max_len = std::max(max_len, right - left);
        }
        return max_len;
    }
};

//438. Find All Anagrams in a String
class Solution438 {
public:
    bool checker(unordered_map<char, int>& lfh, unordered_map<char, int>& rfh) {
        for (auto itor: rfh) {
            if (lfh[itor.first] != itor.second)
                return false;
        }
        return true;
    }

    vector<int> findAnagrams(string s, string p) {
        unordered_map<char, int> mapp;
        for (auto c: p) {
            mapp[c]++;
        }
        vector<int> res;

        int left =0;
        int right =0;
        unordered_map<char, int> maps;
        while (right<s.length()) {
            if (mapp.count(s[right])) {
                maps[s[right]]++;
                if (checker(maps, mapp)) {
                    res.push_back(left);
                }
            }
            right++;
            if (right-left>=p.length()) {
                maps[s[left]]--;
                left++;
            }
        }
        return res;
    }
};

//487. Max Consecutive Ones II
/*
 The problem is about finding the longest sequence of consecutive 1s
 in a binary array, under the condition that we are allowed to flip
 at most one 0 to 1. This task tests our ability to manipulate
 subarrays in a binary context and optimize our approach to account
 for small alterations in the array to achieve the desired outcome.
 example:
Input: [1,0,1,1,0]
Output: 4
Explanation:
Flip the first zero will get the the maximum number of consecutive 1s.
 After flipping, the maximum number of consecutive 1s is 4.
 */
class Solution487 {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int ans = 0;
        int zeros = 0;

        for (int l = 0, r = 0; r < nums.size(); ++r) {
            if (nums[r] == 0)
                ++zeros;
            while (zeros == 2)
                if (nums[l++] == 0)
                    --zeros;
            ans = max(ans, r - l + 1);
        }

        return ans;
    }
};

//713. Subarray Product Less Than K
class Solution713 {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k <= 1) return 0;
        int len = nums.size();
        int left = 0;
        int right = 0;
        long long product = 1;
        int ans = 0;
        while (right < len) {
            product *= nums[right];
            right++;
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
 * Question :
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
        int m = S.size(), n = T.size(), start = -1, minLen = INT_MAX, i = 0, j = 0;
        while (i < m) {
            if (S[i] == T[j]) {
                if (++j == n) {
                    int end = i + 1;
                    while (--j >= 0) {
                        while (S[i--] != T[j]);
                    }
                    ++i; ++j;
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
        int n = arr.size();
        int ret = 1;
        int left = 0, right = 0;
        while (right < n - 1) {
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
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return atMostKDistinct(nums, k) - atMostKDistinct(nums, k-1);
    }

    int atMostKDistinct(vector<int>& nums, int k) {
        int len = nums.size();
        int left = 0;
        int right = 0;
        int count = 0;
        unordered_map<int, int> nmap;
        int ans  = 0;
        while (right < len) {
            if (nmap.count(nums[right])==0) {
                count++;
            }
            nmap[nums[right]]++;
            right++;

            while (count>k) {
                nmap[nums[left]]--;
                if (nmap[nums[left]]==0) {
                    count--;
                    nmap.erase(nums[left]);
                }
                left++;
            }
            ans += right - left;
        }
        return ans;
    }
};

//995. Minimum Number of K Consecutive Bit Flips
class Solution995 {
public:
    int minKBitFlips(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0, revCnt = 0;
        for (int i = 0; i < n; ++i) {
            if (i >= k && nums[i - k] > 1) {
                revCnt ^= 1;
                //nums[i - k] -= 2; // 复原数组元素，若允许修改数组 nums，则可以省略
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
                maxlen = max(right-left, maxlen);
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

//1100.Find-K-Length-Substrings-With-No-Repeated-Characters
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
    int numKLenSubstrNoRepeats(std::string S, int K) {
        std::unordered_set<char> cur;
        int res = 0, i = 0;
        for (int j = 0; j < S.length(); j++) {
            while (cur.count(S[j])) {
                cur.erase(S[i++]);
            }
            cur.insert(S[j]);
            if (j - i + 1 >= K) {
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
        const int k = ranges::count(data, 1);
        int ones = 0;     // the number of ones in the window
        int maxOnes = 0;  // the maximum number of ones in the window

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
        while (right<s.length()) {
            cost += abs(s[right]-t[right]);
            while (cost>maxCost) {
                cost -= abs(s[left]- t[left]);
                left++;
            }
            maxlen = max(maxlen, right+1-left);
            right++;
        }
        return maxlen;
    }
};

//1248. Count Number of Nice Subarrays
class Solution1248 {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        unordered_map<int, int> map;
        int cnt=0;
        int oddcnt=0;

        for (int i=0; i<nums.size(); i++) {
            if (nums[i] &1 ==1) {
                oddcnt++;
            }
            map[oddcnt]++;
            if (oddcnt == k) {
                cnt++;
            }
            if (map.count(oddcnt-k)) {
                cnt += map[oddcnt-k];
            }
        }
        return cnt;
    }
};

//1358. Number of Substrings Containing All Three Characters
class Solution1358 {
    int cnt[3];
public:
    int numberOfSubstrings(string s) {
        int len=(int)s.length(),ans=0;
        cnt[0]=cnt[1]=cnt[2]=0;
        for (int l=0,r=-1;l<len;){
            while (r<len && !(cnt[0]>=1 && cnt[1]>=1 && cnt[2]>=1)){
                if (++r==len) break;
                cnt[s[r]-'a']++;
            }
            ans+=len-r;
            cnt[s[l++]-'a']--;
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
        int left = 0;
        int right=0;
        int sum = 0;
        int max_sum = sum;
        unordered_map<int, int> map;
        while (right<nums.size()) {
            if (map.count(nums[right])) {
                max_sum = max(max_sum, sum);
                int index = max(left, map[nums[right]]+1);
                while (left != index) {
                    sum -= nums[left++];
                }
            }
            sum += nums[right];
            map[nums[right]] = right;
            right++;
        }
        return max(max_sum, sum);
    }
};

//1871. Jump Game VII
// unsolved
class Solution1871 {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.length();
        if (s[n - 1] == '1') return false; // If the last character is '1', it's unreachable

        int left = 0, right = 0;

        for (int i = 0; i < n; ++i) {
            if (s[i] == '0') {
                right = i;
                if (right - left + 1 >= minJump) {
                    if (right == n - 1) return true; // Reached the end
                    left = right - maxJump + 1; // Shrink the window from the left side
                }
            }
        }

        return false;
    }
};

//1984. Minimum Difference Between Highest and Lowest of K Scores
// solution in twopoints.h


#endif //NEETCODE150_SLIDINGWINDOW_H
