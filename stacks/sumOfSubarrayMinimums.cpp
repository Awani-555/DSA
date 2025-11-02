#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/*
====================================================================================================
   PROBLEM: Sum of Subarray Minimums
----------------------------------------------------------------------------------------------------
   Given an array, find the sum of the minimum value of all subarrays.
====================================================================================================
*/

/*
----------------------------------------------------------------------------------------------------
  BRUTE FORCE APPROACH
----------------------------------------------------------------------------------------------------
  Idea:
   1. Generate every possible subarray.
   2. Find the minimum of that subarray.
   3. Add it to the total sum.

  Time Complexity: O(n^3)   --> three nested loops
  Space Complexity: O(1)    --> no extra space
*/
int sumSubarrayMinsBrute(vector<int>& arr) {
    int n = arr.size();
    long long sum = 0;
    const int MOD = 1e9 + 7;

    // Step 1: Loop over start of subarray
    for (int i = 0; i < n; i++) {
        // Step 2: Loop over end of subarray
        for (int j = i; j < n; j++) {
            int mini = arr[i];
            // Step 3: Find minimum in this subarray
            for (int k = i; k <= j; k++) {
                mini = min(mini, arr[k]);
            }
            // Step 4: Add minimum to sum
            sum = (sum + mini) % MOD;
        }
    }
    return (int)sum;
}

/*
----------------------------------------------------------------------------------------------------
  BETTER APPROACH
----------------------------------------------------------------------------------------------------
  Idea:
   1. For each element, find how many subarrays it is the minimum in.
   2. Count how far we can go left and right until a smaller element appears.
   3. Multiply element value by left count * right count and add to sum.

  Time Complexity: O(n^2)
  Space Complexity: O(n) (for counting)
*/
int sumSubarrayMinsBetter(vector<int>& arr) {
    int n = arr.size();
    long long sum = 0;
    const int MOD = 1e9 + 7;

    for (int i = 0; i < n; i++) {
        int left = 1, right = 1;

        // Count elements to the left until smaller
        int j = i - 1;
        while (j >= 0 && arr[j] > arr[i]) { left++; j--; }

        // Count elements to the right until smaller or equal
        j = i + 1;
        while (j < n && arr[j] >= arr[i]) { right++; j++; }

        sum = (sum + (1LL * arr[i] * left * right) % MOD) % MOD;
    }
    return (int)sum;
}

/*
----------------------------------------------------------------------------------------------------
  OPTIMAL APPROACH (MONOTONIC STACK)
----------------------------------------------------------------------------------------------------
  Idea:
   1. Use a stack to quickly find next smaller element (NSE) for every element.
   2. Use another stack to find previous smaller element (PSE) for every element.
   3. Contribution of arr[i] = arr[i] * (i - PSE[i]) * (NSE[i] - i)
      -> counts all subarrays where arr[i] is the minimum.
   4. Sum all contributions modulo 1e9+7.

  Time Complexity: O(n)
  Space Complexity: O(n)
*/

vector<int> nextSmallerElement(vector<int>& arr, int n) {
    stack<int> s;
    s.push(-1);            // -1 indicates no smaller element
    vector<int> ans(n);

    // Step 1: Traverse from right to left
    for (int i = n - 1; i >= 0; i--) {
        // Pop elements greater or equal
        while (s.top() != -1 && arr[s.top()] >= arr[i]) s.pop();
        ans[i] = s.top();   // Next smaller index or -1
        s.push(i);          // Push current index
    }
    return ans;
}

vector<int> prevSmallerElement(vector<int>& arr, int n) {
    stack<int> s;
    s.push(-1);            // -1 indicates no smaller element
    vector<int> ans(n);

    // Step 1: Traverse from left to right
    for (int i = 0; i < n; i++) {
        // Pop elements greater
        while (s.top() != -1 && arr[s.top()] > arr[i]) s.pop();
        ans[i] = s.top();   // Previous smaller index or -1
        s.push(i);          // Push current index
    }
    return ans;
}

int sumSubarrayMinsOptimal(vector<int>& arr) {
    int n = arr.size();
    long long sum = 0;
    const int MOD = 1e9 + 7;

    vector<int> next = nextSmallerElement(arr, n);
    vector<int> prev = prevSmallerElement(arr, n);

    for (int i = 0; i < n; i++) {
        if (next[i] == -1) next[i] = n;      // if no smaller element, use n
        long long left = i - prev[i];        // distance to previous smaller
        long long right = next[i] - i;       // distance to next smaller
        sum = (sum + (arr[i] * left * right) % MOD) % MOD;
    }

    return (int)sum;
}

/* MAIN FUNCTION */
int main() {
    vector<int> arr = {3, 1, 2, 4};

    cout << "Brute Force: " << sumSubarrayMinsBrute(arr) << "\n";
    cout << "Better Approach: " << sumSubarrayMinsBetter(arr) << "\n";
    cout << "Optimal Approach: " << sumSubarrayMinsOptimal(arr) << "\n";

    return 0;
}

