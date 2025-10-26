#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};
/* ---------------------------------------------------------------
   ITERATIVE APPROACH (Optimized)
   ---------------------------------------------------------------
   Idea:
   - Use 3 pointers: prev, curr, next
   - Reverse the links one by one

    Time Complexity: O(n)  -> visit each node once
    Space Complexity: O(1)  -> no extra space
--------------------------------------------------------------- */
ListNode* reverseListIterative(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;

    while (curr) {
        ListNode* nextNode = curr->next; // store next
        curr->next = prev;               // reverse link
        prev = curr;                     // move prev forward
        curr = nextNode;                 // move curr forward
    }

    return prev; // new head
}

/* ---------------------------------------------------------------
   RECURSIVE REVERSE LINKED LIST
   ---------------------------------------------------------------
   Idea:
   - Reverse the rest of the list first (recursive call)
   - Then make the next node point back to current
   - Break the original next pointer to avoid cycles

   Time Complexity: O(n)
   Space Complexity: O(n) -> recursion stack
--------------------------------------------------------------- */
ListNode* reverseListRecursive(ListNode* head) {
    // Base case: empty list or single node
    if (!head || !head->next) return head;

    // Step 1: reverse the rest of the list
    // This call goes all the way to the last node
    ListNode* newHead = reverseListRecursive(head->next);

    // Step 2: head->next now points to the last node of reversed sublist
    // Flip the pointer so the next node points back to current head
    head->next->next = head;

    // Step 3: break the original link to avoid cycle
    head->next = nullptr;

    // Step 4: return new head of the reversed list
    return newHead;
}


/* ================================================================
   HELPER FUNCTIONS
================================================================ */
ListNode* createList(const vector<int>& vals) {
    ListNode* dummy = new ListNode(0);
    ListNode* curr = dummy;
    for (int v : vals) {
        curr->next = new ListNode(v);
        curr = curr->next;
    }
    return dummy->next;
}

void printList(ListNode* head) {
    while (head) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "NULL\n";
}

/* ================================================================
   MAIN
================================================================ */
int main() {
    ListNode* head = createList({1, 2, 3, 4, 5});

    cout << "Original List:\n";
    printList(head);

    ListNode* reversedIter = reverseListIterative(head);
    cout << "\nReversed List (Iterative):\n";
    printList(reversedIter);

    // Reverse back to original using recursive
    ListNode* reversedRec = reverseListRecursive(reversedIter);
    cout << "\nReversed List Back (Recursive):\n";
    printList(reversedRec);

    return 0;
}