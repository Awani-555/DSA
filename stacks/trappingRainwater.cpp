#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:

    /*
    ====================================================================================
        1. BRUTE FORCE APPROACH
    ====================================================================================
    Idea:
      - For each bar, find the tallest bar on its left and right.
      - Water trapped on top of this bar = min(maxLeft, maxRight) - height[i]

      Critical Insight:
        // Very simple but slow. Recomputing left & right max for every bar causes O(n^2) time.

    Complexity:
      - Time: O(n^2)
      - Space: O(1)
    */
    int trapBrute(vector<int>& height) {
        int n = height.size();
        int trapped = 0;

        for (int i = 0; i < n; i++) {
            int maxLeft = 0, maxRight = 0;

            for (int j = 0; j <= i; j++) maxLeft = max(maxLeft, height[j]);
            for (int j = i; j < n; j++) maxRight = max(maxRight, height[j]);

            trapped += min(maxLeft, maxRight) - height[i];
        }

        return trapped;
    }

    /*
    ====================================================================================
        2. BETTER APPROACH (PRECOMPUTE LEFT & RIGHT MAX)
    ====================================================================================
    Idea:
      - Precompute maximum height to the left and right for each bar.
      - Water trapped = min(leftMax[i], rightMax[i]) - height[i]

      Critical Insight:
        // Avoids repeated work. Left & right max arrays make it O(n) time.

    Complexity:
      - Time: O(n)
      - Space: O(n)
    */
    int trapBetter(vector<int>& height) {
        int n = height.size();
        vector<int> leftMax(n), rightMax(n);
        int trapped = 0;

        leftMax[0] = height[0];
        for (int i = 1; i < n; i++) leftMax[i] = max(leftMax[i - 1], height[i]);

        rightMax[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; i--) rightMax[i] = max(rightMax[i + 1], height[i]);

        for (int i = 0; i < n; i++)
            trapped += min(leftMax[i], rightMax[i]) - height[i];

        return trapped;
    }

    /*
    ====================================================================================
        3. OPTIMAL APPROACH (MONOTONIC STACK)
    ====================================================================================
    Idea:
      - Use a stack to keep indices of bars that are waiting for a boundary to trap water.
      - When a taller bar is found, we can calculate water for bars in between.

      Critical Insight:
        // Efficient! Each bar is pushed & popped at most once. 
        // O(n) time, O(n) space. Stack helps find next greater bar for trapping water.

    Complexity:
      - Time: O(n)
      - Space: O(n)
    */
    int trapOptimal(vector<int>& height) {
        int n = height.size();
        stack<int> st;
        int trappedWater = 0;

        for (int i = 0; i < n; i++) {
            while (!st.empty() && height[i] > height[st.top()]) {
                int top = st.top();
                st.pop();
                if (st.empty()) break;

                int distance = i - st.top() - 1;
                int boundedHeight = min(height[i], height[st.top()]) - height[top];
                trappedWater += distance * boundedHeight;
            }
            st.push(i);
        }

        return trappedWater;
    }
};
// ================= MAIN FUNCTION =================
int main() {
    Solution sol;

    vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};

    cout << "Brute Force Water Trapped: " << sol.trapBrute(height) << endl;
    cout << "Better Approach Water Trapped: " << sol.trapBetter(height) << endl;
    cout << "Optimal Stack Approach Water Trapped: " << sol.trapOptimal(height) << endl;

    return 0;
}