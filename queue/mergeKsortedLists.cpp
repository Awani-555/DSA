#include <bits/stdc++.h>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/* -----------------------------------------------------------
   BRUTE FORCE APPROACH
   -----------------------------------------------------------
   IDEA:
   1. Traverse all lists and push all values into a vector.
   2. Sort the vector.
   3. Build a new sorted linked list.

   TIME COMPLEXITY: O(N log N)
   SPACE COMPLEXITY: O(N)
----------------------------------------------------------- */
ListNode* mergeKLists_Brute(vector<ListNode*>& lists) {
    vector<int> vals;
    for (auto list : lists) {
        while (list) {
            vals.push_back(list->val);
            list = list->next;
        }
    }

    sort(vals.begin(), vals.end());

    ListNode dummy(0);
    ListNode* tail = &dummy;
    for (int v : vals) {
        tail->next = new ListNode(v);
        tail = tail->next;
    }
    return dummy.next;
}

/* -----------------------------------------------------------
   BETTER APPROACH
   -----------------------------------------------------------
   IDEA:
   1. Merge lists one by one using the two-sorted-lists merge method.
   2. Reuse the standard merge technique from Merge Sort.

   TIME COMPLEXITY: O(kN)
   SPACE COMPLEXITY: O(1)
----------------------------------------------------------- */
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* tail = &dummy;

    while (l1 && l2) {
        if (l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

ListNode* mergeKLists_Better(vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;

    ListNode* merged = lists[0];
    for (int i = 1; i < lists.size(); i++) {
        merged = mergeTwoLists(merged, lists[i]);
    }
    return merged;
}

/* -----------------------------------------------------------
   OPTIMAL APPROACH
   -----------------------------------------------------------
   IDEA:
   1. Use a min-heap to always extract the smallest element among the heads.
   2. Push the next node of the extracted node into the heap.
   3. Repeat until the heap is empty.

   TIME COMPLEXITY: O(N log k)
   SPACE COMPLEXITY: O(k)
----------------------------------------------------------- */
struct compare {
    bool operator()(ListNode* a, ListNode* b) {
        return a->val > b->val;
    }
};

ListNode* mergeKLists_Optimal(vector<ListNode*>& lists) {
    priority_queue<ListNode*, vector<ListNode*>, compare> minHeap;

    for (auto l : lists) {
        if (l)
            minHeap.push(l);
    }

    ListNode dummy(0);
    ListNode* tail = &dummy;

    while (!minHeap.empty()) {
        ListNode* node = minHeap.top();
        minHeap.pop();

        tail->next = node;
        tail = tail->next;

        if (node->next)
            minHeap.push(node->next);
    }

    return dummy.next;
}

/* -----------------------------------------------------------
   UTILITY FUNCTIONS FOR TESTING
----------------------------------------------------------- */
ListNode* buildList(const vector<int>& vals) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    for (int v : vals) {
        tail->next = new ListNode(v);
        tail = tail->next;
    }
    return dummy.next;
}

void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

/* -----------------------------------------------------------
   MAIN FUNCTION 
----------------------------------------------------------- */
int main() {
    vector<ListNode*> lists;
    lists.push_back(buildList({1, 4, 5}));
    lists.push_back(buildList({1, 3, 4}));
    lists.push_back(buildList({2, 6}));

    cout << "\n BRUTE FORCE \n";
    printList(mergeKLists_Brute(lists));

    // Rebuild lists (since merge modifies them)
    lists.clear();
    lists.push_back(buildList({1, 4, 5}));
    lists.push_back(buildList({1, 3, 4}));
    lists.push_back(buildList({2, 6}));

    cout << "\n BETTER APPROACH \n";
    printList(mergeKLists_Better(lists));

    // Rebuild again
    lists.clear();
    lists.push_back(buildList({1, 4, 5}));
    lists.push_back(buildList({1, 3, 4}));
    lists.push_back(buildList({2, 6}));

    cout << "\n OPTIMAL APPROACH\n";
    printList(mergeKLists_Optimal(lists));

    return 0;
}
