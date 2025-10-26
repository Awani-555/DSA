#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/* ---------------------------------------------------------------
   NAIVE APPROACH
   ---------------------------------------------------------------
   Idea:
   - Count the total number of nodes (n).
   - Traverse again to the n/2-th node.

   Time Complexity: O(n) + O(n) = O(n)
   Space Complexity: O(1)
--------------------------------------------------------------- */
ListNode* middleNodeNaive(ListNode* head){
    int count=0;
    ListNode* temp=head;
    while(temp){
        count++;
        temp=temp->next;
    }
    int mid=count/2;
    temp=head;
    while(mid!=0){
        mid--;
        temp=temp->next;
    }
    return temp;
}
/* ---------------------------------------------------------------
   OPTIMIZED APPROACH (FAST & SLOW POINTERS)
   ---------------------------------------------------------------
   Idea:
   - Use two pointers:
     *slow moves 1 step at a time
     * fast moves 2 steps at a time
   - When fast reaches the end, slow is at the middle.

   Time Complexity: O(n)
   Space Complexity: O(1)
--------------------------------------------------------------- */
ListNode* middleNode(ListNode* head){
    ListNode* slow=head;
    ListNode* fast=head;
    while(fast && fast->next){
        slow=slow->next;
        fast=fast->next->next;
    }
    return slow;

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
    ListNode* head = createList({1, 2, 3, 4, 5, 6});

    cout << "Original List:\n";
    printList(head);

    ListNode* midNaive = middleNodeNaive(head);
    cout << "\nMiddle Node (Naive): " << midNaive->val << endl;

    ListNode* midOptimized = middleNode(head);
    cout << "Middle Node (Optimized): " << midOptimized->val << endl;

    return 0;
}