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
class Solution394 {
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



#endif //NEETCODE150_STACK_H
