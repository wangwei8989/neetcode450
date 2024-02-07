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
#endif //NEETCODE150_BITMANIPULATION_H
