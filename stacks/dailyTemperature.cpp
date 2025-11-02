#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/*
====================================================================================================
   PROBLEM: Daily Temperatures
----------------------------------------------------------------------------------------------------
   Given a list of daily temperatures, for each day, find how many days you have to wait until a 
   warmer temperature. If there is no future warmer day, use 0.
====================================================================================================
*/

/*
----------------------------------------------------------------------------------------------------
  BRUTE FORCE APPROACH
----------------------------------------------------------------------------------------------------
  Idea:
   - For each day, scan all future days until a warmer temperature is found.
   - Store the number of days waited.
   
  Time Complexity: O(n^2)
  Space Complexity: O(1)
*/

vector<int> dailyTemperaturesBrute(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> ans(n, 0);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (temperatures[j] > temperatures[i]) {
                ans[i] = j - i;
                break;  // stop at first warmer day
            }
        }
    }
    return ans;
}


/*
----------------------------------------------------------------------------------------------------
  OPTIMAL APPROACH (MONOTONIC STACK)
----------------------------------------------------------------------------------------------------
  Idea:
   - Traverse from right to left.
   - Use a stack to store indices of days with strictly warmer temperatures.
   - Pop indices of temperatures <= current.
   - Top of stack gives the next warmer day.

  Time Complexity: O(n)
  Space Complexity: O(n)
*/

vector<int> dailyTemperaturesOptimal(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> ans(n, 0);
    stack<int> st; // stores indices

    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && temperatures[st.top()] <= temperatures[i]) {
            st.pop();
        }
        if (!st.empty()) ans[i] = st.top() - i;
        st.push(i);
    }

    return ans;
}

/* MAIN FUNCTION */
int main() {
    vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};

    cout << "Brute Force: ";
    for (int x : dailyTemperaturesBrute(temperatures)) cout << x << " ";
    cout << "\n";

    cout << "Better/Optimal Approach: ";
    for (int x : dailyTemperaturesOptimal(temperatures)) cout << x << " ";
    cout << "\n";

    return 0;
}
