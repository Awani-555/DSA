#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

/*
====================================================================================================
   PROBLEM: Largest Rectangle in Histogram
----------------------------------------------------------------------------------------------------
   Given heights of bars in a histogram, find the area of the largest rectangle.
====================================================================================================
*/

/*
----------------------------------------------------------------------------------------------------
  NAIVE / BRUTE FORCE APPROACH
----------------------------------------------------------------------------------------------------
  Idea:
   - For each bar, expand left and right until a smaller bar is found.
   - Calculate width * height for each bar.
   - Take the maximum area.

  Time Complexity: O(n^2)
  Space Complexity: O(1)
*/

int largestRectangleAreaBrute(vector<int>& heights) {
    int n = heights.size();
    int maxi = 0;

    for (int i = 0; i < n; i++) {
        int l = heights[i];
        int left = i, right = i;

        // Expand left
        while (left > 0 && heights[left-1] >= l) left--;
        // Expand right
        while (right < n-1 && heights[right+1] >= l) right++;

        int b = right - left + 1;  // width
        int area = l * b;
        maxi = max(maxi, area);
    }
    return maxi;
}

/*
----------------------------------------------------------------------------------------------------
  BETTER APPROACH (Precompute NS/PS using arrays, but still O(n^2) in some implementations)
----------------------------------------------------------------------------------------------------
  Idea:
   - Precompute Next Smaller to Right (NSR) and Previous Smaller to Left (PSL) indices using loops.
   - Calculate width using NSR[i] - PSL[i] - 1.
   - This avoids inner scanning for each bar.

  Time Complexity: O(n^2) worst case if NS/PS computed naively
  Space Complexity: O(n) for NSR and PSL
*/

int largestRectangleAreaBetter(vector<int>& heights) {
    int n = heights.size();
    vector<int> next(n, n);  // default next smaller index
    vector<int> prev(n, -1); // default previous smaller index

    // Compute Next Smaller to Right
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (heights[j] < heights[i]) {
                next[i] = j;
                break;
            }
        }
    }

    // Compute Previous Smaller to Left
    for (int i = n-1; i >= 0; i--) {
        for (int j = i-1; j >= 0; j--) {
            if (heights[j] < heights[i]) {
                prev[i] = j;
                break;
            }
        }
    }

    int maxi = 0;
    for (int i = 0; i < n; i++) {
        int width = next[i] - prev[i] - 1;
        int area = heights[i] * width;
        maxi = max(maxi, area);
    }
    return maxi;
}

/*
----------------------------------------------------------------------------------------------------
  OPTIMAL APPROACH (MONOTONIC STACK)
----------------------------------------------------------------------------------------------------
  Idea:
   - Use stacks to compute Next Smaller to Right (NSR) and Previous Smaller to Left (PSL) in O(n)
   - Width = NSR[i] - PSL[i] - 1
   - Area = height * width
   - Maximum area among all bars is the answer

  Time Complexity: O(n)
  Space Complexity: O(n)
  
  Critical Insights:
   1. Stack stores indices of increasing bars → popping gives first smaller element.
   2. Width formula ensures rectangle spans all bars taller than current bar.
*/

vector<int> nextSmallerElement(vector<int> &arr, int n) {
    stack<int> s;
    s.push(-1);
    vector<int> ans(n);

    for (int i = n-1; i >= 0; i--) {
        while (s.top() != -1 && arr[s.top()] >= arr[i]) s.pop();
        ans[i] = s.top();
        s.push(i);
    }
    return ans;
}

vector<int> prevSmallerElement(vector<int> &arr, int n) {
    stack<int> s;
    s.push(-1);
    vector<int> ans(n);

    for (int i = 0; i < n; i++) {
        while (s.top() != -1 && arr[s.top()] >= arr[i]) s.pop();
        ans[i] = s.top();
        s.push(i);
    }
    return ans;
}

int largestRectangleAreaOptimal(vector<int>& heights) {
    int n = heights.size();
    vector<int> next = nextSmallerElement(heights, n);
    vector<int> prev = prevSmallerElement(heights, n);

    int maxi = 0;
    for (int i = 0; i < n; i++) {
        int l = heights[i];
        if (next[i] == -1) next[i] = n;
        int width = next[i] - prev[i] - 1;
        int area = l * width;
        maxi = max(maxi, area);
    }
    return maxi;
}

/* MAIN FUNCTION */
int main() {
    vector<int> heights = {2,1,5,6,2,3};

    cout << "-------------------------------------------\n";
    cout << "BRUTE FORCE APPROACH: " << largestRectangleAreaBrute(heights) << "\n";

    cout << "-------------------------------------------\n";
    cout << "BETTER APPROACH: " << largestRectangleAreaBetter(heights) << "\n";

    cout << "-------------------------------------------\n";
    cout << "OPTIMAL APPROACH (Stack): " << largestRectangleAreaOptimal(heights) << "\n";

    return 0;
}
