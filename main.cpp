#include "interval.h"
#include "dfs.h"
#include "recursion.h"
#include "greedy.h"
#include "TwoPoints.h"
#include "stack.h"
#include "math&geometry.h"
#include "bitManipulation.h"
#include "slidingWindow.h"
#include "dp.h"
#include "graphs.h"
#include "common.h"


int main() {
    vector<vector<int>> grid = {{1,2,2},{3,8,2},{5,3,5}};
    Solution1631 s;
    cout << s.minimumEffortPath(grid) << endl;
    cout << "Hello, World!" << endl;
    return 0;
}
