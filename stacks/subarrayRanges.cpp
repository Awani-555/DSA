#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:

    /*
    ================================================================================================
    NEXT SMALLER ELEMENT (for subarray minimums)
    -----------------------------------------------------------------------------------------------
    Idea:
    - For each element, find the index of the next element smaller than it.
    - Traverse from right to left.
    - Use a stack to keep indices of potential next smaller elements.
    - If the stack top is greater or equal, pop it. The remaining top is the next smaller.
    
    Time Complexity: O(n) -> Each element pushed and popped at most once.
    Space Complexity: O(n) -> Stack + answer array.
    ================================================================================================
    */
    vector<int> nextSmallerElement(vector<int> &arr, int n) {
        stack<int> s;
        s.push(-1); // -1 indicates no smaller element exists
        vector<int> ans(n);

        for (int i = n - 1; i >= 0; i--) {
            while (s.top() != -1 && arr[s.top()] >= arr[i])
                s.pop();
            ans[i] = s.top(); // store index of next smaller element
            s.push(i);        // push current index
        }
        return ans;
    }

    /*
    ================================================================================================
    PREVIOUS SMALLER ELEMENT (for subarray minimums)
    -----------------------------------------------------------------------------------------------
    Idea:
    - Similar to next smaller element but traverse from left to right.
    - Find the previous smaller element for each index.
    ================================================================================================
    */
    vector<int> prevSmallerElement(vector<int> &arr, int n) {
        stack<int> s;
        s.push(-1); // -1 indicates no previous smaller
        vector<int> ans(n);

        for (int i = 0; i < n; i++) {
            while (s.top() != -1 && arr[s.top()] > arr[i])
                s.pop();
            ans[i] = s.top(); // store index of previous smaller
            s.push(i);
        }
        return ans;
    }

    /*
    ================================================================================================
    SUM OF SUBARRAY MINIMUMS
    -----------------------------------------------------------------------------------------------
    Idea:
    - Each element arr[i] contributes to multiple subarrays as the minimum.
    - Contribution formula:
        left = i - prev[i]      (number of subarrays ending at i where arr[i] is min)
        right = next[i] - i     (number of subarrays starting at i where arr[i] is min)
        total contribution = arr[i] * left * right
    - Sum contributions of all elements to get total sum.
    ================================================================================================
    */
    long long sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        long long sum = 0;

        vector<int> next = nextSmallerElement(arr, n);
        vector<int> prev = prevSmallerElement(arr, n);

        for (int i = 0; i < n; i++) {
            if (next[i] == -1) next[i] = n;  // If no smaller element on right, use n
            long long left = i - prev[i];
            long long right = next[i] - i;
            sum += 1LL * arr[i] * left * right;
        }

        return sum;
    }

    /*
    ================================================================================================
    NEXT GREATER ELEMENT (for subarray maximums)
    -----------------------------------------------------------------------------------------------
    Idea:
    - Similar to next smaller element but find next greater element.
    ================================================================================================
    */
    vector<int> nextGreaterElement(vector<int> &arr, int n) {
        stack<int> s;
        s.push(-1);
        vector<int> ans(n);

        for (int i = n - 1; i >= 0; i--) {
            while (s.top() != -1 && arr[s.top()] <= arr[i])
                s.pop();
            ans[i] = s.top();
            s.push(i);
        }
        return ans;
    }

    /*
    ================================================================================================
    PREVIOUS GREATER ELEMENT (for subarray maximums)
    -----------------------------------------------------------------------------------------------
    Idea:
    - Similar to prev smaller element but find previous greater element.
    ================================================================================================
    */
    vector<int> prevGreaterElement(vector<int> &arr, int n) {
        stack<int> s;
        s.push(-1);
        vector<int> ans(n);

        for (int i = 0; i < n; i++) {
            while (s.top() != -1 && arr[s.top()] < arr[i])
                s.pop();
            ans[i] = s.top();
            s.push(i);
        }
        return ans;
    }

    /*
    ================================================================================================
    SUM OF SUBARRAY MAXIMUMS
    -----------------------------------------------------------------------------------------------
    Idea:
    - Same as subarray minimums but use next/prev greater elements.
    ================================================================================================
    */
    long long sumSubarrayMaxs(vector<int>& arr) {
        int n = arr.size();
        long long sum = 0;

        vector<int> next = nextGreaterElement(arr, n);
        vector<int> prev = prevGreaterElement(arr, n);

        for (int i = 0; i < n; i++) {
            if (next[i] == -1) next[i] = n;
            long long left = i - prev[i];
            long long right = next[i] - i;
            sum += 1LL * arr[i] * left * right;
        }

        return sum;
    }

    /*
    ================================================================================================
    SUBARRAY RANGES (OPTIMAL)
    -----------------------------------------------------------------------------------------------
    Idea:
    - Range of subarray = max - min.
    - Sum of ranges for all subarrays = sum(max of subarrays) - sum(min of subarrays)
    - Use monotonic stacks to calculate sums efficiently.
    ================================================================================================
    */
    long long subArrayRanges(vector<int>& nums) {
        long long sumMax = sumSubarrayMaxs(nums);
        long long sumMin = sumSubarrayMins(nums);
        return sumMax - sumMin;
    }
};

/* =======================
        MAIN
======================= */
int main() {
    Solution sol;
    vector<int> nums = {1, 3, 2};

    cout << "Sum of Subarray Ranges: " << sol.subArrayRanges(nums) << endl;
    return 0;
}
