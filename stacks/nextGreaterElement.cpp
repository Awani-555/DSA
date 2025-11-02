#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;

/*
====================================================================================================
   PROBLEM: Next Greater Element I
----------------------------------------------------------------------------------------------------
   You are given two integer arrays nums1 and nums2, where nums1 is a subset of nums2.
   For each element in nums1, find the next greater element in nums2.

   Example:
       nums1 = [4,1,2]
       nums2 = [1,3,4,2]
       Output: [-1,3,-1]
====================================================================================================
*/


/*
----------------------------------------------------------------------------------------------------
  BRUTE FORCE APPROACH
----------------------------------------------------------------------------------------------------
Idea:
   * For every element in nums1, find its index in nums2.
   * From that index, scan to the right to find the next greater element.
   * If no greater element is found, return -1 for that element.

Steps:
   1. Iterate over each element of nums1.
   2. Find where it occurs in nums2.
   3. Scan right in nums2 to find the first element greater than it.

Time Complexity: O(n1 * n2)
   For each element of nums1 (n1), we may scan the entire nums2 (n2).
Space Complexity: O(1)
   Only uses constant extra space.
*/

vector<int> nextGreaterElementBrute(vector<int>& nums1, vector<int>& nums2) {
    vector<int> ans;

    for (int i = 0; i < nums1.size(); i++) {
        int current = nums1[i];
        int nextGreater = -1;
        bool found = false;

        // find current element in nums2
        for (int j = 0; j < nums2.size(); j++) {
            if (nums2[j] == current) {
                found = true;
            }
            // once found, check next greater
            else if (found && nums2[j] > current) {
                nextGreater = nums2[j];
                break;
            }
        }
        ans.push_back(nextGreater);
    }

    return ans;
}


/*
----------------------------------------------------------------------------------------------------
  BETTER APPROACH (Using Hash Map)
----------------------------------------------------------------------------------------------------
Idea:
   * Instead of scanning nums2 every time, store the index of each element in a hash map.
   * For each element in nums1, jump directly to its index in nums2 and scan right.

Steps:
   1. Build a map: num -> index in nums2.
   2. For each element in nums1:
        - Start from map[num] + 1
        - Move right until you find a greater element or reach the end.

Time Complexity: O(n1 * n2) in the worst case
   Still can scan linearly, but avoids repeated index search.
Space Complexity: O(n2)
   Extra hash map to store positions.
*/

vector<int> nextGreaterElementBetter(vector<int>& nums1, vector<int>& nums2) {
    vector<int> ans;
    unordered_map<int, int> indexMap;

    // store index of each number in nums2
    for (int i = 0; i < nums2.size(); i++) {
        indexMap[nums2[i]] = i;
    }

    // find next greater for each number in nums1
    for (int num : nums1) {
        int idx = indexMap[num];
        int nextGreater = -1;

        for (int j = idx + 1; j < nums2.size(); j++) {
            if (nums2[j] > num) {
                nextGreater = nums2[j];
                break;
            }
        }
        ans.push_back(nextGreater);
    }

    return ans;
}


/*
----------------------------------------------------------------------------------------------------
  OPTIMAL APPROACH (Monotonic Stack)
----------------------------------------------------------------------------------------------------
Idea:
   * Traverse nums2 from RIGHT to LEFT using a stack.
   * Maintain a decreasing stack (top has the next greater element).
   * For each element:
        - Pop all smaller or equal elements.
        - If the stack is empty → no next greater element.
        - Otherwise, top of the stack is the next greater element.
        - Push the current element.
   * Store the result in a hash map: num -> next greater
   * Finally, build answers for nums1 using this map.

Time Complexity: O(n1 + n2)
   Each element in nums2 is pushed & popped at most once.
Space Complexity: O(n2)
   Stack + hash map.
*/

vector<int> nextGreaterElementOptimal(vector<int>& nums1, vector<int>& nums2) {
    unordered_map<int, int> nextGreater;  // stores num -> next greater
    stack<int> st;                        // stack for decreasing elements

    // go from right to left
    for (int i = nums2.size() - 1; i >= 0; i--) {
        int curr = nums2[i];

        // remove smaller or equal elements
        while (!st.empty() && st.top() <= curr) {
            st.pop();
        }

        // if stack empty, no next greater
        nextGreater[curr] = st.empty() ? -1 : st.top();

        // push current element
        st.push(curr);
    }

    // build result for nums1
    vector<int> ans;
    for (int num : nums1) {
        ans.push_back(nextGreater[num]);
    }

    return ans;
}


/* ================================================================
   HELPER FUNCTION
================================================================ */
void printVector(vector<int>& arr) {
    cout << "[ ";
    for (int x : arr) cout << x << " ";
    cout << "]\n";
}


/* -------------------------------------------------------------------

   MAIN FUNCTION
------------------------------------------------------------------- */
int main() {
    vector<int> nums1 = {4, 1, 2};
    vector<int> nums2 = {1, 3, 4, 2};

    cout << "------------------------------------------------------------\n";
    cout << "  BRUTE FORCE APPROACH\n";
    cout << "------------------------------------------------------------\n";
    vector<int> bruteAns = nextGreaterElementBrute(nums1, nums2);
    printVector(bruteAns);

    cout << "\n------------------------------------------------------------\n";
    cout << "  BETTER APPROACH (Using Hash Map)\n";
    cout << "------------------------------------------------------------\n";
    vector<int> betterAns = nextGreaterElementBetter(nums1, nums2);
    printVector(betterAns);

    cout << "\n------------------------------------------------------------\n";
    cout << "  OPTIMAL APPROACH (Monotonic Stack)\n";
    cout << "------------------------------------------------------------\n";
    vector<int> optimalAns = nextGreaterElementOptimal(nums1, nums2);
    printVector(optimalAns);

    return 0;
}
