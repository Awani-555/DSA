#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list node
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Helper function to print a linked list
void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

/*
-------------------------------------------------------
EXPLANATION AND ANALYSIS
-------------------------------------------------------

Problem:
Remove all nodes that have duplicate numbers from a sorted linked list,
so that only distinct numbers remain.

Example:
Input:  1 -> 2 -> 3 -> 3 -> 4 -> 4 -> 5
Output: 1 -> 2 -> 5

-------------------------------------------------------
Naive (Brute Force) Approach:
-------------------------------------------------------
Idea:
1. Traverse the list once and count the frequency of each value using a hash map.
2. Traverse again and rebuild a new list containing only values that occur once.

Steps:
- Use unordered_map<int, int> to store counts.
- Reconstruct the list with nodes whose frequency == 1.

Time Complexity:  O(N)
Space Complexity: O(N)  (for hash map and new list)
Pros: Easy to understand, works for unsorted lists too.
Cons: Uses extra space, doesn’t exploit sorted property.*/

ListNode* deleteDuplicates_Brute(ListNode* head) {
    if (!head) return nullptr;

    // Step 1: Count frequency of each value
    unordered_map<int, int> freq;
    ListNode* curr = head;
    while (curr) {
        freq[curr->val]++;
        curr = curr->next;
    }

    // Step 2: Build a new list with only unique values
    ListNode dummy(0);
    ListNode* tail = &dummy;
    curr = head;

    while (curr) {
        if (freq[curr->val] == 1) {
            tail->next = new ListNode(curr->val);
            tail = tail->next;
        }
        curr = curr->next;
    }

    return dummy.next;
}

/*
-------------------------------------------------------
Optimal (Two-Pointer) Approach:
-------------------------------------------------------
Idea:
Since the list is sorted, duplicates always appear consecutively.
We can skip all duplicate groups in a single traversal.

Steps:
1. Use a dummy node before head to simplify pointer handling.
2. Use two pointers:
   - prev: points to the last node confirmed unique so far.
   - curr: moves through the list to find and skip duplicates.
3. When duplicates are found, link prev->next to the node after them.
4. Finally, return dummy.next as the new head.

Time Complexity:  O(N)  (each node visited once)
Space Complexity: O(1)  (only a few pointers used)
Pros: Space efficient, elegant, and clean handling of edge cases.
Cons: Requires careful pointer manipulation.

-------------------------------------------------------
*/

ListNode* deleteDuplicates_Optimal(ListNode* head) {
    if (!head) return nullptr;

    ListNode dummy(0);         // dummy before head
    dummy.next = head;         // link dummy to head
    ListNode* prev = &dummy;   // points to last confirmed non-duplicate
    ListNode* curr = head;     // traverses the list

    while (curr) {
        bool isDuplicate = false;

        // Skip all nodes with the same value
        while (curr->next && curr->val == curr->next->val) {
            curr = curr->next;
            isDuplicate = true;
        }

        if (isDuplicate) {
            // Skip entire duplicate group
            prev->next = curr->next;
        } else {
            // No duplicate; move prev forward
            prev = curr;
        }

        curr = curr->next;
    }

    return dummy.next;
}

// ----------------------------------------------------
// Main function for testing
// ----------------------------------------------------
int main() {
    // Example 1: duplicates at head
    ListNode* head1 = new ListNode(1);
    head1->next = new ListNode(1);
    head1->next->next = new ListNode(2);
    head1->next->next->next = new ListNode(3);

    cout << "Original List 1: ";
    printList(head1);
    ListNode* result1_brute = deleteDuplicates_Brute(head1);
    cout << "Brute Result 1:  ";
    printList(result1_brute);

    // Example 2: duplicates in middle
    ListNode* head2 = new ListNode(1);
    head2->next = new ListNode(2);
    head2->next->next = new ListNode(3);
    head2->next->next->next = new ListNode(3);
    head2->next->next->next->next = new ListNode(4);
    head2->next->next->next->next->next = new ListNode(4);
    head2->next->next->next->next->next->next = new ListNode(5);

    cout << "\nOriginal List 2: ";
    printList(head2);
    ListNode* result2_optimal = deleteDuplicates_Optimal(head2);
    cout << "Optimal Result 2:  ";
    printList(result2_optimal);

    return 0;
}


