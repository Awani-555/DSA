#include <iostream>
#include <stack>
#include <vector>
using namespace std;

vector<int> prevGreater(vector<int> &arr) {
    int n = arr.size();
    vector<int> ans(n, -1);
    stack<int> st;

    for (int i = 0; i < n; i++) {
        int curr = arr[i];

        // Pop all smaller or equal elements (they can't be previous greater)
        while (!st.empty() && st.top() <= curr) {
            st.pop();
        }

        // If stack not empty, top is previous greater
        if (!st.empty()) {
            ans[i] = st.top();
        }

        // Push current element for future elements to use
        st.push(curr);
    }

    return ans;
}

int main() {
    vector<int> arr = {4, 5, 2, 10, 8};
    vector<int> result = prevGreater(arr);

    cout << "Previous greater elements: ";
    for (int x : result) cout << x << " ";
    cout << endl;

    return 0;
}
