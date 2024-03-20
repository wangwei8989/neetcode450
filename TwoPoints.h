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
        string ans="";

        while(i < word1.size() && i < word2.size())
            ans = ans + word1[i] + word2[i++];

        while(i < word1.size())
            ans += word1[i++];
        while(i < word2.size())
            ans += word2[i++];

        return ans;
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
            if (nums1[i] > nums2[0]) {
                swap(nums1[i], nums2[0]);
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

        for(left; left < nums.size(); left++){
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
            if (nums[left-2] != nums[right])
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
                    long sm = static_cast<long>(nums[i]) + nums[j] + nums[l] + nums[r];
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
class Solution1498 {
public:
    int numSubseq(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();

        int left = 0;
        int right = n - 1;
        int res = 0;
        int mod = 1e9 + 7;
        while (left <= right) {
            if (nums[left] + nums[right] > target) {
                right--;
            }
            else {
                res = (res + fastPower(2, right - left, mod)) % mod;
                left++;
            }
        }
        return res;
    }

    int fastPower(int a, int b, int mod) {
        long long ans = 1;
        long long base = a;
        while (b != 0) {
            if (b % 2 == 1) {
                ans = (ans * base) % mod;
            }
            base = (base * base) % mod;
            b /= 2;
        }
        return ans;
    }
};

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

//1968. Array With Elements Not Equal to Average of Neighbors
class Solution1968 {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        sort(nums.begin(), nums.end()); // Sort the array

        int n = nums.size();
        int left = 0, right = n - 1;

        vector<int> result(n);
        int i = 0;

        while (left <= right) {
            // Pick element from the beginning of the sorted array
            result[i++] = nums[left++];

            // Pick element from the end of the sorted array
            if (i < n) {
                result[i++] = nums[right--];
            }
        }

        return result;
    }
};

//881. Boats to Save People
class Solution881 {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());

        int boatRequired = 0;
        int lightestPerson = 0;
        int heaviestPerson = people.size()-1;

        while (lightestPerson <= heaviestPerson){
            if(people[lightestPerson] + people[heaviestPerson] <= limit){
                --heaviestPerson;
                ++lightestPerson;
            }
            else{
                --heaviestPerson;
            }
            ++boatRequired;
        }

        return boatRequired;
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

//28. Find the Index of the First Occurrence in a String
class Solution28 {
public:
    int strStr(string haystack, string needle) {
        if (haystack.size() < needle.size())
            return -1;
        if (needle.size() == 0)
            return 0;
        int i = 0;
        int j = 0;
        while (haystack[i]!=needle[0] && haystack[i]!='\0')
            i++;
        while (haystack[i]!='\0' && needle[j]!='\0') {
            if (haystack[i] == needle[j]) {
                i++;
                j++;
            }
            else {
                i = i - j + 1;
                j = 0;
            }
        }
        if (j == needle.size())
            return i - j;
        else
            return -1;
    }
};

//75. Sort Colors
class Solution75 {
public:
    void sortColors(vector<int>& nums) {
        int len = nums.size();
        if (len<2)
            return;
        int left = 0;
        int right = len-1;

        int i=0;
        while (i<=right) {
            if (nums[i]==0) {
                swap(nums[left], nums[i]);
                left++;
                i++;
            }
            else if (nums[i]==1) {
                i++;
            }
            else {
                swap(nums[right], nums[i]);
                right--;
            }
        }
    }
};

//82. Remove Duplicates from Sorted List II
class Solution82 {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode* dummy = new ListNode;
        dummy->next = head;

        ListNode* cur = dummy;
        while (cur->next && cur->next->next) {
            if (cur->next->val == cur->next->next->val) {
                int x = cur->next->val;
                while (cur->next && x == cur->next->val) {
                    cur->next = cur->next->next;
                }
            }
            else {
                cur = cur->next;
            }
        }
        return dummy->next;
    }
};

//151. Reverse Words in a String
class Solution151 {
public:
    string reverseWords(string s) {
        // Trim leading and trailing spaces
        s.erase(0, s.find_first_not_of(' '));
        s.erase(s.find_last_not_of(' ') + 1);

        // Split the string into words
        vector<string> words;
        istringstream iss(s);
        string word;
        while (iss >> word) {
            words.push_back(word);
        }

        // Reverse the order of the words
        reverse(words.begin(), words.end());

        // Join the words back together into a single string
        string result;
        for (const string& w : words) {
            if (!result.empty()) {
                result += ' ';
            }
            result += w;
        }

        return result;
    }
};

//170. Two Sum III - Data structure design
/*Design and implement a TwoSum class. It should support the following operations: add and find.
add - Add the number to an internal data structure.
find - Find if there exists any pair of numbers which sum is equal to the value.

Example 1:
add(1); add(3); add(5);
find(4) -> true
find(7) -> false

 Example 2:
add(3); add(1); add(2);
find(3) -> true
find(6) -> false
 */
class TwoSum {
public:
    void add(int number) {
        ++count[number];
    }

    bool find(int value) {
        for (const auto& [key, freq] : count) {
            const int remain = value - key;
            if (key == remain && freq > 1)
                return true;
            if (key != remain && count.count(remain))
                return true;
        }

        return false;
    }

private:
    unordered_map<int, int> count;
};

//795. Number of Subarrays with Bounded Maximum
class Solution795 {
public:
    int help(vector<int>& nums, int k) {
        int left = 0;
        int right = 0;
        int ans = 0;
        while (right<nums.size()) {
            if (nums[right]>k) {
                left = right + 1;
            }
            ans += right - left;
            right++;
        }
        return ans;
    }
    int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
        return help(nums, right) - help(nums, left-1);
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
        int res = 0;
        int i = 0;

        while (i < target.length()) {
            int oriI = i;
            for (char c : source) {
                if (i < target.length() && c == target[i]) {
                    i++;
                }
            }
            if (i == oriI) {
                return -1;
            }
            res++;
        }
        return res;
    }
};

//1147. Longest Chunked Palindrome Decomposition
class Solution1147 {
public:
    int longestDecomposition(string word) {
        string::iterator left = word.begin();
        string::iterator right = word.end() -1;
        int count = 0;

        while (left<right && !word.empty()) {
            if (string(word.begin(), left+1) == string(right, word.end())) {
                count++;
                word = string(left+1, right);
                left = word.begin();
                right = word.end()-1;
            }
            else {
                left++;
                right--;
            }
        }
        return word.empty() ? count * 2 : count * 2 +1;
    }
};

//557. Reverse Words in a String III
class Solution557 {
public:
    string reverseWords(string s) {
        int left = 0;
        int right = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ' ') {
                right = i;
                reverse(s.begin() + left, s.begin() + right);
                left = right + 1;
            }
            if (i==s.size() - 1) {
                right = i + 1;
                reverse(s.begin() + left, s.begin() + right);
            }
        }
        return s;
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

#endif //NEETCODE150_TWOPOINTS_H
