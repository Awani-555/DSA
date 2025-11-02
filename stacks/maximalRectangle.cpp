#include <iostream>
#include <vector>
#include <stack>
#include <climits> // For INT_MIN
using namespace std;

class Solution {
public:

    /*
    ------------------------------------------------------------------------------------------------------
        NEXT AND PREVIOUS SMALLER ELEMENTS
    ------------------------------------------------------------------------------------------------------
    Idea:
        * For largest rectangle in histogram, we need the next smaller element (right boundary)
          and previous smaller element (left boundary) for each bar.
        * We use a monotonic stack to efficiently compute these in O(n) time.

    Time Complexity: O(n)
    Space Complexity: O(n)
    */

    vector<int> nextSmallerElement(vector<int> &arr, int n) {
        stack<int> s;
        s.push(-1); // Sentinel value
        vector<int> ans(n);

        for (int i = n - 1; i >= 0; i--) {
            int curr = arr[i];
            while (s.top() != -1 && arr[s.top()] >= curr) s.pop();
            ans[i] = s.top(); // Index of next smaller element or -1 if none
            s.push(i);
        }
        return ans;
    }

    vector<int> prevSmallerElement(vector<int> &arr, int n) {
        stack<int> s;
        s.push(-1); // Sentinel value
        vector<int> ans(n);

        for (int i = 0; i < n; i++) {
            int curr = arr[i];
            while (s.top() != -1 && arr[s.top()] >= curr) s.pop();
            ans[i] = s.top(); // Index of previous smaller element or -1 if none
            s.push(i);
        }
        return ans;
    }

    /*
    ------------------------------------------------------------------------------------------------------
        LARGEST RECTANGLE IN HISTOGRAM
    ------------------------------------------------------------------------------------------------------
    Idea:
        * For each bar, compute the maximum rectangle with height = bar height
          and width = distance between previous smaller and next smaller elements.
        * Use the previously computed next and prev smaller indices.

    Time Complexity: O(n)
    Space Complexity: O(n)
    */
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> next = nextSmallerElement(heights, n);
        vector<int> prev = prevSmallerElement(heights, n);

        int maxi = 0;
        for (int i = 0; i < n; i++) {
            int l = heights[i];
            if (next[i] == -1) next[i] = n; // If no smaller to the right, width goes to end
            int b = next[i] - prev[i] - 1;  // Width of rectangle
            int newArea = l * b;
            maxi = max(maxi, newArea);
        }
        return maxi;
    }

    /*
    ------------------------------------------------------------------------------------------------------
        MAXIMAL RECTANGLE IN 2D BINARY MATRIX
    ------------------------------------------------------------------------------------------------------
    Idea:
        * Treat each row as a histogram of heights of consecutive '1's.
        * For each row, update heights array:
            - If matrix[i][j] == '1', increment height
            - Else, reset to 0
        * Compute largest rectangle for that histogram using largestRectangleArea().
        * Keep track of maximum area across all rows.

    Time Complexity: O(m*n)  (m = rows, n = cols)
    Space Complexity: O(n)   (heights array + stacks)
    */
    int maximalRectangle(vector<vector<char>>& matrix) {
        if(matrix.empty()) return 0;

        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> heights(n, 0);
        int maxArea = 0;

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                heights[j] = (matrix[i][j] == '1') ? heights[j] + 1 : 0;
            }
            maxArea = max(maxArea, largestRectangleArea(heights));
        }

        return maxArea;
    }
};

/*
------------------------------------------------------------------------------------------------------
    CRITICAL INSIGHTS:
    1. Monotonic stack helps us efficiently find next/previous smaller elements in O(n).
    2. Transform 2D maximal rectangle problem into a series of 1D largest rectangle problems.
    3. Using sentinel (-1) simplifies edge cases when no smaller element exists.
------------------------------------------------------------------------------------------------------
*/
int main() {
    Solution sol;

    // Example binary matrix
    vector<vector<char>> matrix = {
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    };

    // Compute maximal rectangle
    int maxArea = sol.maximalRectangle(matrix);

    cout << "Maximum rectangle area of 1's in the matrix: " << maxArea << endl;

    return 0;
}