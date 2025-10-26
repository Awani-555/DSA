#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/* ---------------------------------------------------------------
   REVERSE LINKED LIST II
   ---------------------------------------------------------------
   Idea:
   - Use a dummy node to simplify edge cases (m = 1)
   - Move a pointer to node just before position m
   - Reverse the sublist from m to n
   - Reconnect reversed sublist back

   Time Complexity: O(n)  -> visit each node once
   Space Complexity: O(1)  -> no extra space
--------------------------------------------------------------- */
ListNode* reverseBetween(ListNode* head, int m, int n) {
    if (!head || m == n) return head; // nothing to reverse

    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* prev = dummy;

    // Step 1: move prev to node before position m
    for (int i = 1; i < m; i++) {
        prev = prev->next;
    }

    // Step 2: reverse sublist from m to n
    ListNode* curr = prev->next;      // first node to reverse
    ListNode* nextNode;

    for (int i = 0; i < n - m; i++) {
        nextNode = curr->next;        // store next node
        curr->next = nextNode->next;  // detach nextNode
        nextNode->next = prev->next;  // insert nextNode after prev
        prev->next = nextNode;        // update prev to point to new front
    }

    return dummy->next;
}

/* ---------------------------------------------------------------
   HELPER FUNCTIONS
--------------------------------------------------------------- */
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

/* ---------------------------------------------------------------
   MAIN
--------------------------------------------------------------- */
int main() {
    ListNode* head = createList({1, 2, 3, 4, 5});

    cout << "Original List:\n";
    printList(head);

    int m = 2, n = 4;
    ListNode* reversed = reverseBetween(head, m, n);

    cout << "\nReversed List Between " << m << " and " << n << ":\n";
    printList(reversed);

    return 0;
}
