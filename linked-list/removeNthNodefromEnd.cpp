#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Helper function to print the list
void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

// ----------------------------------------------------
// 1. Brute Force Approach
// Idea: Count total nodes, go to (length - n)-th node, remove next
// Time: O(N), Space: O(1)
// ----------------------------------------------------
ListNode* removeNthFromEnd_Brute(ListNode* head, int n) {
    if(!head) return nullptr;
    int length = 0;
    ListNode* temp = head;
    while(temp) { length++; temp = temp->next; }
    if(n == length) return head->next; // remove head
    temp = head;
    for(int i = 1; i < length - n; i++) temp = temp->next;
    temp->next = temp->next->next;
    return head;
}


// ----------------------------------------------------
// 3. Optimal Approach (One-pass, Two Pointers)
// Idea: Move first pointer n steps ahead, then move both until end
// Time: O(N), Space: O(1)
// ----------------------------------------------------
ListNode* removeNthFromEnd_Optimal(ListNode* head, int n) {
    ListNode* first = head;
    ListNode* second = head;
    if(!head) return head;

    for(int i = 0; i < n; i++) first = first->next;
    if(!first) return head->next; // remove head

    while(first->next) {
        first = first->next;
        second = second->next;
    }

    second->next = second->next->next;
    return head;
}

// ----------------------------------------------------
// Main function to test all approaches
// ----------------------------------------------------
int main() {
    // Example: 1 -> 2 -> 3 -> 4 -> 5, n = 2
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    int n = 2;

    cout << "Original List: ";
    printList(head);

    // Brute
    ListNode* result1 = removeNthFromEnd_Brute(head, n);
    cout << "Brute Force Result: ";
    printList(result1);

    // Recreate the list
    head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

  

    // Recreate the list
    head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    // Optimal
    ListNode* result3 = removeNthFromEnd_Optimal(head, n);
    cout << "Optimal Approach Result: ";
    printList(result3);

    return 0;
}
