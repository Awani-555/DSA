#include <bits/stdc++.h>
using namespace std;

// ============================================
// Definition for singly-linked list
// ============================================
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// ============================================
// Helper function to print linked list
// ============================================
void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}


// ============================================
// 1. Brute Force Approach

// Idea: Copy all node values into a vector, then check if the vector is a palindrome
// Time Complexity: O(N)  -> traverse all N nodes once to copy, and again to check palindrome
// Space Complexity: O(N) -> extra vector of size N is used to store node values


// ============================================
bool isPalindrome_Brute(ListNode* head) {
    vector<int> vals;
    ListNode* temp = head;
    while (temp) {
        vals.push_back(temp->val); // copy node values
        temp = temp->next;
    }

    int i = 0, j = vals.size() - 1;
    while (i < j) {
        if (vals[i] != vals[j]) return false; // mismatch found
        i++; j--;
    }
    return true;
}

// ============================================
// 2. Optimal Approach (Reverse Second Half)
// Idea: Find the middle of the list, reverse the second half, then compare the halves
// Time Complexity: O(N)  -> 
//     Step 1: Find middle  -> O(N/2)
//     Step 2: Reverse second half -> O(N/2)
//     Step 3: Compare halves -> O(N/2)
//     Total ~ O(N)
// Space Complexity: O(1) -> Only a few pointers are used, no extra array needed

// ============================================
bool isPalindrome_Optimal(ListNode* head) {
    if (!head || !head->next) return true; // empty or single node list

    // Step 1: Find middle using slow and fast pointers
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Step 2: Reverse second half
    ListNode* prev = nullptr;
    ListNode* curr = slow->next;
    while (curr) {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    // Step 3: Compare first half and reversed second half
    ListNode* first = head;
    ListNode* second = prev;
    bool palindrome = true;
    while (second) {
        if (first->val != second->val) {
            palindrome = false;
            break;
        }
        first = first->next;
        second = second->next;
    }

    // Step 4: Optional - restore the reversed second half to original list
    curr = prev;
    prev = nullptr;
    while (curr) {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    slow->next = prev;

    return palindrome;
}

// ============================================
// Main Function to Test
// ============================================
int main() {
    // Example: 1 -> 2 -> 3 -> 2 -> 1
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(2);
    head->next->next->next->next = new ListNode(1);

    cout << "Linked List: ";
    printList(head);

    cout << "Brute Force: " 
         << (isPalindrome_Brute(head) ? "Yes" : "No") << endl;

    cout << "Optimal: " 
         << (isPalindrome_Optimal(head) ? "Yes" : "No") << endl;

    return 0;
}
