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
        int count = 0;
        while (n) {
            if (n & 1 == 1) {
                count++;
            }
            n = n >> 1;
        }
        return count;
    }
};

class Solution191_kernighan {
public:
    int hammingWeight(uint32_t n) {
        unsigned int count = 0;

        while(n) {
            ++count;
            // unset rightmost set bit
            n = (n & (n - 1));
        }

        return count;
    }
};

//338. Counting Bits
class Solution338_dp {
public:
    vector<int> countBits(int n) {
        if (n==0)
            return vector<int>{0};
        vector<int> dp(n+1);
        dp[0] = 0;
        dp[1] = 1;
        int step = 1;
        for (int i=2; i<=n; i++) {
            //the binary representation of i is 1,10,100,1000...
            if ((i & (i-1)) == 0) {
                step *= 2;
            }
            dp[i] = dp[i-step] + 1;
        }
        return dp;
    }
};

class Solution338 {
public:
    vector<int> countBits(int n) {
        vector<int> result(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            //                 i / 2      i % 2
            result[i] = result[i >> 1] + (i & 1);
        }

        return result;
    }
};

//190. Reverse Bits
class Solution190 {
public:
    uint32_t reverseBits(uint32_t n) {
        int result = 0;
        int bit = 31;
        while (n) {
            //copy the last bit of n the first bit of the result if it is not zero.
            result += (n & 1) << bit;
            //iterate the last bit of n.
            n = n >> 1;
            bit--;
        }
        return result;
    }
};

//268. Missing Number
class Solution268 {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int result = n;
        for (int i = 0; i < n; i++) {
            result ^= i ^ nums[i];
        }
        return result;
    }
};

//1470. Shuffle the Array
class Solution1470 {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        for(int i = 0; i < 2 * n; i++){
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

        for (int i = n - 1; i >= 0 || k > 0 || carry > 0; --i) {
            int digit = (i >= 0 ? num[i] : 0) + (k % 10) + carry;
            carry = digit / 10;
            k /= 10;
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
            if (i >= 0)
                sum += a[i--] - '0';
            if (j >= 0)
                sum += b[j--] - '0';
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
        int result = 0;
        int shift = 0;  // Count the number of right shifts needed

        while (left != right) {
            left >>= 1;
            right >>= 1;
            shift++;
        }

        // Common prefix between left and right
        result = left << shift;

        return result;
    }
};

//260. Single Number III
class Solution260 {
    vector<int> singleNumber(vector<int> &nums) {
        // Step 1: Calculate the XOR of all elements
        int xorResult = 0;
        for (int num: nums) {
            xorResult ^= num;
        }

        // Step 2: Find the rightmost set bit
        int rightmostSetBit = xorResult & -xorResult;

        // Step 3: Partition the array and calculate XOR of each group
        int group1Xor = 0, group2Xor = 0;
        for (int num: nums) {
            if (num & rightmostSetBit) {
                group1Xor ^= num;
            } else {
                group2Xor ^= num;
            }
        }

        return {group1Xor, group2Xor};
    }
};

class Solution260_set {
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
        if (num == 0) return "0";

        string hexChars = "0123456789abcdef";
        string hexRepresentation = "";

        unsigned int uNum;
        if (num < 0) {
            // Convert negative number to its two's complement representation
            uNum = UINT_MAX + 1 + num;
        } else {
            uNum = num;
        }

        while (uNum != 0) {
            hexRepresentation = hexChars[uNum & 0xf] + hexRepresentation;
            uNum >>= 4;
        }

        return hexRepresentation;
    }
};

//421. Maximum XOR of Two Numbers in an Array
class Solution421 {
public:
    int findMaximumXOR(vector<int>& nums) {
        int maxXOR = 0, mask = 0;

        // Iterate through each bit position from the most significant bit to the least significant bit
        for (int i = 31; i >= 0; --i) {
            mask |= (1 << i); // Set the bit in the mask

            unordered_set<int> prefixes;
            for (int num : nums) {
                prefixes.insert(num & mask); // Store the prefixes up to the current bit position
            }

            int candidateXOR = maxXOR | (1 << i); // Try setting the current bit to 1

            for (int prefix : prefixes) {
                if (prefixes.count(candidateXOR ^ prefix)) { // Check if the complement exists
                    maxXOR = candidateXOR; // Update maxXOR if valid XOR result found
                    break;
                }
            }
        }

        return maxXOR;
    }
};

//1310. XOR Queries of a Subarray
class Solution1310 {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        int n = arr.size();

        // Step 1: Preprocess array to compute prefix XOR values
        vector<int> prefixXOR(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixXOR[i + 1] = prefixXOR[i] ^ arr[i];
        }

        // Step 2: Process queries
        vector<int> answer;
        for (const auto& query : queries) {
            int left = query[0], right = query[1];
            answer.push_back(prefixXOR[right + 1] ^ prefixXOR[left]);
        }

        return answer;
    }
};

//1707. Maximum XOR With an Element From Array
class Solution1707 {
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        sort(nums.begin(), nums.end());

        int n = nums.size();
        vector<vector<int>> dp(32, vector<int>(n, 0));

        // Fill dp array
        for (int i = 0; i < 32; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j == 0 || (nums[j] & (1 << i)) != (nums[j - 1] & (1 << i))) {
                    dp[i][j] = j;
                } else {
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }

        vector<int> result;
        for (auto& query : queries) {
            int x = query[0];
            int m = query[1];
            int s = 0, e = n - 1;
            int max_xor = 0;

            if (nums[0] > m) {
                result.push_back(-1);
                continue;
            }

            for (int i = 31; i >= 0; --i) {
                if ((nums[s] & (1 << i)) == (nums[e] & (1 << i))) {
                    max_xor += nums[s] & (1 << i);
                } else if (nums[dp[i][e]] <= m && (x ^ nums[s]) < (x ^ nums[e])) {
                    max_xor += nums[e] & (1 << i);
                    s = dp[i][e];
                } else {
                    max_xor += nums[s] & (1 << i);
                    e = dp[i][e] - 1;
                }
            }

            result.push_back(max_xor ^ x);
        }

        return result;
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
