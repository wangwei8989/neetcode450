//
// Created by Wei on 2/7/24.
//

#ifndef NEETCODE150_HEAP_PRIORITYQUEUE_H
#define NEETCODE150_HEAP_PRIORITYQUEUE_H

#include "common.h"

//703. Kth Largest Element in a Stream
class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        for (int i = 0; i < nums.size(); i++) {
            pq.push(nums[i]);
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
    int k;
    priority_queue<int, vector<int>, greater<int>> pq;
};

//1046. Last Stone Weight
class Solution1046 {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> pq;
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
        vector<vector<int>> triples;
        for (auto& p : points)
            triples.push_back({p[0] * p[0] + p[1] * p[1], p[0], p[1]});
        // Min heap of vectors (triples). This constructor takes O(n) time (n = len(v))
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq(triples.begin(), triples.end());
        vector<vector<int>> res;
        while (k--){
            vector<int> el = pq.top();
            pq.pop();
            res.push_back({el[1], el[2]});
        }
        return res;
    }
};

//215. Kth Largest Element in an Array
class Solution215 {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int index = nums.size() - k;
        return quickSelect(nums, index, 0, nums.size() - 1);
    }
private:
    int quickSelect(vector<int>& nums, int k, int l, int r){
        int pivot = nums[r];
        int p_pos = l;
        for (int i = l; i < r; ++i){
            if (nums[i] <= pivot){
                swap(nums[i], nums[p_pos]);
                ++p_pos;
            }
        }
        swap(nums[p_pos], nums[r]);
        if (k < p_pos)
            return quickSelect(nums, k, l, p_pos - 1);
        if (k > p_pos)
            return quickSelect(nums, k, p_pos + 1, r);
        return nums[p_pos];
    }
};

//621. Task Scheduler
class Solution621 {
public:
    int leastInterval(vector<char>& tasks, int n) {
        priority_queue<int> pq;
        queue<vector<int>> q;
        vector<int> counter(26);

        for (int i = 0; i < tasks.size(); ++i)
            ++counter[tasks[i] - 'A'];
        for (int i = 0; i < 26; ++i){
            if (counter[i])
                pq.push(counter[i]);
        }

        int time = 0;
        while (!q.empty() || !pq.empty()){
            ++time;
            if (!pq.empty()){
                if (pq.top() - 1)
                    q.push({pq.top() - 1, time + n});
                pq.pop();
            }
            if (!q.empty() && q.front()[1] == time){
                pq.push(q.front()[0]);
                q.pop();
            }
        }
        return time;
    }
};

//355. Design Twitter
class Twitter {
public:
    Twitter() {

    }

    void postTweet(int userId, int tweetId) {
        posts.push_back({userId, tweetId});
    }

    vector<int> getNewsFeed(int userId) {
        // 10 tweets
        int count = 10;
        vector<int> result;

        // since postTweet pushes to the back, looping from back gets most recent
        for (int i = posts.size() - 1; i >= 0; i--) {
            if (count == 0) {
                break;
            }

            int followingId = posts[i].first;
            int tweetId = posts[i].second;
            unordered_set<int> following = followMap[userId];
            // add to result if they're following them or it's a tweet from themself
            if (following.find(followingId) != following.end() || followingId == userId) {
                result.push_back(tweetId);
                count--;
            }
        }

        return result;
    }

    void follow(int followerId, int followeeId) {
        followMap[followerId].insert(followeeId);
    }

    void unfollow(int followerId, int followeeId) {
        followMap[followerId].erase(followeeId);
    }
private:
    // pairs: [user, tweet]
    vector<pair<int, int>> posts;
    // hash map: {user -> people they follow}
    unordered_map<int, unordered_set<int>> followMap;
};

//295. Find Median from Data Stream
class MedianFinder {
public:
    MedianFinder() {

    }

    void addNum(int num) {
        if (lower.empty()) {
            lower.push(num);
            return;
        }

        if (lower.size() > higher.size()) {
            if (lower.top() > num) {
                higher.push(lower.top());
                lower.pop();
                lower.push(num);
            } else {
                higher.push(num);
            }
        } else {
            if (num > higher.top()) {
                lower.push(higher.top());
                higher.pop();
                higher.push(num);
            } else {
                lower.push(num);
            }
        }
    }

    double findMedian() {
        double result = 0.0;

        if (lower.size() == higher.size()) {
            result = lower.top() + (higher.top() - lower.top()) / 2.0;
        } else {
            if (lower.size() > higher.size()) {
                result = lower.top();
            } else {
                result = higher.top();
            }
        }

        return result;
    }
private:
    priority_queue<int> lower;
    priority_queue<int, vector<int>, greater<int>> higher;
};

//451. Sort Characters By Frequency
class Solution451 {
public:
    string frequencySort(string s) {
        unordered_map<char, int> mp;
        int maxFreq = 0;
        int length = s.size();
        for (auto &ch : s) {
            maxFreq = max(maxFreq, ++mp[ch]);
        }
        map<int, string,greater<int>> buckets;
        for (auto &[ch, num] : mp) {
            buckets[num].push_back(ch);
        }
        string ret;
        for (auto x: buckets) {
            string &bucket = x.second;
            for (auto &ch : x.second) {
                //string tmp(x.first, ch);
                ret += string(x.first, ch);
            }
        }
        return ret;
    }
};

//692. Top K Frequent Words
class Solution692 {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> map;
        for (auto w: words) {
            map[w]++;
        }
        vector<string> vec;
        for (auto &[k,v]: map) {
            vec.emplace_back(k);
        }
        sort(vec.begin(), vec.end(), [&](string a, string b)->bool{return map[a]>map[b] || (map[a]==map[b] && a<b);});
        return vector<string>(vec.begin(), vec.begin()+k);
    }
};

//871. Minimum Number of Refueling Stops
class Solution871 {
public:
    class IntHeap {
    public:
        bool operator()(int a, int b) {
            return a < b; // Note: C++ priority queues are max heaps by default, so we invert the comparison
        }
    };

    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int fuel = startFuel;
        if (fuel >= target) {
            return 0;
        }
        int ret = 0;
        priority_queue<int, vector<int>, IntHeap> total; // Use priority queue as max heap

        for (int i = 0; i < stations.size(); ++i) {
            while (fuel < stations[i][0]) {
                if (total.empty()) {
                    return -1;
                }
                fuel += total.top(); // Take out the maximum fuel and use it
                total.pop();
                ret++;
            }
            total.push(stations[i][1]); // Put the fuel of the current station into the total pool for later use
        }

        while (fuel < target) {
            if (total.empty()) {
                return -1;
            }
            fuel += total.top();
            total.pop();
            ret++;
        }
        return ret;
    }
};

//1388. Pizza With 3n Slices
class Solution1388 {
public:
    int rob(vector<int>::iterator begin, int n) {
        int choose = n / 3;
        vector<vector<int>> dp(n, vector<int>(choose + 1));
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j <= choose; ++j) {
                dp[i][j] = max(dp[i - 1][j], (i >= 2 ? dp[i - 2][j - 1] : 0) + *(begin+i-1));
            }
        }
        return dp[n-1][choose];
    }

    int maxSizeSlices(vector<int>& slices) {
        int n = slices.size();
        int ans1 = rob(slices.begin() + 1, n);
        int ans2 = rob(slices.begin(), n);
        return max(ans1, ans2);
    }
};


#endif //NEETCODE150_HEAP_PRIORITYQUEUE_H
