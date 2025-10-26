#include <iostream>
#include <unordered_set>
using namespace std;


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

 /*
 ----------------------------------------------------------------------
   NAIVE APPROACH: Using Hash Set
 -----------------------------------------------------------------------
    Idea:
   - Traverse the linked list and store each node's address in a hash set.
   - If we ever encounter a node that already exists in the set,
     that means the linked list contains a cycle.
   - If we reach the end (nullptr), it means there is no cycle.

   Time Complexity:  O(n)
     -> Each node is visited once and lookup/insert in unordered_set is O(1) on average.
   Space Complexity: O(n)
     -> We store each node’s address in the hash set in the worst case.
*/
bool hasCycleNaive(ListNode* head)
{
    unordered_set<ListNode*> visited;
    ListNode* current=head;

    while(current!=nullptr){
        //check if element present in the set,if found, return true
        if(visited.find(current)!=visited.end())
        {
            return true;
        }
        //if not found,insert in set
        visited.insert(current);
        current=current->next;
    }
        return false;
        
    }

    /* 
   -------------------------------------------------------------------------
   OPTIMIZED APPROACH: Floyd’s Cycle Detection Algorithm (Tortoise & Hare)
   -------------------------------------------------------------------------
   Idea:
   - Use two pointers:
       1. slow  → moves one step at a time
       2. fast  → moves two steps at a time
   - If the linked list has a cycle, both pointers will eventually meet.
   - If fast reaches the end (nullptr), there’s no cycle.

   Time Complexity:  O(n)
     -> In the worst case, each pointer travels through all nodes.
   Space Complexity: O(1)
     -> Only two pointers used, no extra data structure.
*/
bool hasCycle(ListNode* head){
    if(!head) return head;
    ListNode* slow=head;
    ListNode* fast=head;
    while(fast && fast->next)
    {
        slow=slow->next; // Move slow by 1 step
        fast=fast->next->next; // Move fast by 2 steps

        if(fast==slow)
        {
            return true;// Cycle detected
        }
    }
    return false;//Fast reached end → no cycle

}


// ---------------------------------------------------------------------------
// Helper function to create a linked list and manually create a cycle
// ---------------------------------------------------------------------------
ListNode* createCyclicList() {
    ListNode* head = new ListNode(3);
    ListNode* second = new ListNode(2);
    ListNode* third = new ListNode(0);
    ListNode* fourth = new ListNode(-4);

    head->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = second; // creates a cycle at node 'second'

    return head;
}

ListNode* createAcyclicList() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    return head; // No cycle
}

// ---------------------------------------------------------------------------
// Main function to test both approaches
// ---------------------------------------------------------------------------
int main() {
    // Create a cyclic and acyclic linked list
    ListNode* cyclicHead = createCyclicList();
    ListNode* acyclicHead = createAcyclicList();

    cout << "Testing Naive Approach:\n";
    cout << "Cyclic List: " << (hasCycleNaive(cyclicHead) ? "Cycle Found" : "No Cycle") << endl;
    cout << "Acyclic List: " << (hasCycleNaive(acyclicHead) ? "Cycle Found" : "No Cycle") << endl;

    cout << "\nTesting Optimized Approach (Floyd's Algorithm):\n";
    cout << "Cyclic List: " << (hasCycle(cyclicHead) ? "Cycle Found" : "No Cycle") << endl;
    cout << "Acyclic List: " << (hasCycle(acyclicHead) ? "Cycle Found" : "No Cycle") << endl;

    return 0;
}

