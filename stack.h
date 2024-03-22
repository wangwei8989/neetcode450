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

//682. Baseball Game
class Solution682 {
public:
    int calPoints(vector<string>& ops) {
        stack<int> stack;
        int sum =  0;

        for (int i = 0; i < ops.size(); i++){
            if (ops[i] == "+"){
                int first = stack.top();
                stack.pop();

                int second = stack.top();

                stack.push(first);

                stack.push(first + second);

                sum += first + second;
            }

            else if (ops[i] == "D"){
                sum += 2 * stack.top();
                stack.push(2 * stack.top());
            }

            else if (ops[i] == "C"){
                sum -= stack.top();
                stack.pop();
            }

            else{
                sum += stoi(ops[i]);
                stack.push(stoi(ops[i]));
            }
        }

        return sum;
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

//2390. Removing Stars From a String
class Solution2390 {
public:
    string removeStars(string s) {
        stack<char> stack;
        for (char ch : s) {
            if (ch == '*' && !stack.empty()) {
                stack.pop();
            } else {
                stack.push(ch);
            }
        }

        string result;
        while (!stack.empty()) {
            result += stack.top();
            stack.pop();
        }

        reverse(result.begin(), result.end());
        return result;
    }
};

//946. Validate Stack Sequences
class Solution946 {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> stack;
        int j = 0;
        for (int num : pushed) {
            stack.push(num);
            while (!stack.empty() && stack.top() == popped[j]) {
                stack.pop();
                j++;
            }
        }
        for (; j < popped.size(); ++j) {
            if (stack.empty() || stack.top() != popped[j]) {
                return false;
            }
            stack.pop();
        }
        return true;
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

//735. Asteroid Collision
class Solution735 {
public:
    std::vector<int> asteroidCollision(std::vector<int>& asteroids) {
        std::stack<int> stk;
        for (int asteroid : asteroids) {
            if (stk.empty() || asteroid > 0) {
                stk.push(asteroid);
            } else {
                while (!stk.empty() && stk.top() > 0 && stk.top() < -asteroid) {
                    stk.pop();
                }
                if (stk.empty() || stk.top() < 0) {
                    stk.push(asteroid);
                } else if (stk.top() == -asteroid) {
                    stk.pop(); // Both asteroids explode
                }
            }
        }

        std::vector<int> result;
        for (int i = stk.size() - 1; i >= 0; --i) {
            result.push_back(stk.top());
            stk.pop();
        }
        reverse(result.begin(), result.end());
        return result;
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

//901. Online Stock Span
class StockSpanner {
private:
    std::stack<std::pair<int, int>> stk;

public:
    StockSpanner() {

    }

    int next(int price) {
        int span = 1;
        while (!stk.empty() && stk.top().first <= price) {
            span += stk.top().second;
            stk.pop();
        }
        stk.push({price, span});
        return span;
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

//71. Simplify Path
class Solution71 {
public:
    std::string simplifyPath(std::string path) {
        std::stack<std::string> directories;
        std::string directory;

        // Split the input path by '/'
        for (char& c : path) {
            if (c == '/') {
                if (directory == "..") {
                    if (!directories.empty()) {
                        directories.pop(); // Go up a level
                    }
                } else if (!directory.empty() && directory != ".") {
                    directories.push(directory);
                }
                directory.clear();
            } else {
                directory += c;
            }
        }

        // Handle the last directory
        if (!directory.empty()) {
            if (directory == "..") {
                if (!directories.empty()) {
                    directories.pop(); // Go up a level
                }
            } else if (directory != ".") {
                directories.push(directory);
            }
        }

        // Construct the canonical path
        std::string canonicalPath;
        while (!directories.empty()) {
            canonicalPath = '/' + directories.top() + canonicalPath;
            directories.pop();
        }

        return canonicalPath.empty() ? "/" : canonicalPath;
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

//402. Remove K Digits
class Solution402 {
public:
    std::string removeKdigits(std::string num, int k) {
        std::stack<char> stk;

        for (char digit : num) {
            while (!stk.empty() && k > 0 && stk.top() > digit) {
                stk.pop();
                k--;
            }
            stk.push(digit);
        }

        while (k > 0 && !stk.empty()) {
            stk.pop();
            k--;
        }

        std::string result;
        while (!stk.empty()) {
            result += stk.top();
            stk.pop();
        }
        reverse(result.begin(), result.end());

        size_t nonZeroPos = result.find_first_not_of('0');
        result = (nonZeroPos == std::string::npos) ? "0" : result.substr(nonZeroPos);

        return result.empty() ? "0" : result;
    }
};

//1209. Remove All Adjacent Duplicates in String II
class Solution1209 {
public:
    std::string removeDuplicates(std::string s, int k) {
        std::stack<std::pair<char, int>> stk;

        for (char c : s) {
            if (!stk.empty() && stk.top().first == c) {
                stk.top().second++;
                if (stk.top().second == k) {
                    stk.pop();
                }
            } else {
                stk.push({c, 1});
            }
        }

        std::string result;
        while (!stk.empty()) {
            auto [c, count] = stk.top();
            stk.pop();
            while (count--)
                result.push_back(c);
        }
        reverse(result.begin(), result.end());

        return result;
    }
};

//456. 132 Pattern
class Solution456 {
public:
    bool find132pattern(std::vector<int>& nums) {
        int n = nums.size();
        std::stack<int> stk;
        int max_val = INT_MIN;

        for (int i = n - 1; i >= 0; --i) {
            if (nums[i] < max_val) {
                return true;
            }
            while (!stk.empty() && nums[i] > stk.top()) {
                max_val = stk.top();
                stk.pop();
            }
            stk.push(nums[i]);
        }

        return false;
    }
};

//895. Maximum Frequency Stack
class FreqStack {
public:
    FreqStack() {
        maxFreq = 0;
    }

    void push(int val) {
        freq[val]++;
        group[freq[val]].push(val);
        maxFreq = max(maxFreq, freq[val]);
    }

    int pop() {
        int val = group[maxFreq].top();
        freq[val]--;
        group[maxFreq].pop();
        if (group[maxFreq].empty()) {
            maxFreq--;
        }
        return val;
    }

private:
    unordered_map<int, int> freq;
    unordered_map<int, stack<int>> group;
    int maxFreq;
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
