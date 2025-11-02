#include <iostream>
#include <stack>
#include <vector>
using namespace std;

vector<int> prevSmaller(vector<int> &arr) {
    int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> st;

    for (int i = 0; i < n; i++) {
        int curr = arr[i];

        // Pop all greater or equal elements
        while (!st.empty() && st.top() >= curr) {
            st.pop();
        }

        // If stack not empty, top is previous smaller
        if (!st.empty()) {
            ans[i] = st.top();
        }

        // Push current element for future use
        st.push(curr);
    }

    return ans;
}

int main() {
    vector<int> arr = {4, 5, 2, 10, 8};
    vector<int> result = prevSmaller(arr);

    cout << "Previous smaller elements: ";
    for (int x : result) cout << x << " ";
    cout << endl;

    return 0;
}
