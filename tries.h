//
// Created by Wei on 2/7/24.
//

#ifndef NEETCODE150_TRIES_H
#define NEETCODE150_TRIES_H

#include "common.h"

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
            return node->isEnd;
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

//2707. Extra Characters in a String
class Solution2707 {
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        int n = s.size();
        vector<int> dp(n + 1, n);

        dp[0] = 0;

        for (int i = 1; i <= n; ++i) {
            for(int j = 0 ; j < dictionary.size() ; ++j) {
                int len = dictionary[j].size();
                if (i >= len && s.substr(i - len, len) == dictionary[j]) {
                    dp[i] = min(dp[i], dp[i - len]);
                }
            }
            dp[i] = min(dp[i], dp[i - 1] + 1);
        }

        return dp[n];
    }
};

//212. Word Search II
class Solution212 {
    class TrieNode {
    public:
        TrieNode* children[26];
        bool isWord;

        TrieNode() {
            for (int i = 0; i < 26; i++) {
                children[i] = NULL;
            }
            isWord = false;
        }
    };
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        for (int i = 0; i < words.size(); i++) {
            insert(words[i]);
        }

        int m = board.size();
        int n = board[0].size();

        TrieNode* node = root;
        vector<string> result;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                search(board, i, j, m, n, node, "", result);
            }
        }

        return result;
    }
private:
    TrieNode* root = new TrieNode();

    void insert(string word) {
        TrieNode* node = root;
        int curr = 0;

        for (int i = 0; i < word.size(); i++) {
            curr = word[i] - 'a';
            if (node->children[curr] == NULL) {
                node->children[curr] = new TrieNode();
            }
            node = node->children[curr];
        }

        node->isWord = true;
    }

    void search(vector<vector<char>>& board, int i, int j, int m, int n, TrieNode* node, string word, vector<string>& result) {
        if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] == '#') {
            return;
        }

        char c = board[i][j];

        node = node->children[c - 'a'];
        if (node == NULL) {
            return;
        }

        word += board[i][j];
        if (node->isWord) {
            result.push_back(word);
            node->isWord = false;
        }

        board[i][j] = '#';

        search(board, i - 1, j, m, n, node, word, result);
        search(board, i + 1, j, m, n, node, word, result);
        search(board, i, j - 1, m, n, node, word, result);
        search(board, i, j + 1, m, n, node, word, result);

        board[i][j] = c;
    }
};

//421. Maximum XOR of Two Numbers in an Array
class Solution421_tries {
public:
    struct Trie {
        // 左子树指向表示 0 的子节点
        Trie* left = nullptr;
        // 右子树指向表示 1 的子节点
        Trie* right = nullptr;

        Trie() = default;
    };
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

//1707. Maximum XOR With an Element From Array
class Solution1707_tries {
public:
    class Trie {
    public:
        const int L = 30;

        Trie* children[2] = {};
        int min = INT_MAX;

        void insert(int val) {
            Trie* node = this;
            node->min = min(node->min, val);
            for (int i = L - 1; i >= 0; --i) {
                int bit = (val >> i) & 1;
                if (node->children[bit] == nullptr) {
                    node->children[bit] = new Trie();
                }
                node = node->children[bit];
                node->min = min(node->min, val);
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

//1268. Search Suggestions System
class Solution1268 {
private:
    struct Trie {
        unordered_map<char, Trie*> child;
        priority_queue<string> words;
    };

    void addWord(Trie* root, const string& word) {
        Trie* cur = root;
        for (const char& ch: word) {
            if (!cur->child.count(ch)) {
                cur->child[ch] = new Trie();
            }
            cur = cur->child[ch];
            cur->words.push(word);
            if (cur->words.size() > 3) {
                cur->words.pop();
            }
        }
    }

public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        Trie* root = new Trie();
        for (const string& word: products) {
            addWord(root, word);
        }

        vector<vector<string>> ans;
        Trie* cur = root;
        bool flag = false;
        for (const char& ch: searchWord) {
            if (flag || !cur->child.count(ch)) {
                ans.emplace_back();
                flag = true;
            }
            else {
                cur = cur->child[ch];
                vector<string> selects;
                while (!cur->words.empty()) {
                    selects.push_back(cur->words.top());
                    cur->words.pop();
                }
                reverse(selects.begin(), selects.end());
                ans.push_back(move(selects));
            }
        }

        return ans;
    }
};
#endif //NEETCODE150_TRIES_H
