#include <iostream>
#include <vector>
#include <climits> // For INT_MIN
#include <stack>
using namespace std;

class Solution {
public:

    // ================= BRUTE FORCE =================
    /*
    Idea:
      - Try every possible triplet (i, j, k) with i < j < k
      - Check if nums[i] < nums[k] < nums[j]
    
    Time Complexity: O(n^3)
    Space Complexity: O(1)
    
    Note:
      - Works for small arrays only
    */
    bool find132patternBrute(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                for (int k = j + 1; k < n; k++) {
                    if (nums[i] < nums[k] && nums[k] < nums[j]) {
                        return true; // Found 132 pattern
                    }
                }
            }
        }
        return false; // No pattern found
    }

    // ================= BETTER APPROACH =================
    /*
    Idea:
      - Fix nums[j] as the middle element
      - Keep track of minimum value before j (nums[i])
      - For each j, check if there exists a nums[k] after j satisfying nums[i] < nums[k] < nums[j]
    
    Time Complexity: O(n^2)
    Space Complexity: O(1)
    
    Note:
      - Faster than brute-force but still not optimal
    */
    bool find132patternBetter(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return false;

        int min_i = nums[0]; // Minimum value before current j
        for (int j = 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                if (min_i < nums[k] && nums[k] < nums[j]) {
                    return true; // Found 132 pattern
                }
            }
            min_i = min(min_i, nums[j]); // Update minimum
        }
        return false;
    }

    // ================= OPTIMAL APPROACH =================
    /*
    Idea:
      - Traverse from right to left
      - Use a stack to store potential nums[j] (middle element of 132)
      - Keep track of 'third' = nums[k] (largest valid number smaller than nums[j])
      - If nums[i] < third, we found the pattern

    Time Complexity: O(n)
    Space Complexity: O(n)

    Critical Insight:
      - Stack stores decreasing elements
      - 'third' keeps track of the largest nums[k] that can form 132
    */
    bool find132patternOptimal(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return false;

        int third = INT_MIN; // This will hold nums[k]
        stack<int> st;       // Stack holds potential nums[j]

        for (int i = n - 1; i >= 0; i--) {
            // If current number is less than third, pattern exists
            if (nums[i] < third) return true;

            // Pop stack elements smaller than current to update third
            while (!st.empty() && nums[i] > st.top()) {
                third = st.top();
                st.pop();
            }

            // Push current number as potential nums[j]
            st.push(nums[i]);
        }

        return false; // No pattern found
    }
};

// ================= MAIN FUNCTION =================
int main() {
    Solution sol;

    vector<int> nums = {3, 1, 4, 2};

    cout << "Brute Force: " 
         << (sol.find132patternBrute(nums) ? "Yes" : "No") << endl;

    cout << "Better Approach: " 
         << (sol.find132patternBetter(nums) ? "Yes" : "No") << endl;

    cout << "Optimal Approach: " 
         << (sol.find132patternOptimal(nums) ? "Yes" : "No") << endl;

    return 0;
}
