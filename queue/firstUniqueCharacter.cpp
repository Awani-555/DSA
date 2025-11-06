#include <bits/stdc++.h>
using namespace std;

// ============================================
// PROBLEM: First Unique Character in a String
// ============================================
// Given a string s, find the index of the first
// non-repeating character. If it doesn’t exist, return -1.
//
// Example:
// Input:  "loveleetcode"
// Output: 2   (because 'v' is the first unique character)


// ============================================
// 1. Brute Force Approach
// ============================================
//
// Idea:
// For every character, check if it appears again in the string.
// If it doesn't repeat, return its index.
//
// Time Complexity:  O(N^2)
//      -> For each character, we may scan the entire string again.
// Space Complexity: O(1)
//      -> No extra space used.
//
int firstUniqChar_Brute(string s) {
    for (int i = 0; i < s.size(); i++) {
        bool unique = true;
        for (int j = 0; j < s.size(); j++) {
            if (i != j && s[i] == s[j]) {
                unique = false;
                break;
            }
        }
        if (unique) return i;  // found first non-repeating char
    }
    return -1; // none found
}


// ============================================
// 2. Better Approach (Frequency Array)
// ============================================
//
// Idea:
// 1. Count how many times each character appears (26 lowercase letters).
// 2. In a second pass, return the first character whose count is 1.
//
// Time Complexity:  O(N)
//      -> One pass to count, one pass to find result.
// Space Complexity: O(1)
//      -> Fixed array of 26 letters.
//
int firstUniqChar_Better(string s) {
    vector<int> freq(26, 0);

    // Count frequency
    for (char c : s)
        freq[c - 'a']++;

    // Find first unique
    for (int i = 0; i < s.size(); i++) {
        if (freq[s[i] - 'a'] == 1)
            return i;
    }
    return -1;
}


// ============================================
// 3. Optimal Approach (Queue + Frequency Tracking)
// ============================================
//
// Idea:
// Use a queue to keep track of indices of characters that are currently unique.
// - Push each index into the queue as we process the string.
// - If a character becomes non-unique, pop it from the front.
// - The front of the queue always holds the index of the first unique char.
//
// Time Complexity:  O(N)
//      -> Each character pushed and popped at most once.
// Space Complexity: O(N)
//      -> Queue can store up to N indices in the worst case.
//
int firstUniqChar_Optimal(string s) {
    queue<int> q;
    vector<int> count(26, 0);

    for (int i = 0; i < s.size(); i++) {
        int idx = s[i] - 'a';
        count[idx]++;
        q.push(i);

        // Remove from front while not unique
        while (!q.empty() && count[s[q.front()] - 'a'] > 1)
            q.pop();
    }

    // Front of queue = index of first unique character
    return q.empty() ? -1 : q.front();
}


// ============================================
// MAIN FUNCTION TO TEST
// ============================================
int main() {
    string s = "loveleetcode";

    cout << "Input String: " << s << "\n\n";

    cout << "Brute Force Result:  " << firstUniqChar_Brute(s) << endl;
    cout << "Better Result:       " << firstUniqChar_Better(s) << endl;
    cout << "Optimal (Queue) Result: " << firstUniqChar_Optimal(s) << endl;

    return 0;
}
