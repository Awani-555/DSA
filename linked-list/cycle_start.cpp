#include<iostream>
#include<unordered_set>
using namespace std;


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/*
---------------------------------------------------------------------------------------------
  NAIVE APPROACH:
---------------------------------------------------------------------------------------------
  *Idea:

  - Use a hash set to track visited nodes.
  - The first node that repeats is the start of the cycle.

  Time Complexity:  O(n)
   We visit each node once.Inserting/looking up in the hash set takes O(1) average time.
  Space Complexity: O(n)
  We store every visited node in a set (in the worst case).
*/
ListNode* detectCycleNaive(ListNode* head)
{
    unordered_set <ListNode*> visited;
    if(!head) return head;
    while(head){
         // If we already saw this node, it’s the start of the cycle
        if(visited.find(head)!=visited.end()) return head;
        else{
            visited.insert(head);
            head=head->next;
        }
    }
    // No cycle found
    return nullptr;

}

/*================================================================
   OPTIMIZED APPROACH (Floyd’s Cycle Detection)
   ---------------------------------------------------------------
   Idea:
   1. Use two pointers (slow & fast).
      * slow moves 1 step
      *fast moves 2 steps
   2. If they meet - there’s a cycle.
   3. Move slow to head, and move both one step at a time.
      The point where they meet again is the start of the cycle.

   Time Complexity: O(n)
       Each pointer goes through the list at most twice.

   Space Complexity: O(1)
       Uses only two pointers, no extra space.

   Best and most efficient approach.
================================================================ */
ListNode* detectCycle(ListNode* head){
    if(!head) return nullptr;

    ListNode* slow=head;
    ListNode* fast=head;
    // Step 1: Detect cycle
     while(fast && fast->next){
        slow=slow->next;
        fast=fast->next->next;
     // Step 2: find the starting node
        if(fast==slow)
        {
            slow=head;
            while(slow!=fast)
            {
                slow=slow->next;
                fast=fast->next;
            }
            return fast;// start of cycle
        }
     }
     return nullptr;// no cycle

}

/* ================================================================
   HELPER FUNCTIONS
================================================================ */

// Creates a cyclic linked list for testing
ListNode* createCyclicList() {
    ListNode* head = new ListNode(3);
    ListNode* second = new ListNode(2);
    ListNode* third = new ListNode(0);
    ListNode* fourth = new ListNode(-4);

    head->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = second; // makes a cycle at node '2'

    return head;
}

// Creates a normal (no cycle) list
ListNode* createAcyclicList() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    return head;
}

/* ================================================================
   MAIN FUNCTION
================================================================ */
int main() {
    ListNode* cyclicHead = createCyclicList();
    ListNode* acyclicHead = createAcyclicList();

    cout << "Testing Naive Approach:\n";
    ListNode* node1 = detectCycleNaive(cyclicHead);
    cout << (node1 ? "Cycle starts at node " + to_string(node1->val) : "No cycle found") << endl;

    cout << "\nTesting Optimized Approach (Floyd’s):\n";
    ListNode* node2 = detectCycle(cyclicHead);
    cout << (node2 ? "Cycle starts at node " + to_string(node2->val) : "No cycle found") << endl;

    cout << "\nTesting Acyclic List (Optimized):\n";
    ListNode* node3 = detectCycle(acyclicHead);
    cout << (node3 ? "Cycle starts at node " + to_string(node3->val) : "No cycle found") << endl;

    return 0;
}