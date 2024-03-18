//
// Created by Wei on 2/7/24.
//

#ifndef NEETCODE150_BITMANIPULATION_H
#define NEETCODE150_BITMANIPULATION_H

#include "common.h"
//136. Single Number
class Solution136 {
public:
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for (auto n: nums) {
            result ^= n;
        }
        return result;
    }
};

//191. Number of 1 Bits
class Solution191 {
public:
    int hammingWeight(uint32_t n) {
        int result = 0;
        int bit = 0;
        while (n) {
            bit = n & 1;
            if (bit == 1) {
                result++;
            }
            n = n >> 1;
        }
        return result;
    }
};

//338. Counting Bits
class Solution338 {
public:
    vector<int> countBits(int n) {
        if (n==0)
            return vector<int>{0};
        vector<int> dp(n+1);
        dp[0] = 0;
        dp[1] = 1;
        int step = 1;
        for (int i=2; i<=n; i++) {
            if ((i & (i-1)) == 0) {
                step *= 2;
            }
            dp[i] = dp[i-step] + 1;
        }
        return dp;
    }
};

//190. Reverse Bits
class Solution190 {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t result = 0;

        for (int i = 0; i < 32; i++) {
            result <<= 1;
            result |= n & 1;
            n >>= 1;
        }

        return result;
    }
};

//268. Missing Number
class Solution268 {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        return n * (n + 1) / 2 - accumulate(nums.begin(), nums.end(), 0);
    }
};

//1470. Shuffle the Array
class Solution1470 {
public:
    vector<int> shuffle(vector<int>& nums, int n) {

        for(int i = 0; i < 2 * n; i ++){
            int j = i < n ? 2 * i : 2 * (i - n) + 1;
            nums[j] |= (nums[i] & 1023) << 10;
        }
        for(int& e: nums) e >>= 10;
        return nums;
    }
};

//989. Add to Array-Form of Integer
class Solution989 {
public:
    vector<int> addToArrayForm(vector<int>& num, int k) {
        std::vector<int> result;
        int n = num.size();
        int carry = 0;

        for (int i = n - 1; i >= 0 || k > 0 || carry > 0; --i, k /= 10) {
            int digit = (i >= 0 ? num[i] : 0) + (k % 10) + carry;
            carry = digit / 10;
            result.push_back(digit % 10);
        }

        std::reverse(result.begin(), result.end());
        return result;
    }
};

//371. Sum of Two Integers
class Solution371 {
public:
    int getSum(int a, int b) {
        while (b!=0) {
            int carry = a & b;
            a = a ^ b;
            b = static_cast<unsigned int>(carry) << 1;
        }
        return a;
    }
};

//7. Reverse Integer
class Solution7 {
public:
    int reverse(int x) {
        int result = 0;
        while (x) {
            int digit = x % 10;
            x /= 10;
            if (result > INT_MAX / 10 || result == INT_MAX / 10 && digit==7)
                return 0;
            if (result < INT_MIN / 10 || result == INT_MIN / 10 && digit==-8)
                return 0;
            result = result * 10 + digit;
        }
        return result;
    }
};

//67. Add Binary
class Solution67 {
public:
    string addBinary(string a, string b) {
        std::string result;
        int carry = 0;
        int i = a.size() - 1;
        int j = b.size() - 1;

        while (i >= 0 || j >= 0 || carry > 0) {
            int sum = carry;
            if (i >= 0) sum += a[i--] - '0';
            if (j >= 0) sum += b[j--] - '0';
            result += '0' + (sum % 2);
            carry = sum / 2;
        }

        std::reverse(result.begin(), result.end());
        return result;
    }
};

//137. Single Number II
class Solution137 {
public:
    int singleNumber(vector<int>& nums) {
        int ans = 0;

        for (int i=0; i<32; i++) {
            int total = 0;
            for (auto n: nums) {
                total += (n>>i & 1);
            }
            if (total % 3) {
                ans |= 1<<i;
            }
        }
        return ans;
    }
};

//201. Bitwise AND of Numbers Range
class Solution201 {
public:
    int rangeBitwiseAnd(int left, int right) {
        if (left == right)
            return left;

        int ans = right;
        while ((ans & (ans-1)) != 0) {
            ans = ans & (ans-1);
        }
        if (left < ans && right >= ans)
            return 0;

        return ans + rangeBitwiseAnd((left & (ans - 1)), (right & (ans - 1)));
    }
};

//260. Single Number III
class Solution260 {
public:
    vector<int> singleNumber(vector<int>& nums) {
        unordered_set<int> set;

        for (auto n: nums) {
            if (set.count(n)) {
                set.erase(n);
            }
            else {
                set.insert(n);
            }
        }

        vector<int> ret;
        for (auto n:set) {
            ret.push_back(n);
        }
        return ret;
    }
};

//405. Convert a Number to Hexadecimal
class Solution405 {
public:
    string toHex(int num) {
        if (num == 0)
            return "0";
        string res = "";

        int cnt = 8;
        while (cnt != 0) {
            int s = num & 0xf;
            if (s < 10)
                res.push_back('0' + s);
            else
                res.push_back('a' + s - 10);
            num  = num >> 4;
            cnt--;
        }

        reverse(res.begin(), res.end());
        auto it = res.find_first_not_of('0');
        res = res.substr(it, res.length() - it);

        return res;
    }
};

//421. Maximum XOR of Two Numbers in an Array
struct Trie {
    // 左子树指向表示 0 的子节点
    Trie* left = nullptr;
    // 右子树指向表示 1 的子节点
    Trie* right = nullptr;

    Trie() = default;
};

class Solution421 {
private:
    // 字典树的根节点
    Trie* root = new Trie();
    // 最高位的二进制位编号为 30
    static constexpr int HIGH_BIT = 30;

public:
    void add(int num) {
        Trie* cur = root;
        for (int k = HIGH_BIT; k >= 0; --k) {
            int bit = (num >> k) & 1;
            if (bit == 0) {
                if (!cur->left) {
                    cur->left = new Trie();
                }
                cur = cur->left;
            }
            else {
                if (!cur->right) {
                    cur->right = new Trie();
                }
                cur = cur->right;
            }
        }
    }

    int check(int num) {
        Trie* cur = root;
        int x = 0;
        for (int k = HIGH_BIT; k >= 0; --k) {
            int bit = (num >> k) & 1;
            if (bit == 0) {
                // a_i 的第 k 个二进制位为 0，应当往表示 1 的子节点 right 走
                if (cur->right) {
                    cur = cur->right;
                    x = x * 2 + 1;
                }
                else {
                    cur = cur->left;
                    x = x * 2;
                }
            }
            else {
                // a_i 的第 k 个二进制位为 1，应当往表示 0 的子节点 left 走
                if (cur->left) {
                    cur = cur->left;
                    x = x * 2 + 1;
                }
                else {
                    cur = cur->right;
                    x = x * 2;
                }
            }
        }
        return x;
    }

    int findMaximumXOR(vector<int>& nums) {
        int n = nums.size();
        int x = 0;
        for (int i = 1; i < n; ++i) {
            // 将 nums[i-1] 放入字典树，此时 nums[0 .. i-1] 都在字典树中
            add(nums[i - 1]);
            // 将 nums[i] 看作 ai，找出最大的 x 更新答案
            x = max(x, check(nums[i]));
        }
        return x;
    }
};

//1310. XOR Queries of a Subarray
class Solution1310 {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        vector<long long> data;
        long long ans =arr[0];
        data.push_back(ans);
        for (int i=1; i<arr.size(); i++) {
            ans ^= arr[i];
            data.push_back(ans);
        }
        vector<int> res;
        for (int i=0; i<queries.size(); i++) {
            int r = data[queries[i][1]];
            int l;
            if (queries[i][0]!=0) {
                l = data[queries[i][0]-1];
            }
            else {
                l = 0;
            }
            res.push_back(r^l);
        }
        return res;
    }
};

//1707. Maximum XOR With an Element From Array
class Solution1707 {
public:
    class Trie {
    public:
        const int L = 30;

        Trie* children[2] = {};
        int min = INT_MAX;

        void insert(int val) {
            Trie* node = this;
            node->min = std::min(node->min, val);
            for (int i = L - 1; i >= 0; --i) {
                int bit = (val >> i) & 1;
                if (node->children[bit] == nullptr) {
                    node->children[bit] = new Trie();
                }
                node = node->children[bit];
                node->min = std::min(node->min, val);
            }
        }

        int getMaxXorWithLimit(int val, int limit) {
            Trie* node = this;
            if (node->min > limit) {
                return -1;
            }
            int ans = 0;
            for (int i = L - 1; i >= 0; --i) {
                int bit = (val >> i) & 1;
                if (node->children[bit ^ 1] != nullptr && node->children[bit ^ 1]->min <= limit) {
                    ans |= 1 << i;
                    bit ^= 1;
                }
                node = node->children[bit];
            }
            return ans;
        }
    };
    vector<int> maximizeXor(vector<int> &nums, vector<vector<int>> &queries) {
        Trie* t = new Trie();
        for (int val : nums) {
            t->insert(val);
        }
        int numQ = queries.size();
        vector<int> ans(numQ);
        for (int i = 0; i < numQ; ++i) {
            ans[i] = t->getMaxXorWithLimit(queries[i][0], queries[i][1]);
        }
        return ans;
    }
};

//473. Matchsticks to Square
class Solution473_bitmask {
public:
    bool makesquare(vector<int>& matchsticks) {
        int totalLen = accumulate(matchsticks.begin(), matchsticks.end(), 0);
        if (totalLen % 4 != 0) {
            return false;
        }
        int len = totalLen / 4, n = matchsticks.size();
        vector<int> dp(1 << n, -1);
        dp[0] = 0;
        for (int s = 1; s < (1 << n); s++) {
            for (int k = 0; k < n; k++) {
                if ((s & (1 << k)) == 0) {
                    continue;
                }
                int s1 = s & ~(1 << k);
                if (dp[s1] >= 0 && dp[s1] + matchsticks[k] <= len) {
                    dp[s] = (dp[s1] + matchsticks[k]) % len;
                    break;
                }
            }
        }
        return dp[(1 << n) - 1] == 0;
    }
};

#endif //NEETCODE150_BITMANIPULATION_H
