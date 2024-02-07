#include "interval.h"
#include "dfs.h"
#include "recursion.h"
#include "greedy.h"
#include "common.h"

//*************************************** Stack **************************************************//
//Largest Rectangle in Histogram
int largestRectangleArea(vector<int>& heights) {
    int maxArea = 0;
    stack<pair<int, int>> stk;
    for (int i=0; i<heights.size(); i++) {
        int start = i;
        while (!stk.empty() && stk.top().second > heights[i]) {
            int height = stk.top().second;
            int width = i - stk.top().first;
            maxArea = max(maxArea, height * width);
            start = stk.top().first;
            stk.pop();
        }
        stk.push({start, heights[i]});
    }
    while (!stk.empty()) {
        int width = heights.size() - stk.top().first;
        int height = stk.top().second;
        maxArea = max(maxArea, width * height);
        stk.pop();
    }
    return maxArea;
}

//*************************************** Binary Search **************************************************//
//Binary Search
int search(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
            return mid;
        else if (nums[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

//Search a 2D Matrix
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int lowRow = 0;
    int highRow = matrix.size() - 1;
    int lowCol = 0;
    int highCol = matrix[0].size() - 1;
    while (lowRow < highRow) {
        int mid = lowRow + (highRow - lowRow) / 2;
        if (matrix[mid][0] == target)
            return true;
        else if (matrix[mid][0] > target && matrix[mid+1][0] < target) {
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

//Coco Eating bannans
int minEatingSpeed(vector<int>& piles, int h) {
    int low = 1;
    int high = *max_element(piles.begin(), piles.end());
    int ans = high;
    while (low <= high) {
        int k = low + (high - low) / 2;
        long hours = 0;
        for (const auto& pile: piles) {
            hours += ceil(static_cast<double>(pile) / k);
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

//Find Minimum in Rotated Sorted Array
int findMin(vector<int>& nums) {
    int ans = nums[0];
    int left = 0;
    int right = nums.size() - 1;
    while (left < right) {
        if (nums[left] < nums[right]) {
            ans = min(ans, nums[left]);
            break;
        }
        int mid = left + (right - left) / 2;
        ans = min(ans, nums[mid]);
        if (nums[left] <= nums[mid])
            left = mid + 1;
        else
            right = mid - 1;
    }
    return ans;
}

//33. Search in Rotated Sorted Array
int search2(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target)
            return mid;
        if (nums[left] <= nums[mid]) {
            if (nums[left] <= target && target < nums[mid]) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        else {
            if (nums[mid] < target && target <= nums[right]) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
    }
    return -1;
}

//981. Time Based Key-Value Store
class TimeMap {
public:
    TimeMap() {

    }

    void set(string key, string value, int timestamp) {
        m[key].push_back({timestamp, value});
    }

    string get(string key, int timestamp) {
        if (m.find(key) == m.end())
            return "";
        int low = 0;
        int high = m[key].size() - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (m[key][mid].first < timestamp) {
                low = mid + 1;
            }
            else if (m[key][mid].first > timestamp) {
                high = mid - 1;
            }
            else {
                return m[key][mid].second;
            }
        }
        if (high >= 0)
            return m[key][high].second;
        return "";
    }

private:
    unordered_map<string, vector<pair<int, string>>> m;
};

//4. Median of Two Sorted Arrays
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size();
    int n = nums2.size();
    int len = m + n;
    int mstep = 0;
    int nstep = 0;
    int i = 0;
    int left = 0;
    int right = 0;
    while (i++ <= len / 2) {
        left = right;
        if (mstep < m && (nums1[mstep] < nums2[nstep] || nstep >= n)) {
            right = nums1[mstep++];
        }
        else {
            right = nums2[nstep++];
        }
        //i++;
    }
    if (len % 2 == 1)
        return right;
    else
        return (left + right) / 2;
}

//*************************************** Linked List **************************************************//

//206. Reverse Linked List
ListNode* reverseList(ListNode* head) {
    if (head == nullptr || head->next == nullptr)
        return head;
    ListNode* prev = nullptr;
    ListNode* curr = head;
    while (curr != nullptr) {
        ListNode* temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    return prev;
}

//21. Merge Two Sorted Lists
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    if (list1 == nullptr && list2 == nullptr)
        return nullptr;
    if (list1 == nullptr)
        return list2;
    if (list2 == nullptr)
        return list1;
    ListNode* head = new ListNode();
    ListNode* curr = head;
    while (list1 != nullptr && list2 != nullptr) {
        if (list1->val <= list2->val) {
            curr->next = list1;
            list1 = list1->next;
        }
        else {
            curr->next = list2;
            list2 = list2->next;
        }
        curr = curr->next;
    }
    if (list1 != nullptr)
        curr->next = list1;
    if (list2->next != nullptr)
        curr->next = list2;
    return head;
}

//143. Reorder List
void reorderList(ListNode* head) {
    vector<ListNode*> vec;
    ListNode* itor = head;
    while (itor != nullptr) {
        vec.push_back(itor);
        itor = itor->next;
    }
    int left = 0;
    int right = vec.size() - 1;
    while (left < right) {
        vec[left]->next = vec[right];
        left++;
        if (left == right)
            break;
        vec[right]->next = vec[left];
        right--;
    }
    vec[left]->next = nullptr;
}

//19. Remove Nth Node From End of List
ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (head == nullptr)
        return nullptr;
    ListNode* fast = head;
    ListNode* slow = head;
    while (n-->0 && fast != nullptr) {
        fast = fast->next;
    }
    if (fast == nullptr) {
        return head->next;
    }
    while (fast->next != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }
    slow->next = slow->next->next;
    return head;
}

//138. Copy List with Random Pointer
class solution138 {
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

Node* copyRandomList(Node* head) {
    unordered_map<Node*, Node*> nodeMap;
    Node* h = head;
    while (h != nullptr) {
        nodeMap[h] = new Node(h->val);
        h = h->next;
    }
    h = head;
    while (h != nullptr) {
        nodeMap[h]->next = nodeMap[h->next];
        nodeMap[h]->random = nodeMap[h->random];
        h = h->next;
    }
    return nodeMap[head];
}
};

//2. Add Two Numbers
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int sum = 0;
    int carry = 0;
    ListNode* l = new ListNode;
    ListNode* node = l;
    while (l1 != nullptr || l2 != nullptr || carry != 0) {
        sum = (l1 == nullptr ? 0 : l1->val) +
              (l2 == nullptr ? 0 :l2->val) +
              carry;
        carry = sum / 10;
        node->next = new ListNode(sum % 10);
        node = node->next;
        if (l1 != nullptr)
            l1 = l1->next;
        if (l2 != nullptr)
            l2 = l2->next;
    }
    return l->next;
}

//141. Linked List Cycle
bool hasCycle(ListNode *head) {
    if (head == nullptr)
        return false;
    ListNode* fast = head;
    ListNode* slow = head;
    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow)
            return true;
    }
    return false;
}

//287. Find the Duplicate Number
int findDuplicate(vector<int>& nums) {
    unordered_set<int> unique;
    for (auto &n: nums) {
        if (unique.count(n))
            return n;
        else
            unique.emplace(n);
    }
    return -1;
}

//146. LRU Cache
class LRUCache {
public:
    LRUCache(int capacity):cap(capacity) {}

    int get(int key) {
        if (itorMap.find(key) == itorMap.end())
            return -1;
        auto itor = itorMap[key];
        Node node(itor->key, itor->value);
        cacheList.erase(itor);
        cacheList.push_front(node);
        itorMap[key] = cacheList.begin();
        return node.value;
    }

    void put(int key, int value) {
        if (itorMap.find(key) != itorMap.end()) {
            auto itor = itorMap[key];
            cacheList.erase(itor);
        }
        else {
           if (cacheList.size() == cap) {
               itorMap.erase(cacheList.back().key);
               cacheList.pop_back();
           }
        }
        Node node(key, value);
        cacheList.push_front(node);
        itorMap[key] = cacheList.begin();
    }

private:
    struct Node {
        int key;
        int value;
        Node(int k, int v):key(k), value(v) {}
    };
    list<Node> cacheList;
    unordered_map<int, list<Node>::iterator> itorMap;
    int cap;
};

//23. Merge k Sorted Lists
ListNode* mergeKLists(vector<ListNode*>& lists) {
    map<int, int> valCnt;
    ListNode* node;
    for (auto &list: lists) {
        node = list;
        while (node != nullptr) {
            valCnt[node->val]++;
            node = node->next;
        }
    }
    ListNode* pre = new ListNode;
    node = pre;
    for (auto &[value, count]: valCnt) {
        while(count--) {
            ListNode* newNode = new ListNode(value);
            node->next = newNode;
            node = node->next;
        }
    }
    return pre->next;
}

//25. Reverse Nodes in k-Group
ListNode* reverseList(ListNode* head, ListNode* tail) {
    ListNode* prev = nullptr;
    ListNode* cur = head;
    ListNode* next = nullptr;
    while (cur!= tail) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}

ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode* ret = nullptr;
    ListNode* fast = head;
    ListNode* slow = head;
    ListNode* prev = new ListNode;
    while (fast != nullptr) {
        int count = k;
        while (count-- && fast != nullptr) {
            fast = fast->next;
        }
        if (fast== nullptr && count!=-1) {
            prev->next = slow;
            break;
        }
        prev->next = reverseList(slow, fast);
        if (ret == nullptr)
            ret = prev->next;
        prev = slow;
        slow = fast;
    }
    return ret;
}

//*************************************** Linked List **************************************************//
//Definition for a binary tree node.
class solution226{
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//226. Invert Binary Tree
TreeNode* invertTree(TreeNode* root) {
    if (root == nullptr) {
        return root;
    }
    swap(root->left, root->right);
    invertTree(root->left);
    invertTree(root->right);
    return root;
}
};

//104. Maximum Depth of Binary Tree
int maxDepth(TreeNode* root) {
    if (root == nullptr)
        return 0;
    return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}

//543. Diameter of Binary Tree
int dfs(TreeNode* root, int& result) {
    if (root == nullptr)
        return 0;
    int left = dfs(root->left, result);
    int right = dfs(root->right, result);
    result = max(result, left + right);
    return max(left, right) + 1;
}
int diameterOfBinaryTree(TreeNode* root) {
    int result = 0;
    dfs(root, result);
    return result;
}

//110. Balanced Binary Tree
class solution110 {
    bool dfs(TreeNode* root, int& depth) {
        if (root == nullptr)
            return true;
        int leftDepth = 0;
        int rightDepth = 0;
        if (root->left != nullptr && dfs(root->left, leftDepth) == false)
            return false;
        if (root->right != nullptr && dfs(root->right, rightDepth) == false)
            return false;
        depth = max(leftDepth, rightDepth) + 1;
        if (abs(leftDepth - rightDepth) > 1)
            return false;
        return true;
    }

public:
    bool isBalanced(TreeNode* root) {
        int depth = 0;
        return dfs(root, depth);
    }
};

//100. Same Tree
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (p == nullptr && q == nullptr)
        return true;
    if (p == nullptr || q == nullptr)
        return false;
    if (p->val != q->val)
        return false;
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

//572. Subtree of Another Tree
class solution572 {
    bool isSame(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr)
            return true;
        if (p == nullptr || q == nullptr)
            return false;
        if (p->val != q->val)
            return false;
        return isSame(p->left, q->left) && isSame(p->right, q->right);
    }
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (root == nullptr)
            return false;
        if (isSame(root, subRoot))
            return true;
        return (isSubtree(root->left, subRoot)) || (isSubtree(root->right, subRoot));
    }
};

//235. Lowest Common Ancestor of a Binary Search Tree
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (p->val < root->val && q->val < root->val)
        return lowestCommonAncestor(root->left, p, q);
    else if (p->val > root->val && q->val > root->val)
        return lowestCommonAncestor(root->right, p, q);
    else
        return root;
}

//102. Binary Tree Level Order Traversal
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (root == nullptr)
        return result;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        result.push_back(vector<int>());
        while (size--) {
            TreeNode* node = q.front();
            result.back().push_back(node->val);
            q.pop();
            if (node->left != nullptr)
                q.push(node->left);
            if (node->right != nullptr)
                q.push(node->right);
        }
    }
    return result;
}

//199. Binary Tree Right Side View
vector<int> rightSideView(TreeNode* root) {
    vector<int> ans;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        ans.push_back(q.back()->val);
        int size = q.size();
        while (size--) {
            TreeNode* node = q.front();
            q.pop();
            if (node->left != nullptr)
                q.push(node->left);
            if (node->right != nullptr)
                q.push(node->right);
        }
    }
    return ans;
}

//1448. Count Good Nodes in Binary Tree
class solution1148 {
    void dfs(TreeNode* root, int maxSoFar, int& result) {
        if (root == nullptr) {
            return;
        }
        if (root->val >= maxSoFar)
            result++;
        dfs(root->left, max(root->val, maxSoFar), result);
        dfs(root->right, max(root->val, maxSoFar), result);
    }
public:
    int goodNodes(TreeNode* root) {
        int result = 0;
        dfs(root, 0, result);
        return result;
    }
};

//230. Kth Smallest Element in a BST
class Solution230 {
public:
};

//*************************************** Tries **************************************************//
//208. Implement Trie (Prefix Tree)
class TrieNode {
public:
    TrieNode* children[26];
    bool isEnd;
    TrieNode() {
        for (int i=0; i<26; i++) {
            children[i] = nullptr;
        }
        isEnd = false;
    }
};
class Trie {
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* curr = root;
        for (auto c: word) {
            auto i = c - 'a';
            if (curr->children[i] == nullptr) {
                curr->children[i] = new TrieNode();
            }
            curr = curr->children[i];
        }
        curr->isEnd = true;
    }

    bool search(string word) {
        TrieNode* curr = root;
        for (auto c: word) {
            int i = c - 'a';
            if (curr->children[i] == nullptr)
                return false;
            curr = curr->children[i];
        }
        return curr->isEnd;
    }

    bool startsWith(string prefix) {
        TrieNode* curr = root;
        for (auto c: prefix) {
            int i = c - 'a';
            if (curr->children[i] == nullptr)
                return false;
            curr = curr->children[i];
        }
        return true;
    }
};

//211. Design Add and Search Words Data Structure
class WordDictionary {
    TrieNode* root;
    bool SearchInNode(string word, int i, TrieNode* node) {
        if (node == nullptr)
            return false;
        if (i == word.size())
            return false;
        if (word[i] == '.') {
            for (int j=0; j<26; j++) {
                if (SearchInNode(word, i+1, node->children[j]))
                    return true;
            }
        }
        else {
            return SearchInNode(word, i+1, node->children[word[i]-'a']);
        }
        return false;
    }
public:
    WordDictionary() {
        root = new TrieNode();
    }

    void addWord(string word) {
        TrieNode* curr = root;
        for (auto c: word) {
            int i = c - 'a';
            if (curr->children[i] == nullptr)
                curr->children[i] = new TrieNode();
            curr = curr->children[i];
        }
        curr->isEnd = true;
    }

    bool search(string word) {
        return SearchInNode(word, 0, root);
    }
};

//*************************************** Heap / Priority Queue **************************************************//
//703. Kth Largest Element in a Stream
class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) {
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

//1046. Last Stone Weight
class Solution1046 {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int, vector<int>, greater<int>> pq;
        for (auto& stone: stones) {
            pq.push(stone);
        }

        while (pq.size() > 1) {
            int y = pq.top();
            pq.pop();
            int x = pq.top();
            pq.pop();
            if (y != x) {
                pq.push(y - x);
            }
        }
        if (pq.empty())
            return 0;
        return pq.top();
    }
};

//973. K Closest Points to Origin
class Solution973 {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        for (auto& p: points) {
            pq.push({p[0]*p[0] + p[1]*p[1], p[0], p[1]});
        }
        vector<vector<int>> res;
        while (k--) {
            auto& p = pq.top();
            pq.pop();
            res.push_back({p[1], p[2]});
        }
        return res;
    }
};

//215. Kth Largest Element in an Array
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (auto n: nums) {
        if (pq.size() == k) {
            if (n > pq.top()) {
                pq.pop();
                pq.push(n);
            }
        }
        else {
            pq.push(n);
        }
    }
    return pq.top();
}

//621. Task Scheduler
int leastInterval(vector<char>& tasks, int n) {
    return 0;
}

//*************************************** Intervals **************************************************//
//57. Insert Interval

//*************************************** Math & Geomotry **************************************************//
//48. Rotate Image
void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    for(int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
        reverse(matrix[i].begin(), matrix[i].end());
    }
}

//54. Spiral Matrix
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    int top = 0;
    int bottom = matrix.size() - 1;
    int left = 0;
    int right = matrix[0].size() - 1;
    vector<int> result;
    while (left <= right && top <= bottom) {
        for (int i=left; i<=right; i++) {
            result.push_back(matrix[top][i]);
        }
        top++;
        for (int i=top; i<=bottom; i++) {
            result.push_back(matrix[i][right]);
        }
        right--;
        if (top<=bottom) {
            for (int i=right; i>=left; i--) {
                result.push_back(matrix[bottom][i]);
            }
        }
        bottom--;
        if (left<=right) {
            for (int i=bottom; i>=top; i--) {
                result.push_back(matrix[i][left]);
            }
        }
        left++;
    }
    return result;
}

//73. Set Matrix Zeroes
void setZeroes(vector<vector<int>>& matrix) {
    bool firstColZero = false;
    bool firstRowZero = false;
    int m = matrix.size();
    int n = matrix[0].size();

    for (int i=0; i<m; i++) {
        if (matrix[i][0] == 0) {
            firstColZero = true;
            break;
        }
    }
    for (int j=0; j<n; j++) {
        if (matrix[0][j] == 0) {
            firstRowZero = true;
            break;
        }
    }
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            if(matrix[i][j] == 0) {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }
    for (int i=1; i<m; i++) {
        for (int j=1; j<n; j++) {
            if(matrix[0][j] == 0 || matrix[i][0] == 0) {
                matrix[i][j] = 0;
            }
        }
    }
    if (firstColZero) {
        for (int i=0; i<m; i++) {
            matrix[i][0] = 0;
        }
    }

    if (firstRowZero) {
        for (int j=0; j<n; j++) {
            matrix[0][j] = 0;
        }
    }
}

//202. Happy Number
bool isHappy(int n) {
    unordered_set<int> s;
    do {
        s.insert(n);
        int temp = 0;
        while (n) {
            temp += pow(n % 10, 2);
            n /= 10;
        }
        if (temp == 1)
            return true;
        if (s.count(temp))
            return false;
        n = temp;
    } while(true);
}

//66. Plus One
vector<int> plusOne(vector<int>& digits) {
    int carry = 0;
    int i = digits.size() - 1;
    do {
        digits[i] = digits[i] + carry + (i==digits.size() - 1 ? 1 : 0);
        if (digits[i] >= 10) {
            digits[i] = digits[i] % 10;
            carry = 1;
        } else {
            carry = 0;
        }
    } while(--i < digits.size() && carry != 0);
    if (carry != 0) {
        digits.insert(digits.begin(), 1);
    }
    return digits;
}



//43. Multiply Strings
string multiply(string num1, string num2) {
    int m = num1.size();
    int n = num2.size();
    string result(m+n, '0');
    for (int i=m-1; i>=0; i--) {
        for (int j=n-1; j>=0; j--) {
            int sum = (num1[i] - '0') * (num2[j] - '0') + (result[i+j+1] - '0');
            result[i+j+1] = (sum % 10) + '0';
            result[i+j] += (sum / 10);
        }
    }
    for (int i=0; i<m+n; i++) {
        if (result[i] != '0')
            return result.substr(i);
    }
    return "0";
}

//2013. Detect Squares
struct pair_hash{
    template <class T1, class T2>
        size_t operator() (const pair<T1, T2>& p) const {
            return (hash<T1> () (p.first)) ^ (hash<T2> () (p.second));
        }
};

class DetectSquares {
public:
    DetectSquares() = default;

    void add(vector<int> point) {
        points[{point[0], point[1]}]++;
    }

    int count(vector<int> point) {
        int px = point[0];
        int py = point[1];
        int result = 0;
        for (const auto &[p, cnt]: points) {
            int x, y;
            tie(x, y) = p;
            if (px != x && abs(px - x) == abs(py - y)) {
                auto it1 = points.find({x, py});
                auto it2 = points.find({px, y});
                if (it1 != points.end() && it2 != points.end()) {
                    result += cnt * points[{x, py}] * points[{px, y}];
                }
            }
        }
        return result;
    }
private:
    unordered_map<pair<int, int>, int, pair_hash> points;
};

//*************************************** Bit Manipulation **************************************************//
//136. Single Number
int singleNumber(vector<int>& nums) {
    int result = 0;
    for (auto n: nums) {
        result ^=n;
    }
    return result;
}

//191. Number of 1 Bits
int hammingWeight(uint32_t n) {
    int result = 0;
    while (n) {
        result++;
        //In essence, "n & (n - 1)" effectively clears the rightmost set bit in the binary representation of n.
        n = n & (n-1);
    }
    return result;
}

//338. Counting Bits
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

//190. Reverse Bits
uint32_t reverseBits(uint32_t n) {
    int result = 0;
    int bit = 31;
    while (n) {
        result += (n & 1) << bit;
        n = n >> 1;
        bit--;
    }
    return result;
}

//268. Missing Number
int missingNumber(vector<int>& nums) {
    int n = nums.size();
    int sum = accumulate(nums.begin(), nums.end(), 0);
    return n * (n+1) / 2 - sum;
}

//371. Sum of Two Integers
int getSum(int a, int b) {
    while (b!=0) {
        int carry = a & b;
        a = a ^ b;
        b = static_cast<unsigned int>(carry) << 1;
    }
    return a;
}

//7.Reverse Integer
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


int main() {
    Solution1921 s;
    vector<int> dist = {1,3,4};
    vector<int> speed = {1,1,1};
    cout << s.eliminateMaximum(dist, speed) << endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
