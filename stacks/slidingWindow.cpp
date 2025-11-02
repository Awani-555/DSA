#include <iostream>
#include <vector>
#include <deque>
#include <set>
using namespace std;

class Solution {
public:

    /*
    ============================================
    BRUTE FORCE APPROACH
    ============================================
    Idea:
      - For each window of size k, check every element in the window.
      - Keep track of the maximum value in that window.
      - Slide the window by one and repeat.

    Steps:
      1. Loop from i = 0 to n-k (start index of each window).
      2. For each window, loop through k elements to find the max.
      3. Store the max in result vector.
    
    Time Complexity: O(n*k)  -> Nested loops
    Space Complexity: O(1)   -> No extra data structures
    */
    vector<int> maxSlidingWindowBrute(vector<int>& nums, int k) {
        vector<int> result;
        int n = nums.size();

        for(int i = 0; i <= n - k; i++) {
            int maxVal = nums[i]; // Start with first element in the window
            for(int j = i; j < i + k; j++) {
                maxVal = max(maxVal, nums[j]); // Compare each element in the window
            }
            result.push_back(maxVal); // Store max for this window
        }
        return result;
    }

    /*
    ============================================
    BETTER APPROACH (Using Multiset / Balanced BST)
    ============================================
    Idea:
      - Keep all elements of current window in a multiset (balanced BST).
      - Multiset always keeps elements sorted.
      - The largest element can be accessed in O(1) via rbegin().
      - Remove elements leaving the window and insert new elements.

    Steps:
      1. Loop through the array.
      2. Insert current element into multiset.
      3. If window size >= k:
          - Get max element from multiset (rbegin()).
          - Remove the element that is leaving the window.
    
    Time Complexity: O(n*log k)  -> Each insertion/deletion is O(log k)
    Space Complexity: O(k)        -> Multiset stores k elements max
    */
    vector<int> maxSlidingWindowBetter(vector<int>& nums, int k) {
        vector<int> result;
        multiset<int> window; // Automatically sorted

        for(int i = 0; i < nums.size(); i++) {
            window.insert(nums[i]); // Add current element to the window

            if(i >= k - 1) {
                result.push_back(*window.rbegin()); // Max is last element
                window.erase(window.find(nums[i - k + 1])); // Remove element leaving the window
            }
        }
        return result;
    }

    /*
    ============================================
    OPTIMAL APPROACH (Using Deque)
    ============================================
    Idea:
      - Use a deque to store **indices** of elements.
      - Maintain two properties:
          1. Indices in deque are always in the current window.
          2. Elements corresponding to indices are in **descending order**.
      - Front of deque always gives max element for current window.

    Steps:
      1. Loop through each element of the array.
      2. Remove indices that are out of the current window from front.
      3. Remove elements smaller than current from back (they can't be max in future windows).
      4. Add current index to the back.
      5. If we have at least k elements processed, add the element at deque front to result.

    Time Complexity: O(n) -> Each element is added and removed at most once
    Space Complexity: O(k) -> Deque stores at most k elements
    */
    vector<int> maxSlidingWindowOptimal(vector<int>& nums, int k) {
        deque<int> dq; // Stores indices
        vector<int> result;

        for(int i = 0; i < nums.size(); i++) {
            // Step 2: Remove indices outside window
            if(!dq.empty() && dq.front() == i - k) dq.pop_front();

            // Step 3: Remove smaller elements from back
            while(!dq.empty() && nums[i] > nums[dq.back()]) dq.pop_back();

            // Step 4: Add current index
            dq.push_back(i);

            // Step 5: Append max to result when window is ready
            if(i >= k - 1) result.push_back(nums[dq.front()]);
        }
        return result;
    }
};

// ========================= MAIN FUNCTION =========================
int main() {
    Solution sol;
    vector<int> nums = {1,3,-1,-3,5,3,6,7};
    int k = 3;

    // Brute Force
    vector<int> resBrute = sol.maxSlidingWindowBrute(nums, k);
    cout << "Brute Force: ";
    for(int val : resBrute) cout << val << " ";
    cout << endl;

    // Better Approach
    vector<int> resBetter = sol.maxSlidingWindowBetter(nums, k);
    cout << "Better Approach: ";
    for(int val : resBetter) cout << val << " ";
    cout << endl;

    // Optimal Approach
    vector<int> resOptimal = sol.maxSlidingWindowOptimal(nums, k);
    cout << "Optimal Approach: ";
    for(int val : resOptimal) cout << val << " ";
    cout << endl;

    return 0;
}
