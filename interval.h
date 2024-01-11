//
// Created by Wei on 12/8/23.
//

#ifndef NEETCODE150_INTERVAL_H
#define NEETCODE150_INTERVAL_H

#include "common.h"
//57. Insert Interval
class Solution57 {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        int n = intervals.size();
        int i = 0;
        while (i < n) {
            if (intervals[i][1] < newInterval[0]) {
                result.push_back(intervals[i]);
            }
            else if (intervals[i][0] <= newInterval[1]) {
                newInterval[0] = min(intervals[i][0], newInterval[0]);
                newInterval[1] = max(intervals[i][1], newInterval[1]);
            }
            else {
                result.push_back(newInterval);
                copy(intervals.begin() + i, intervals.end(), back_inserter(result));
                return result;
            }
            i++;
        }
        result.push_back(newInterval);
        return result;
    }
};

//56. Merge Intervals
class Solution56 {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> result;
        sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b){
            return a[0] < b[0];
        });
        for (const auto& interval: intervals) {
            if (result.empty() || interval[0] > result.back()[1]) {
                result.push_back(interval);
            }
            else {
                result.back()[1] = max(result.back()[1], interval[1]);
            }
        }
        return result;
    }
};

//435. Non-overlapping Intervals
class Solution435 {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b){
            return a[0] < b[0];
        });
        int result = 0;
        int preEnd = intervals[0][1];
        for (const auto& interval: intervals) {
            if (interval[0] >= preEnd) {
                preEnd = interval[1];
            }
            else {
                preEnd = min(preEnd, interval[1]);
                result++;
            }
        }
        return result-1;
    }
};

//920 meeting rooms
class Solution920 {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return true;
        }

        sort(intervals.begin(), intervals.end());
        for (int i = 0; i < intervals.size() - 1; i++) {
            if (intervals[i][1] > intervals[i + 1][0]) {
                return false;
            }
        }
        return true;
    }
};

//253 meeting rooms 2
class Solution253 {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        // sort intervals by start time
        sort(intervals.begin(), intervals.end());

        // min heap to track min end time of merged intervals
        priority_queue<int, vector<int>, greater<int>> pq;
        pq.push(intervals[0][1]);

        for (int i = 1; i < intervals.size(); i++) {
            // compare curr start w/ earliest end time, if no overlap then pop
            if (intervals[i][0] >= pq.top()) {
                pq.pop();
            }
            // add new room (will replace/be same size if above was true)
            pq.push(intervals[i][1]);
        }

        return pq.size();
    }
};

//1851. Minimum Interval to Include Each Query
class Solution1851 {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        vector<int> sortedQueries = queries;

        // [size of interval, end of interval]
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        // {query -> size of interval}
        unordered_map<int, int> m;

        // also need only valid intervals so sort by start time & sort queries
        sort(intervals.begin(), intervals.end());
        sort(sortedQueries.begin(), sortedQueries.end());

        vector<int> result;

        int i = 0;
        for (int j = 0; j < sortedQueries.size(); j++) {
            int query = sortedQueries[j];

            while (i < intervals.size() && intervals[i][0] <= query) {
                int left = intervals[i][0];
                int right = intervals[i][1];
                pq.push({right - left + 1, right});
                i++;
            }

            while (!pq.empty() && pq.top().second < query) {
                pq.pop();
            }

            if (!pq.empty()) {
                m[query] = pq.top().first;
            } else {
                m[query] = -1;
            }
        }

        for (int j = 0; j < queries.size(); j++) {
            result.push_back(m[queries[j]]);
        }
        return result;
    }
};


#endif //NEETCODE150_INTERVAL_H
