//
// Created by Wei on 2/7/24.
//

#ifndef NEETCODE150_TREES_H
#define NEETCODE150_TREES_H

#include "common.h"

//226. Invert Binary Tree
class Solution226 {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == NULL) {
            return NULL;
        }
        swap(root->left, root->right);
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};

//104. Maximum Depth of Binary Tree
class Solution104 {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr)
            return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};

//543. Diameter of Binary Tree
class Solution543 {
public:
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
};

//110. Balanced Binary Tree
class Solution {
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
        return false;
    }
    bool isBalanced(TreeNode* root) {
        int depth = 0;
        return dfs(root, depth);
    }
};

//100. Same Tree
class Solution100 {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr)
            return true;
        if (p == nullptr || q == nullptr)
            return false;
        if (p->val != q->val)
            return false;
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

//572. Subtree of Another Tree
class Solution572 {
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

//102. Binary Tree Level Order Traversal
class Solution102 {
public:
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

//1448. Count Good Nodes in Binary Tree
class Solution1448 {
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
        dfs(root, root->val, result);
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

//230. Kth Smallest Element in a BST
class Solution230 {
public:
    int kthSmallest(TreeNode* root, int k) {
        int result = 0;
        inorder(root, k, result);
        return result;
    }
private:
    void inorder(TreeNode* root, int& k, int& result) {
        if (root == NULL) {
            return;
        }
        inorder(root->left, k, result);
        k--;
        if (k == 0) {
            result = root->val;
            return;
        }
        inorder(root->right, k, result);
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

        TreeNode* root = new TreeNode(preorder[preorderIndex++]);
        auto inorderIndex = inorderMap[root->val];

        // Increment the preorderIndex correctly for left and right subtrees
        root->left = dfs(preorder, inorder, preorderIndex, inorderLeft, inorderIndex-1);
        root->right = dfs(preorder, inorder, preorderIndex, inorderIndex+1, inorderRight);

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

//124. Binary Tree Maximum Path Sum
class Solution124 {
public:
    int maxPathSum(TreeNode* root) {
        maxPathHelper(root);
        return ans;
    }

private:
    int ans = INT_MIN;
    int maxPathHelper(TreeNode* root){
        if(root == nullptr) {
            return 0;
        }
        int left = max(maxPathHelper(root->left), 0);
        int right = max(maxPathHelper(root->right), 0);
        ans = max(ans,left + right + root->val);
        // Return the maximum path sum that can be extended to the parent node
        return max(left,right) + root->val;
    }
};

//297. Serialize and Deserialize Binary Tree
class Codec297 {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream out;
        encode(root, out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return decode(in);
    }

private:

    void encode(TreeNode* root, ostringstream& out) {
        if (root == NULL) {
            out << "N ";
            return;
        }

        out << root->val << " ";

        encode(root->left, out);
        encode(root->right, out);
    }

    TreeNode* decode(istringstream& in) {
        string value = "";
        in >> value;

        if (value == "N") {
            return NULL;
        }

        TreeNode* root = new TreeNode(stoi(value));

        root->left = decode(in);
        root->right = decode(in);

        return root;
    }

};
#endif //NEETCODE150_TREES_H
