//
// Created by Wei on 12/22/23.
//

#ifndef NEETCODE150_DFS_H
#define NEETCODE150_DFS_H
#include "common.h"

//94. Binary Tree Inorder Traversal

class Solution94 {
public:
    void dfs(TreeNode* root, vector<int>& result)
    {
        if (root->left != NULL)
            dfs(root->left, result);
        result.push_back(root->val);
        if (root->right != NULL)
            dfs(root->right, result);
    }

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if (root == NULL)
            return result;
        dfs(root, result);
        return result;
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

//100. Same Tree
class Solution100 {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr)
            return true;
        if (p != nullptr && q != nullptr) {
            return p->val == q->val
                   && isSameTree(p->left, q->left)
                   && isSameTree(p->right, q->right);
        } else
            return false;
    }
};

//101, symmetric tree
class Solution101 {
public:
    bool dfs(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr)
            return true;
        if (p != nullptr && q != nullptr) {
            return p->val == q->val
                   && dfs(p->left, q->right)
                   && dfs(p->right, q->left);
        } else
            return false;
    }

    bool isSymmetric(TreeNode* root) {
        if (root == nullptr)
            return true;
        return dfs(root->left, root->right);
    }
};

//104. Maximum Depth of Binary Tree
class Solution104 {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};

//110. Balanced Binary Tree
class Solution110 {
public:
    bool dfs(TreeNode* root, int& depth) {
        if (root == nullptr)
            return true;
        int leftDepth = 0;
        int rightDepth = 0;
        if (dfs(root->left, leftDepth) &&
            dfs(root->right, rightDepth) &&
            abs(leftDepth - rightDepth) <= 1) {
            depth = max(leftDepth, rightDepth) + 1;
            return true;
        }
        else
            return false;
    }
    bool isBalanced(TreeNode* root) {
        int depth = 0;
        return dfs(root, depth);
    }
};

//111. Minimum Depth of Binary Tree
class Solution111 {
public:
    int minDepth(TreeNode* root) {
        if (root== nullptr)
            return 0;
        if (root->left == nullptr && root->right == nullptr)
            return 1;
        int leftDepth = root->left ? minDepth(root->left) : INT_MAX;
        int rightDepth = root->right ? minDepth(root->right) : INT_MAX;
        return min(leftDepth, rightDepth) + 1;
    }
};

//112. path sum
class Solution112 {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) {
            return false;
        }
        if (root->left == nullptr && root->right == nullptr && root->val == targetSum)
            return true;
        return hasPathSum(root->left, targetSum - root->val)
               || hasPathSum(root->right, targetSum - root->val);
    }
};

//129. Sum Root to Leaf Numbers
class Solution129 {
public:
/*    int dfs(TreeNode* node, int currentSum) {
        if(node == nullptr)
            return 0;
        currentSum = currentSum * 10 + node->val;
        if (node->left == nullptr && node->right == nullptr) {
            return currentSum;
        }
        return dfs(node->left, currentSum) + dfs(node->right, currentSum);
    }*/

    int sumNumbers(TreeNode* root) {
        // return dfs(root, 0);
        if (root == nullptr)
            return 0;
        stack<pair<TreeNode*, int>> s;
        s.push({root, 0});
        int result = 0;
        while (!s.empty()) {
            auto& [node, val] = s.top();
            s.pop();
            val = val * 10 + node->val;
            if (node->left)
                s.push({node->left, val});
            if (node->right)
                s.push({node->right, val});
            if (node->left == nullptr && node->right == nullptr)
               result += val;
        }
        return result;
    }
};

//130. Surrounded Regions
class Solution130 {
public:
    void dfs(vector<vector<char>>& board, int x, int y) {
        if (x < 0 || x >= board.size() || y < 0 || y >= board[0].size() ||
            board[x][y] != 'O')
            return;
        board[x][y] = 'A';
        dfs(board, x-1, y);
        dfs(board, x+1, y);
        dfs(board, x, y-1);
        dfs(board, x, y+1);
    }

    void solve(vector<vector<char>>& board) {
        int n = board.size();
        if (n == 0)
            return;
        int m = board[0].size();
        for (int i=0; i<n; i++) {
            dfs(board, i, 0);
            dfs(board, i, m-1);
        }
        for (int i=0; i<m; i++) {
            dfs(board, 0, i);
            dfs(board, n-1, i);
        }
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (board[i][j] == 'A')
                    board[i][j] = 'O';
                else if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
            }
        }
    }
};

//133. Clone Graph
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution133 {
public:
    class Solution {
    public:
        unordered_map<Node*, Node*> seen;
        Node* cloneGraph(Node* node) {
            if (node == nullptr)
                return nullptr;
            if (seen.count(node)!=0) {
                return seen[node];
            }

            Node* cloneNode = new Node(node->val);
            seen[node] = cloneNode;

            for (auto neighbor:node->neighbors) {
                cloneNode->neighbors.emplace_back(cloneGraph(neighbor));
            }
            return cloneNode;
        }
    };
};

//144. Binary Tree Preorder Traversal
class Solution144 {
public:
    void dfs(TreeNode* node, vector<int>& result) {
        if (node == nullptr)
            return;
        result.push_back(node->val);
        dfs(node->left, result);
        dfs(node->right, result);
    }

    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        dfs(root, result);
        return result;
    }
};

//145. Binary Tree Postorder Traversal
class Solution145 {
public:
    void dfs(TreeNode* node, vector<int>& result) {
        if (node == nullptr)
            return;
        dfs(node->left, result);
        dfs(node->right, result);
        result.push_back(node->val);
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        dfs(root, result);
        return result;
    }
};

//199. Binary Tree Right Side View
class Solution199 {
public:
    void dfs(TreeNode* node, vector<int>& result) {
        if (node == nullptr)
            return;
        result.push_back(node->val);
        if (node->right != nullptr)
            dfs(node->right, result);
        else
            dfs(node->left, result);
    }
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        dfs(root, result);
        return result;
    }
};

//236. Lowest Common Ancestor of a Binary Tree
class Solution236 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == NULL || root == p || root == q){
            return root;
        }
        auto left = lowestCommonAncestor(root->left, p, q);
        auto right = lowestCommonAncestor(root->right, p, q);
        if(left != NULL && right != NULL){
            return root;
        }
        else if (right != NULL){
            return right;
        }
        else {
            return left;
        }
    }
};

//105. Construct Binary Tree from Preorder and Inorder Traversal
class Solution105 {
    unordered_map<int, int> inorderMap;

public:
    TreeNode* dfs(const vector<int>& preorder, const vector<int>& inorder, int& preorderIndex, int inorderLeft, int inorderRight) {
        if (inorderLeft > inorderRight) {
            return nullptr;
        }

        TreeNode* root = new TreeNode(preorder[preorderIndex]);
        auto inorderIndex = inorderMap[root->val];

        // Increment the preorderIndex correctly for left and right subtrees
        root->left = dfs(preorder, inorder, ++preorderIndex, inorderLeft, inorderIndex-1);
        root->right = dfs(preorder, inorder, ++preorderIndex, inorderIndex+1, inorderRight);

        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        for (int i = 0; i < n; ++i) {
            inorderMap[inorder[i]] = i;
        }

        int preorderIndex = 0; // Pass by reference to keep track of the current index in preorder
        return dfs(preorder, inorder, preorderIndex, 0, inorder.size()-1);
    }
};

//106. Construct Binary Tree from Inorder and Postorder Traversal
class Solution106 {
    unordered_map<int, int> inorderMap;

public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();
        for (int i = 0; i < n; ++i) {
            inorderMap[inorder[i]] = i;
        }

        int postorderIndex = n - 1; // Start from the last element of postorder
        return dfs(inorder, postorder, 0, n - 1, postorderIndex);
    }

    TreeNode* dfs(const vector<int>& inorder, const vector<int>& postorder, int inorderLeft, int inorderRight, int& postorderIndex) {
        if (inorderLeft > inorderRight) {
            return nullptr;
        }
        TreeNode* root = new TreeNode(postorder[postorderIndex--]);
        int inorderIndex = inorderMap[root->val];
        root->right = dfs(inorder, postorder, inorderIndex + 1, inorderRight, postorderIndex);
        root->left = dfs(inorder, postorder, inorderLeft, inorderIndex - 1, postorderIndex);
        return root;
    }
};

//1008. Construct Binary Search Tree from Preorder Traversal
class Solution1008_dfs {
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

//1028. Recover a Tree From Preorder Traversal
class Solution1028 {
public:
    TreeNode* recoverFromPreorder(string traversal) {
        stack<TreeNode*> nodes;
        int i = 0;  // index for traversal string

        while (i < traversal.size()) {
            int depth = 0;
            while (i < traversal.size() && traversal[i] == '-') {
                ++depth;
                ++i;
            }

            int value = 0;
            while (i < traversal.size() && isdigit(traversal[i])) {
                value = value * 10 + (traversal[i] - '0');
                ++i;
            }

            TreeNode* node = new TreeNode(value);

            while (nodes.size() > depth) {
                nodes.pop();
            }

            if (!nodes.empty()) {
                if (!nodes.top()->left) {
                    nodes.top()->left = node;
                } else {
                    nodes.top()->right = node;
                }
            }

            nodes.push(node);
        }

        while (nodes.size() > 1) {
            nodes.pop();
        }

        return nodes.top();
    }
};



#endif //NEETCODE150_DFS_H
