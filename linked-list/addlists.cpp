#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/* ------------------------------------------------------------------------------------------------------
   ADD TWO NUMBERS (Linked List)
------------------------------------------------------------------------------------------------------
Idea:
   * Each linked list represents a number in reverse order (ones digit at head)
   * Add corresponding digits of two lists, like elementary addition
   * Maintain a carry for sums >= 10
   * Store the result in a new linked list

Approaches:
1️⃣ Naive: Convert lists to integers, sum, and convert back to linked list
2️⃣ Better: Traverse both lists simultaneously, adding digits with carry
3️⃣ Optimized: Reuse one of the input lists to store the result (in-place)

Time Complexity:
- Naive: O(n + m) to convert lists + O(log(sum)) to rebuild list (limited by integer size)
- Better / Optimized: O(max(n, m)) traverse nodes once

Space Complexity:
- Naive: O(1) extra (but integer size limits)
- Better: O(1) extra for new nodes
- Optimized: O(1) extra (in-place)
------------------------------------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------------------------------------
   1️⃣ Naive Approach
------------------------------------------------------------------------------------------------------ */
ListNode* addTwoNumbersNaive(ListNode* l1, ListNode* l2) {
    long long num1 = 0, num2 = 0, base = 1;

    // Convert l1 to integer
    while (l1) {
        num1 += l1->val * base;
        base *= 10;
        l1 = l1->next;
    }

    base = 1;
    // Convert l2 to integer
    while (l2) {
        num2 += l2->val * base;
        base *= 10;
        l2 = l2->next;
    }

    long long sum = num1 + num2;

    // Convert sum back to linked list
    if (sum == 0) return new ListNode(0);

    ListNode* dummy = new ListNode(0);
    ListNode* curr = dummy;
    while (sum > 0) {
        curr->next = new ListNode(sum % 10);
        sum /= 10;
        curr = curr->next;
    }

    return dummy->next;
}

/* ------------------------------------------------------------------------------------------------------
   2️⃣ Better Approach
------------------------------------------------------------------------------------------------------ */
ListNode* addTwoNumbersBetter(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* curr = &dummy;
    int carry = 0;

    while (l1 || l2 || carry) {
        int sum = carry;
        if (l1) { sum += l1->val; l1 = l1->next; }
        if (l2) { sum += l2->val; l2 = l2->next; }

        carry = sum / 10;
        curr->next = new ListNode(sum % 10);
        curr = curr->next;
    }

    return dummy.next;
}

/* ------------------------------------------------------------------------------------------------------
   3️⃣ Optimized Approach (In-place)
------------------------------------------------------------------------------------------------------ */
ListNode* addTwoNumbersOptimized(ListNode* l1, ListNode* l2) {
    ListNode* head = l1;
    ListNode* prev = nullptr;
    int carry = 0;

    while (l1 || l2 || carry) {
        int sum = carry;
        if (l1) sum += l1->val;
        if (l2) sum += l2->val;

        if (l1) {
            l1->val = sum % 10;
            carry = sum / 10;
            prev = l1;
            l1 = l1->next;
        } else {
            prev->next = new ListNode(sum % 10);
            carry = sum / 10;
            prev = prev->next;
        }

        if (l2) l2 = l2->next;
    }

    return head;
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
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << " -> NULL\n";
}

/* ================================================================
   MAIN FUNCTION
================================================================ */
int main() {
    ListNode* l1 = createList({2, 4, 3}); // represents 342
    ListNode* l2 = createList({5, 6, 4}); // represents 465

    cout << "Input Lists:\n";
    printList(l1);
    printList(l2);

    cout << "\nNaive Approach:\n";
    printList(addTwoNumbersNaive(createList({2,4,3}), createList({5,6,4})));

    cout << "\nBetter Approach:\n";
    printList(addTwoNumbersBetter(createList({2,4,3}), createList({5,6,4})));

    cout << "\nOptimized Approach:\n";
    printList(addTwoNumbersOptimized(createList({2,4,3}), createList({5,6,4})));

    return 0;
}
