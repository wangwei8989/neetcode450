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
#endif //NEETCODE150_TRIES_H
