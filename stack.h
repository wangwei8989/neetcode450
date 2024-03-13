//
// Created by Wei on 2/1/24.
//

#ifndef NEETCODE150_STACK_H
#define NEETCODE150_STACK_H

#include "common.h"
//20. Valid Parentheses
class Solution20 {
public:
    bool isValid(string s) {
        unordered_map<char, char> cps = {
                {')', '('},
                {']', '['},
                {'}', '{'}
        };
        stack<char> st;
        for (const auto& c: s) {
            if (cps.count(c)) {
                if (st.empty() || cps[c] != st.top())
                    return false;
                st.pop();
            }
            else {
                st.push(c);
            }
        }
        return st.empty();
    }
};

//225. Implement Stack using Queues
class MyStack {
    queue<int> q1;
    queue<int> q2;
public:
    MyStack() = default;

    void push(int x) {
        q2.push(x);
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1, q2);
    }

    int pop() {
        int x = q1.front();
        q1.pop();
        return x;
    }

    int top() {
        return q1.front();
    }

    bool empty() {
        return q1.empty();
    }
};

//155. Min Stack
class MinStack {
    stack<int> st;
    stack<int> stMin;
public:
    MinStack() = default;

    void push(int val) {
        if (stMin.empty() || val <= stMin.top())
            stMin.push(val);
        st.push(val);
    }

    void pop() {
        if (st.top() == stMin.top()) {
            stMin.pop();
        }
        st.pop();
    }

    int top() {
        return st.top();
    }

    int getMin() {
        return stMin.top();
    }
};

//150. Evaluate Reverse Polish Notation
class Solution150 {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> stk;
        for (const auto& token: tokens) {
            if (token.length() > 1 || isdigit(token[0])) {
                stk.push(stoi(token));
            }
            else {
                int rhp = stk.top();
                stk.pop();
                int lhp = stk.top();
                stk.pop();
                if (token == "+")
                    stk.push(lhp + rhp);
                else if (token == "-")
                    stk.push(lhp - rhp);
                else if (token == "*")
                    stk.push(lhp * rhp);
                else
                    stk.push(lhp / rhp);
            }
        }
        return stk.top();
    }
};

//22. Generate Parentheses
class Solution22 {
public:
    unordered_set<string> recur(int n) {
        unordered_set<string> ans;
        if (n == 1) {
            ans.insert("()");
        }
        else {
            const auto& sub = recur(n - 1);
            for (const auto& str : sub) {
                for (int i = 0; i < str.length(); i++) {
                    string tmp = str;
                    tmp.insert(i, "()");
                    ans.insert(tmp);
                }
            }
        }
        return ans;
    }

    vector<string> generateParenthesis(int n) {
        const unordered_set<string>& ans = recur(n);
        return vector<string>(make_move_iterator(ans.begin()),
                              make_move_iterator(ans.end()));
    }

};

//739. Daily Temperatures
class Solution739 {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n, 0);
        stack<int> stk;
        for (int i = 0; i < n; i++) {
            while (!stk.empty() && temperatures[stk.top()] < temperatures[i]) {
                ans[stk.top()] = i - stk.top();
                stk.pop();
            }
            stk.push(i);
        }
        return ans;
    }
};

//853. Car Fleet
class Solution853 {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();

        vector<pair<int, double>> cars;
        for (int i = 0; i < n; i++) {
            double time = (double) (target - position[i]) / speed[i];
            cars.push_back({position[i], time});
        }
        sort(cars.begin(), cars.end());

        double maxTime = 0.0;
        int result = 0;

        for (int i = n - 1; i >= 0; i--) {
            double time = cars[i].second;
            if (time > maxTime) {
                maxTime = time;
                result++;
            }
        }

        return result;
    }
};

//394. Decode String
class Solution394_stack {
public:
    string decodeString(string s) {
        stack<int> multi_stack;
        stack<string> str_stack;
        string ans;
        int multi = 0;
        for (const auto c: s) {
            if (c == '[') {
                multi_stack.push(multi);
                str_stack.push(ans);
                multi = 0;
                ans.clear();
            }
            else if (c == ']') {
                string temp;
                while (multi_stack.top()-- > 0) {
                    temp += ans;
                }
                multi_stack.pop();
                ans = str_stack.top() + temp;
                str_stack.pop();
            }
            else if (isdigit(c)) {
                multi = multi * 10 + c - '0';
            }
            else {
                ans += c;
            }
        }
        return ans;
    }
};

//84. Largest Rectangle in Histogram
class Solution84 {
public:
    int largestRectangleArea(vector<int>& heights) {
        // pair: [index, height]
        stack<pair<int, int>> stk;
        int result = 0;

        for (int i = 0; i < heights.size(); i++) {
            int start = i;

            while (!stk.empty() && stk.top().second > heights[i]) {
                int index = stk.top().first;
                int width = i - index;
                int height = stk.top().second;
                stk.pop();

                result = max(result, height * width);
                start = index;
            }

            stk.push({start, heights[i]});
        }

        while (!stk.empty()) {
            int width = heights.size() - stk.top().first;
            int height = stk.top().second;
            stk.pop();

            result = max(result, height * width);
        }

        return result;
    }
};

//32. Longest Valid Parentheses
class Solution32 {
public:
    int longestValidParentheses(string s) {
        int maxans = 0;
        stack<int> stk;
        stk.push(-1);
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                stk.push(i);
            } else {
                stk.pop();
                if (stk.empty()) {
                    stk.push(i);
                } else {
                    maxans = max(maxans, i - stk.top());
                }
            }
        }
        return maxans;
    }
};

//225. Implement Stack using Queues
class MyStack {
    queue<int> q1;
    queue<int> q2;
public:
    /** Initialize your data structure here. */
    MyStack() = default;

    /** Push element x onto stack. */
    void push(int x) {
        q2.push(x);
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1, q2);
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int x = q1.front();
        q1.pop();
        return x;
    }

    /** Get the top element. */
    int top() {
        return q1.front();
    }

    /** Returns whether the stack is empty. */
    bool empty() {
        return q1.empty();
    }
};

//232. Implement Queue using Stacks
class MyQueue {
public:
    stack<int> ins;
    stack<int> outs;
    void in2out () {
        while (!ins.empty()) {
            outs.push(ins.top());
            ins.pop();
        }
    }
    MyQueue() =default;

    /** Push element x to the back of queue. */
    void push(int x) {
        ins.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        if (outs.empty()) {
            in2out();
        }
        int x = outs.top();
        outs.pop();
        return x;
    }

    /** Get the front element. */
    int peek() {
        if (outs.empty()) {
            in2out();
        }
        return outs.top();
    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return ins.empty() && outs.empty();
    }
};

//341. Flatten Nested List Iterator
 class NestedInteger {
  public:
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};
class NestedIterator {
    deque<int> queue;
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        for (auto list: nestedList)
            dfs(list);
    }

    int next() {
        if (hasNext()) {
            int x = queue.front();
            queue.pop_front();
            return x;
        }
        else
            return -1;
    }

    bool hasNext() {
        return !queue.empty();
    }

    void dfs(NestedInteger list) {
        if (list.isInteger()) {
            queue.push_back(list.getInteger());
        }
        else {
            for (auto itor: list.getList()) {
                dfs(itor);
            }
        }
    }

};

//445. Add Two Numbers II
class Solution445 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<int> s1;
        stack<int> s2;
        ListNode* node = l1;
        while (node != nullptr) {
            s1.push(node->val);
            node = node->next;
        }
        node = l2;
        while (node != nullptr) {
            s2.push(node->val);
            node = node->next;
        }

        int carry = 0;
        int tmp1 =0;
        int tmp2 =0;
        ListNode* next = nullptr;
        ListNode* newnode = nullptr;
        while (!s1.empty() || !s2.empty() || carry != 0) {
            newnode = new ListNode;
            if (!s1.empty()) {
                tmp1 = s1.top();
                s1.pop();
            }
            else {
                tmp1 = 0;
            }

            if (!s2.empty()) {
                tmp2 = s2.top();
                s2.pop();
            }
            else {
                tmp2 = 0;
            }
            newnode->val = (tmp1 + tmp2 + carry) % 10;
            carry = (tmp1 + tmp2 + carry) / 10;
            newnode->next = next;
            next = newnode;
        }
        return newnode;
    }
};
#endif //NEETCODE150_STACK_H
