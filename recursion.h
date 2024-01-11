//
// Created by Wei on 1/3/24.
//

#ifndef NEETCODE150_RECURSION_H
#define NEETCODE150_RECURSION_H

#include "common.h"

//50. Pow(x, n)
class Solution50 {
public:
    double powBase(double x, int n) {
        if (n == 0)
            return 1.0;
        double y = powBase(x, n/2);
        return n&1 ? y * y * x : y * y;
    }
    double myPow(double x, int n) {
        return n < 0 ? 1.0 / powBase(x, n) : powBase(x, n);
    }
};

//08.05. Recursive Mulitply LCCI
class Solution0805 {
public:
    int multiply(int A, int B) {
        if (B>A)
            return multiply(B, A);
        if (B == 0)
            return 0;
        int result = multiply(A, B >> 1) << 1;
        if (B&1)
            result += A;
        return result;
    }
};

//912. Sort an Array
class Solution912_mergesort {
public:
    vector<int> sortArray(vector<int>& nums) {
        mergeSort(nums, 0, nums.size()-1);
        return nums;
    }

private:
    void merge(vector<int>& nums, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<int> leftArr(nums.begin() + left, nums.begin() + left + n1);
        vector<int> rightArr(nums.begin() + mid + 1, nums.begin() + mid + 1 + n2);

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (leftArr[i] <= rightArr[j]) {
                nums[k++] = leftArr[i++];
            } else {
                nums[k++] = rightArr[j++];
            }
        }

        while (i < n1) nums[k++] = leftArr[i++];
        while (j < n2) nums[k++] = rightArr[j++];
    }

    void mergeSort(vector<int>& nums, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(nums, left, mid);
            mergeSort(nums, mid + 1, right);
            merge(nums, left, mid, right);
        }
    }
};

class Solution912_quicksort {
public:
    vector<int> sortArray(vector<int>& nums) {
        srand(unsigned(time(NULL)));
        quickSort(nums, 0, nums.size()-1);
        return nums;
    }

private:
    void quickSort(vector<int>& nums, int l, int r) {
        if (l >= r)
            return;
        int pos = partition(nums, l, r);
        quickSort(nums, l, pos-1);
        quickSort(nums, pos+1, r);
    }

    int partition(vector<int>& nums, int start, int end) {
        int i = rand() % (end - start + 1) + start;
        swap(nums[start], nums[i]);
        int pivot = nums[start];
        int left = start + 1;
        int right = end;
        while(left < right) {
            while (left < right && nums[left] < pivot)
                left++;
            while (left < right && nums[right] > pivot)
                right--;
            if (left < right)
                swap(nums[left++], nums[right--]);
        }
        if (left == right && nums[right] > pivot) {
            right--;
        }
        swap(nums[right], nums[start]);
        return right;
    }
};

// 215. The kth largest element in the array
class Solution215 {
public:
    int findKthLargest(vector<int>& nums, int k) {
        srand(unsigned(time(NULL)));
        return quickSelect(nums, 0, nums.size(), k);
    }

private:
    int partition(vector<int>& nums, int left, int right) {
        int pos = rand() % (right - left + 1) + left;
        swap(nums[right], nums[pos]);
        int pivot = nums[right];
        int i = left - 1;
        for (int j = left; j < right; j++) {
            if (nums[j] > pivot) {
                i++;
                swap(nums[i], nums[j]);
            }
        }
        swap(nums[i+1], nums[right]);
        return i+1;
    }
    int quickSelect(vector<int>& nums, int left, int right, int k) {
        if (left < right) {
            int pos = partition(nums, left, right);
            if (pos == k - 1)
                return nums[pos];
            else if (pos < k - 1) {
                return quickSelect(nums, pos+1, right, k);
            }
            else {
                return quickSelect(nums, left, pos-1, k);
            }
        }
        return -1;
    }
};

//315. Count of Smaller Numbers After Self
class Solution315 {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> counts(nums.size(), 0);
        vector<int> indices(nums.size(), 0);

        for (int i = 0; i < nums.size(); ++i) {
            indices[i] = i;
        }

        mergeSort(nums, indices, counts, 0, nums.size() - 1);

        return counts;
    }

private:
    void mergeSort(const vector<int>& nums, vector<int>& indices, vector<int>& counts, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            mergeSort(nums, indices, counts, left, mid);
            mergeSort(nums, indices, counts, mid + 1, right);

            merge(nums, indices, counts, left, mid, right);
        }
    }

    void merge(const vector<int>& nums, vector<int>& indices, vector<int>& counts, int left, int mid, int right) {
        vector<int> temp(right - left + 1);
        int i = left;
        int j = mid + 1;
        int k = 0;
        int rightCount = 0;

        while (i <= mid && j <= right) {
            if (nums[indices[i]] > nums[indices[j]]) {
                // Element in the right half is smaller, update counts
                rightCount++;
                temp[k++] = indices[j++];
            } else {
                // Element in the left half is smaller or equal
                counts[indices[i]] += rightCount;
                temp[k++] = indices[i++];
            }
        }

        // Process remaining elements in the left half
        while (i <= mid) {
            counts[indices[i]] += rightCount;
            temp[k++] = indices[i++];
        }

        // Process remaining elements in the right half
        while (j <= right) {
            temp[k++] = indices[j++];
        }

        // Copy the merged indices back to the original array
        for (int idx = 0; idx < temp.size(); ++idx) {
            indices[left + idx] = temp[idx];
        }
    }
};

//493. Reverse Pairs
class Solution493 {
public:
    int reversePairs(vector<int>& nums) {
        return mergeSort(nums, 0, nums.size() - 1);
    }

private:
    int mergeSort(vector<int>& nums, int left, int right) {
        if (left >= right) {
            return 0;
        }

        int mid = left + (right - left) / 2;

        int count = mergeSort(nums, left, mid) + mergeSort(nums, mid + 1, right);

        // Count the reverse pairs during the merging step
        int j = mid + 1;
        for (int i = left; i <= mid; ++i) {
            while (j <= right && nums[i] > 2LL * nums[j]) {
                ++j;
            }
            count += (j - (mid + 1));
        }

        // Merge the two sorted halves
        merge(nums, left, mid, right);

        return count;
    }

    void merge(vector<int>& nums, int left, int mid, int right) {
        vector<int> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;

        while (i <= mid && j <= right) {
            if (nums[i] <= nums[j]) {
                temp[k++] = nums[i++];
            } else {
                temp[k++] = nums[j++];
            }
        }

        while (i <= mid) {
            temp[k++] = nums[i++];
        }

        while (j <= right) {
            temp[k++] = nums[j++];
        }

        for (int idx = 0; idx < temp.size(); ++idx) {
            nums[left + idx] = temp[idx];
        }
    }
};

//53. Maximum Subarray
class Solution53 {
public:
    int maxSubArray(const vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        return Helper(nums, 0, nums.size() - 1);
    }

private:
    int Helper(const vector<int>& nums, int left, int right) {
        if (left == right) {
            return nums[left];
        }

        int mid = left + (right - left) / 2;

        // Find the maximum subarray sum in the left and right halves
        int leftMax = Helper(nums, left, mid);
        int rightMax = Helper(nums, mid + 1, right);

        // Find the maximum subarray sum crossing the midpoint
        int crossMax = maxCrossingSum(nums, left, mid, right);

        // Return the maximum among the three possibilities
        return max(max(leftMax, rightMax), crossMax);
    }

    int maxCrossingSum(const vector<int>& nums, int left, int mid, int right) {
        int leftSum = INT_MIN;
        int sum = 0;

        // Find the maximum sum of the left subarray
        for (int i = mid; i >= left; --i) {
            sum += nums[i];
            leftSum = max(leftSum, sum);
        }

        int rightSum = INT_MIN;
        sum = 0;

        // Find the maximum sum of the right subarray
        for (int i = mid + 1; i <= right; ++i) {
            sum += nums[i];
            rightSum = max(rightSum, sum);
        }

        // Return the sum of the maximum subarray crossing the midpoint
        return leftSum + rightSum;
    }
};

//21. Merge Two Sorted Lists
class Solution21 {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr )
            return list2;
        if (list2 == nullptr)
            return list1;
        if (list1->val < list2->val) {
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        }
        else {
            list2->next = mergeTwoLists(list1, list2->next);
            return list2;
        }
    }
};

//206. Reverse Linked List
class Solution206 {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode* next = head->next;
        auto result = reverseList(next);
        next->next = head;
        head->next = nullptr;
        return result;
    }
};

//203. Remove Linked List Elements
class Solution203 {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if (head == nullptr)
            return head;
        head->next = removeElements(head->next, val);
        if (head->val == val) {
            auto next = head->next;
            delete head;
            return next;
        }
        else {
            return head;
        }
    }
};

//24. Swap Nodes in Pairs
class Solution24 {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        auto next = head->next;
        head->next = swapPairs(next->next);
        next->next = head;
        return next;
    }
};

//143. Reorder List
class Solution143 {
public:
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return;

        auto fast = head;
        auto slow = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
        }
        auto secondHalf = reverseList(slow->next);
        slow->next = nullptr;

        merge(head, secondHalf);
    }

private:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode* prev = nullptr;
        auto curr = head;
        while (curr != nullptr) {
            auto next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }

    void merge(ListNode* first, ListNode* second) {
        if (second == nullptr)
            return;
        auto firstNext = first->next;
        merge(first->next, second->next);
        first->next = second;
        second->next = firstNext;
    }
};

//92. Reverse Linked List II
class Solution92 {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (head == nullptr || head->next == nullptr)
            return head;
        right -= left;
        auto curr = head;
        ListNode* prev = nullptr;
        while(--left && curr != nullptr) {
            prev = curr;
            curr = curr->next;
        }
        auto leftNode = prev;

        while (right-- >= 0 && curr != nullptr) {
            auto next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        if (leftNode != nullptr) {
            leftNode->next->next = curr;
            leftNode->next = prev;
        }
        else {
            head->next = curr;
            head = prev;
        }
        return head;
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

//124. Binary Tree Maximum Path Sum
class Solution124 {
public:
    int maxPathSum(TreeNode* root) {
        Helper(root);
        return ans;
    }

private:
    int ans = INT_MIN;
    int Helper(TreeNode* root){
        if(root == nullptr) {
            return 0;
        }
        int left = max(Helper(root->left), 0);
        int right = max(Helper(root->right), 0);
        ans = max(ans,left + right + root->val);
        // Return the maximum path sum that can be extended to the parent node
        return max(left,right) + root->val;
    }
};

//10. Regular Expression Matching
class Solution10_recursion {
public:
    bool isMatch(const string& s, const string& p) {
        memo.assign(s.length()+1, vector<int>(p.length()+1, -1));
        return Helper(s, p, 0, 0);
    }

private:
    vector<vector<int>> memo;
    bool Helper(const string& s, const string& p, int i, int j) {
        if (memo[i][j] != -1)
            return memo[i][j];

        if (p.length() == j) {
            return s.length() == i;
        }

        bool currentMatch = i < s.length() && (s[i] == p[j] || p[j] == '.');

        if (j+1 < p.length() && p[j+1] == '*') {
            return memo[i][j] = Helper(s, p, i, j+2) || (currentMatch && Helper(s, p, i+1, j));
        }
        else {
            return memo[i][j] = currentMatch && Helper(s, p, i+1, j+1);
        }
    }
};

//38. Count and Say
class Solution38 {
public:
    string countAndSay(int n) {
        if (n == 1)
            return "1";
        string subResult = countAndSay(n-1);
        string result;
        char prev = '0';
        int count = 0;
        for (auto c: subResult) {
            if (c == prev) {
                count++;
            }
            else {
                if (prev != '0') {
                    result.push_back('0' + count);
                    result.push_back(prev);
                }
                prev = c;
                count = 1;
            }
        }
        result.push_back('0' + count);
        result.push_back(prev);
        return result;
    }
};


/*The recursive implementation of the following problems is in dfs.h
105. Construct Binary Tree from Preorder and Inorder Traversal

106. Construct Binary Tree from Inorder and Postorder Traversal

98. Validate Binary Search Tree

104. Maximum Depth of Binary Tree

110. Balanced Binary Tree

199. Binary Tree Right Side View
 */

#endif //NEETCODE150_RECURSION_H
