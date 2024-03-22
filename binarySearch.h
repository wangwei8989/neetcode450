//
// Created by Wei on 2/7/24.
//

#ifndef NEETCODE150_BINARYSEARCH_H
#define NEETCODE150_BINARYSEARCH_H

#include "common.h"

//704. Binary Search
class Solution704 {
public:
    int search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] < target) {
                low = mid + 1;
            } else if (nums[mid] > target) {
                high = mid - 1;
            } else {
                return mid;
            }
        }

        return -1;
    }
};

//35. Search Insert Position
class Solution35 {
public:
    int searchInsert(vector<int>& nums, int target) {
        int ans = nums.size();
        int left = 0;
        int right = nums.size() - 1;
        int mid = 0;

        while(left <= right) {
            mid = ((right - left) >> 1) + left;
            if (target <= nums[mid]) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }
};

//374. Guess Number Higher or Lower
class Solution374 {
    int guess(int num);
public:
    int guessNumber(int n) {
        long long left=1,right=n;
        while(left<=right)
        {
            long long mid=(left+right)/2;
            int res=guess(mid);
            if(res==0)
                return mid;
            else if(res==-1)
                right=mid-1;
            else
                left=mid+1;
        }
        return -1;
    }
};

//69. Sqrt(x)
class Solution69 {
public:
    int mySqrt(int x) {
        int left = 0;
        int right = x;
        long long mid = 0;

        while (left<=right) {
            mid = left + ((right - left) / 2);
            //int tmp = mid * mid;
            if (mid * mid == x || (mid * mid < x && (mid+1)*(mid+1)>x))
                return mid;
            else if (mid * mid < x)
                left = mid+1;
            else
                right = mid - 1;
        }
        return -1;
    }
};

//162. Find Peak Element
class Solution162 {
public:
    int findPeakElement(vector<int>& nums) {
        if (nums.size()==1)
            return 0;
        int left = 0;
        int right = nums.size();

        while (left < right) {
            int mid = left + ((right-left)/2);
            if (((mid+1<right && nums[mid]>nums[mid+1]) || mid+1>=right) &&
                ((mid-1>=left && nums[mid]>nums[mid-1]) || mid-1<left)) {
                return mid;
            } else if (nums[mid] >= nums[mid-1]) {
                left = mid+1;
            } else {
                right = mid;
            }
        }
        return -1;
    }
};

//74. search a 2d matrix
class Solution74 {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int lowRow = 0;
        int highRow = matrix.size() - 1;
        int lowCol = 0;
        int highCol = matrix[0].size() - 1;
        while (lowRow < highRow) {
            int mid = lowRow + (highRow - lowRow) / 2;
            if (matrix[mid][0] == target)
                return true;
            else if (matrix[mid][0] < target && matrix[mid+1][0] > target) {
                lowRow = mid;
                break;
            }
            if ( matrix[mid][0] > target) {
                highRow = mid - 1;
            }
            else {
                lowRow = mid + 1;
            }
        }
        while (lowCol <= highCol) {
            int mid = lowCol + (highCol - lowCol) / 2;
            if (matrix[lowRow][mid] == target) {
                return true;
            }
            else if (matrix[lowRow][mid] < target) {
                lowCol = mid + 1;
            }
            else {
                highCol = mid -1;
            }
        }
        return false;
    }
};

//875. Koko Eating Bananas
class Solution875 {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int low = 1;
        int high = *max_element(piles.begin(), piles.end());
        int ans = high;
        while (low <= high) {
            int k = low + (high - low) / 2;
            long hours = 0;
            for (const auto& p: piles) {
                hours += ceil(static_cast<double>(p) / k);
            }
            if (hours <= h) {
                ans = min(ans, k);
                high = k -1;
            }
            else {
                low = k + 1;
            }
        }
        return ans;
    }
};

//153. Find Minimum in Rotated Sorted Array
class Solution153 {
public:
    int findMin(vector<int> &nums)
    {
        // Neetcode solution Ologn time O1 space binary search
        int res = nums[0];
        int l = 0;
        int r = nums.size() - 1;

        while (l <= r)
        {
            if (nums[l] < nums[r])
            {
                res = min(res, nums[l]);
                break;
            }
            int mid = l + (r - l) / 2;
            res = min(res, nums[mid]);

            if (nums[mid] >= nums[l]) // mid present in left sorted array
            {
                l = mid + 1; // try to move closer to right sorted array
            }
            else
            {
                r = mid - 1;
            }
        }

        return res;
    }
};

//33. Search in Rotated Sorted Array
class Solution33 {
public:
    int search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] == target) {
                return mid;
            }
            if (nums[low] <= nums[mid]) {
                if (nums[low] <= target && target <= nums[mid]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else {
                if (nums[mid] <= target && target <= nums[high]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }

        return -1;
    }
};

//981. Time Based Key-Value Store
class TimeMap {
public:
    TimeMap() {

    }

    void set(string key, string value, int timestamp) {
        m[key].push_back({timestamp, value});
    }

    string get(string key, int timestamp) {
        if (m.find(key) == m.end()) {
            return "";
        }

        int low = 0;
        int high = m[key].size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (m[key][mid].first < timestamp) {
                low = mid + 1;
            } else if (m[key][mid].first > timestamp) {
                high = mid - 1;
            } else {
                return m[key][mid].second;
            }
        }

        if (high >= 0) {
            return m[key][high].second;
        }
        return "";
    }
private:
    unordered_map<string, vector<pair<int, string>>> m;
};

//4. Median of Two Sorted Arrays
class Solution4 {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();

        if (m > n) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int total = m + n;

        int low = 0;
        int high = m;

        double result = 0.0;

        while (low <= high) {
            // nums1
            int i = low + (high - low) / 2;
            // nums2
            int j = (total + 1) / 2 - i;

            int left1 = (i > 0) ? nums1[i - 1] : INT_MIN;
            int right1 = (i < m) ? nums1[i] : INT_MAX;
            int left2 = (j > 0) ? nums2[j - 1] : INT_MIN;
            int right2 = (j < n) ? nums2[j] : INT_MAX;

            // partition is correct
            if (left1 <= right2 && left2 <= right1) {
                // even
                if (total % 2 == 0) {
                    result = (max(left1, left2) + min(right1, right2)) / 2.0;
                    // odd
                } else {
                    result = max(left1, left2);
                }
                break;
            } else if (left1 > right2) {
                high = i - 1;
            } else {
                low = i + 1;
            }
        }

        return result;
    }
};

//34. Find First and Last Position of Element in Sorted Array
class Solution {
public:
    int binarySearch(vector<int>& nums, int target, bool lower) {
        int left = 0, right = (int)nums.size() - 1, ans = (int)nums.size();
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[mid] > target || (lower && nums[mid] >= target)) {
                right = mid - 1;
                ans = mid;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        int leftIdx = binarySearch(nums, target, true);
        int rightIdx = binarySearch(nums, target, false) - 1;
        if (leftIdx <= rightIdx && rightIdx < nums.size() && nums[leftIdx] == target && nums[rightIdx] == target) {
            return vector<int>{leftIdx, rightIdx};
        }
        return vector<int>{-1, -1};
    }
};

//95. Unique Binary Search Trees II
class Solution95 {
public:
    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*> result;
        if (n == 0)
            return result;
        else {
            return helper(1,n);
        }
    }

private:
    vector<TreeNode*> helper(int start, int end) {
        vector<TreeNode*> ans;
        if (start>end) {
            ans.push_back(nullptr);
            return ans;
        }
        for (int i=start; i<=end; i++) {
            vector<TreeNode*> left = helper(start, i-1);
            vector<TreeNode*> right = helper(i+1, end);

            for (auto l: left) {
                for (auto r: right) {
                    TreeNode* root = new TreeNode(i);
                    root->left = l;
                    root->right = r;
                    ans.push_back(root);
                }
            }
        }
        return ans;
    }
};

//96. Unique Binary Search Trees
class Solution96 {
public:
    int numTrees(int n) {
        vector<int> G(n + 1, 0);
        G[0] = 1;
        G[1] = 1;

        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j <= i; ++j) {
                G[i] += G[j - 1] * G[i - j];
            }
        }
        return G[n];
    }
};

//98. Validate Binary Search Tree
class Solution98 {
    bool dfs(TreeNode* root, long left = LONG_MIN, long right = LONG_MAX) {
        if (root == nullptr)
            return true;
        if (root->val > left && root->val < right) {
            return dfs(root->left, left, root->val) &&
                   dfs(root->right, root->val, right);
        }
        return false;
    }
public:
    bool isValidBST(TreeNode* root) {
        return dfs(root);
    }
};

//108. Convert Sorted Array to Binary Search Tree
class Solution108 {
public:
    TreeNode* sortedArrayToBST(const vector<int>& nums) {
        if (nums.empty()) {
            return nullptr;
        }

        return Helper(nums, 0, nums.size() - 1);
    }

private:
    TreeNode* Helper(const vector<int>& nums, int left, int right) {
        if (left > right) {
            return nullptr;
        }

        // Choose the middle element as the root
        int mid = left + (right - left) / 2;
        TreeNode* root = new TreeNode(nums[mid]);

        // Recursively construct left and right subtrees
        root->left = Helper(nums, left, mid - 1);
        root->right = Helper(nums, mid + 1, right);

        return root;
    }
};

//173. Binary Search Tree Iterator
class BSTIterator {
public:
    queue<int> q;
    int Traversal(TreeNode* root) {
        if(nullptr == root) {
            return 0;
        }
        stack<TreeNode*> s;
        TreeNode* step = root;
        while(nullptr != step || !s.empty()) {
            while(nullptr != step) {
                s.push(step);
                step = step->left;
            }
            if(!s.empty()) {
                TreeNode* temp = s.top();
                s.pop();
                q.push(temp->val);
                step = temp->right;
            }
        }
        return 0;
    }
    BSTIterator(TreeNode* root) {
        Traversal(root);
    }

    /** @return the next smallest number */
    int next() {
        int res = q.front();
        q.pop();
        return res;
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !q.empty();
    }
};

//235. Lowest Common Ancestor of a Binary Search Tree
class Solution235 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (p->val < root->val && q->val < root->val)
            return lowestCommonAncestor(root->left, p, q);
        else if (p->val > root->val && q->val > root->val)
            return lowestCommonAncestor(root->right, p, q);
        else
            return root;
    }
};

//701. Insert into a Binary Search Tree
class Solution701 {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(nullptr == root) {
            root = new TreeNode(val);
            return root;
        }
        if(val == root->val) {
            return nullptr;
        }else if(val < root->val) {
            if(nullptr == root->left) {
                root->left = new TreeNode(val);
            } else {
                insertIntoBST(root->left, val);
            }
        }else {
            if(nullptr == root->right) {
                root->right = new TreeNode(val);
            } else {
                insertIntoBST(root->right, val);
            }
        }
        return root;
    }
};

//703. Kth Largest Element in a Stream
class KthLargest_binarySearch {
public:
    KthLargest_binarySearch(int k, vector<int>& nums) {
        this->k = k;
        for (auto& num: nums) {
            pq.push(num);
        }
        while (pq.size() > this->k) {
            pq.pop();
        }
    }

    int add(int val) {
        pq.push(val);
        if (pq.size() > k) {
            pq.pop();
        }
        return pq.top();
    }

private:
    priority_queue<int, vector<int>, greater<int>> pq;
    int k;
};

//1008. Construct Binary Search Tree from Preorder Traversal
class Solution1008 {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        return dfs(preorder, 0, preorder.size() - 1);
    }

private:
    TreeNode* dfs(const vector<int>& preorder, int start, int end) {
        if (start > end) {
            return nullptr;
        }
        TreeNode* root = new TreeNode(preorder[start]);
        // Find the index of the first element greater than the root value
        int i;
        for (i = start + 1; i <= end; ++i) {
            if (preorder[i] > root->val) {
                break;
            }
        }
        // Recursively build the left and right subtrees
        root->left = dfs(preorder, start + 1, i - 1);
        root->right = dfs(preorder, i, end);
        return root;
    }
};
#endif //NEETCODE150_BINARYSEARCH_H
