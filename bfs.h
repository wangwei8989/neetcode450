//
// Created by Wei on 1/11/24.
//

#ifndef NEETCODE150_BFS_H
#define NEETCODE150_BFS_H

#include "common.h"

//102. Binary Tree Level Order Traversal
/*class Solution102 {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> que;
        vector<vector<int>> res ;
        if(root != nullptr) que.push(root);
        while(!que.empty())
        {
            vector<int> tmp;
            for(int i = que.size(); i > 0 ; i--)
            {
                root  = que.front();
                que.pop();
                tmp.push_back(root->val);
                if(root->left != nullptr) que.push(root->left);
                if(root->right != nullptr) que.push(root->right);
            }
            res.push_back(tmp);
        }

        return res;
    }
};*/

//323. numbers of connected components in a undirected graph
/*class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {

    }
};*/

//107. Binary Tree Level Order Traversal II
/*class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {

    }
};*/

//103. Binary Tree Zigzag Level Order Traversal
/*class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {

        std ::map<int, std::vector<TreeNode*>>bfs_map;
        vector < vector<int>>result;

        if (root !=nullptr)

    }
};*/

//429. N-ary Tree Level Order Traversal
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

/*class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {

    }
};*/

//993. Cousins in Binary Tree
/*class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {

    }
};*/
#endif //NEETCODE150_BFS_H
