#include <iostream>
#include<vector>
#include <algorithm>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};
/*
------------------------------------------------------------------------------------------------------
  NAIVE APPROACH
------------------------------------------------------------------------------------------------------
Idea:
   * Copy all nodes from both lists into a vector.
   * Sort the vector.
   * Rebuild a new sorted linked list from the vector.

    Time Complexity: O((n+m) log(n+m)) 
      Sorting all elements.
    Space Complexity: O(n+m)
      Extra array to store all nodes.
*/

ListNode* mergeTwoListsNaive(ListNode* l1, ListNode* l2) {
    vector<int> values;

    //Push all the values/elements from both the lists into a vector
    while (l1) {
        values.push_back(l1->val);
        l1 = l1->next;
    }
    while (l2) {
        values.push_back(l2->val);
        l2 = l2->next;
    }

    //Sort the vector
    sort(values.begin(), values.end());

    //Create a new Linked List and push all the values from vector into the Linked List

    ListNode* dummy = new ListNode(0);
    ListNode* current = dummy;
    for (int val : values) {
        current->next = new ListNode(val);
        current = current->next;
    }

    return dummy->next;
}

/*
------------------------------------------------------------------------------------------------------
  OPTIMISED APPROACH (MERGING IN PLACE)
------------------------------------------------------------------------------------------------------
  Idea:
   *Use two pointers, compare nodes of both lists.
   * Attach the smaller node to the merged list.
   * Continue until one list is exhausted, then append the rest.

 Time Complexity: O(n + m)
   We visit each node exactly once.
 Space Complexity: O(1)
   No extra storage needed, just pointers.
*/

ListNode* mergeTwoLists(ListNode* list1,ListNode* list2)
{
    ListNode* dummy = new ListNode(0); // create dummy node
    ListNode* current = dummy;         // pointer to build the list

    while(list1 && list2)
    {
        if(list1->val < list2->val)
        {
            current->next=list1;
            list1=list1->next;

        }
        else{
             current->next=list2;
            list2=list2->next;

        }
        current=current->next;// move current forward
    }
    // attach remaining nodes
    current->next = (list1) ? list1 : list2;
    
    return dummy->next;

}

/* ================================================================
   HELPER FUNCTIONS
================================================================ */
void printList(ListNode* head) {
    while (head) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "NULL\n";
}

// Create a simple sorted list
ListNode* createList(vector<int> vals) {
    ListNode* dummy = new ListNode(0);
    ListNode* curr = dummy;
    for (int v : vals) {
        curr->next = new ListNode(v);
        curr = curr->next;
    }
    return dummy->next;
}

/* ================================================================
   MAIN FUNCTION
================================================================ */
int main() {
    ListNode* l1 = createList({1,3,5});
    ListNode* l2 = createList({2,4,6});

    cout << "Naive Merge:\n";
    ListNode* mergedNaive = mergeTwoListsNaive(l1, l2);
    printList(mergedNaive);

    // Re-create lists because naive merge creates new nodes
    l1 = createList({1,3,5});
    l2 = createList({2,4,6});

    cout << "\nOptimized Merge:\n";
    ListNode* mergedOptimized = mergeTwoLists(l1, l2);
    printList(mergedOptimized);

    return 0;
}
