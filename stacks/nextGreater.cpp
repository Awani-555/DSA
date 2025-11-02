#include <iostream>
#include <stack>
#include <vector>
using namespace std;

vector<int> nextGreater(vector<int> &arr) {
    int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> st;

    for (int i = n - 1; i >= 0; i--) {
        int curr = arr[i];

        // Pop all smaller elements
        while (!st.empty() && st.top() <= curr) {
            st.pop();
        }

        // If stack not empty, top is next greater
        if (!st.empty()) {
            ans[i] = st.top();
        }

        // Push current element
        st.push(curr);
    }

    return ans;
}

int main() {
    vector<int> arr = {4, 5, 2, 10, 8};
    vector<int> result = nextGreater(arr);

    cout << "Next greater elements: ";
    for (int x : result) cout << x << " ";
    cout << endl;

    return 0;
}
