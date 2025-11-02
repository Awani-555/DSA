#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/*
====================================================================================================
   PROBLEM: Next Greater Element II (Circular Array)
----------------------------------------------------------------------------------------------------
   Given a circular array nums, for each element find the next greater element in the array.
   The next greater element of a number x is the first greater number 
   to its right (considering the array circularly).

   Example:
       nums = [1,2,1]
       Output = [2,-1,2]
====================================================================================================
*/

/*
----------------------------------------------------------------------------------------------------
  BRUTE FORCE APPROACH
----------------------------------------------------------------------------------------------------
  → For each element:
       1. Look to the right to find the next greater element.
       2. If not found, wrap around (circular) and continue search.
       3. If still not found, put -1.

  Time:  O(n^2)
  Space: O(1)
*/

vector<int> nextGreaterElementsBrute(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n, -1);

    for (int i = 0; i < n; i++) {
        // check next n-1 elements (circularly)
        for (int j = 1; j < n; j++) {
            int nextIdx = (i + j) % n;
            if (nums[nextIdx] > nums[i]) {
                ans[i] = nums[nextIdx];
                break;
            }
        }
    }

    return ans;
}

/*
----------------------------------------------------------------------------------------------------
  BETTER APPROACH (Simulate 2 passes)
----------------------------------------------------------------------------------------------------
  → Instead of using % in every step, simulate the circular behavior 
    by looping through the array twice.
  → For each element in the second pass, check for the next greater
    using elements ahead in the circular sense.

  Time:  O(n^2) in worst case (nested loop)
  Space: O(n) for result
*/

vector<int> nextGreaterElementsBetter(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n, -1);

    // loop twice to simulate circular array
    for (int i = 0; i < 2 * n; i++) {
        int curr = nums[i % n];

        // check forward only if not found yet
        for (int j = i + 1; j < 2 * n; j++) {
            if (nums[j % n] > curr) {
                ans[i % n] = nums[j % n];
                break;
            }
        }
    }

    return ans;
}

/*
----------------------------------------------------------------------------------------------------
  OPTIMAL APPROACH (Using Stack)
----------------------------------------------------------------------------------------------------
  → Use a stack to store possible next greater elements.
  → Traverse array twice (from right to left) to handle circular behavior.
  → For each element:
       - Pop all smaller or equal elements from the stack.
       - If stack not empty → top is the next greater.
       - Push current element.

  Time:  O(n)
  Space: O(n)
*/

vector<int> nextGreaterElementsOptimal(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n, -1);
    stack<int> st;

    // traverse array twice
    for (int i = 2 * n - 1; i >= 0; i--) {
        int curr = nums[i % n];

        // remove smaller or equal elements
        while (!st.empty() && st.top() <= curr) {
            st.pop();
        }

        // if stack has next greater
        if (!st.empty()) {
            ans[i % n] = st.top();
        }

        // push current element
        st.push(curr);
    }

    return ans;
}

/* Helper function to print vector */
void printVector(vector<int>& arr) {
    cout << "[ ";
    for (int x : arr) cout << x << " ";
    cout << "]\n";
}

/* MAIN FUNCTION */
int main() {
    vector<int> nums = {1, 2, 1};

    cout << "-------------------------------------------\n";
    cout << "BRUTE FORCE APPROACH:\n";
    vector<int> brute = nextGreaterElementsBrute(nums);
    printVector(brute);

    cout << "\n-------------------------------------------\n";
    cout << "BETTER APPROACH:\n";
    vector<int> better = nextGreaterElementsBetter(nums);
    printVector(better);

    cout << "\n-------------------------------------------\n";
    cout << "OPTIMAL APPROACH (Using Stack):\n";
    vector<int> optimal = nextGreaterElementsOptimal(nums);
    printVector(optimal);

    return 0;
}
