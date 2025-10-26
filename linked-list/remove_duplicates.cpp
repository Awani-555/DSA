#include <iostream>
using namespace std;
/*
Problem: Remove duplicates from a sorted singly linked list
    * Singly Linked List implementation in C++
    * Includes:
    *  - Remove duplicates from a sorted linked list
    */
   //Definition for singly liked list.
   // Node struct represents a single element in a singly linked list.
   struct ListNode {
       int val;
       ListNode* next;
       ListNode(int x) : val(x), next(nullptr) {}
       ListNode(int x, ListNode *next) : val(x), next(next) {}

   };

   class Solution{
     
    
    //Brute-Force
    /*
    *Intuition: Traverse each node ,for each node traverse the rest of the list to remove duplicates.
    * Time Complexity: O(n^2)
    * Space Complexity: O(1)
    */
   /*
   ListNode* deleteDuplicatesBrute(ListNode* head) {
       if(!head) return nullptr;
       ListNode* current=head;
       while(current){
       ListNode* runner=current;
       while(runner->next)
        {
         if(current->val==runner->next->val)
           {
             runner->next=runner->next->next;
           }
         else{
             runner=runner->next;
           }
        }
           current=current->next;
       }
           return head;
       }

    //Better Approach
    /*Intuition:Use a hash set to track seen values(works for unsorted lists too)
    *Time Complexity:O(n)
    *Space Complexity:O(n)

    #include <unordered_set>
    unordered_set<int> seen;
    ListNode* dummy=new ListNode(0);
    dummy->next=head;
    ListNode*prev=dummy;
        while(head){
            if(seen.count(head->val))
            {
                 prev->next=head->next;
            }else
            {
                 seen.insert(head->val);
                 prev=head;
            }
                 head=head->next;

    }
                 return dummy->next;
   }
   */
  //Optimised Approach
  /*
   *Idea: Since list is sorted, duplicates are consecutive
   * Simply compare current node with next
   * Time Complexity: O(n)
   * Space Complexity: O(1)
   */

   public:
   ListNode* removeDuplicates(ListNode* head){
    if(!head) return nullptr;
    ListNode* current=head;
    while(current && current->next)
        {
            if(current->val==current->next->val){
                current->next=current->next->next;
            }
            else{
                current=current->next;
            }
        }
        return head;
   }

   };
   //Helper Functions
   void printList(ListNode* head) {
    while(head) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

ListNode* createList(int arr[], int n) {
    if(n==0) return nullptr;
    ListNode* head = new ListNode(arr[0]);
    ListNode* curr = head;
    for(int i=1;i<n;i++) {
        curr->next = new ListNode(arr[i]);
        curr = curr->next;
    }
    return head;
}

// ==============================
// Main Function for Testing
// ==============================
int main() {
    // Edge Cases to Test:
    // 1. Empty List
    // 2. Single Node
    // 3. All duplicates
    // 4. No duplicates
    // 5. Duplicates at the beginning/end

    int arr[] = {1, 1, 2, 3, 3, 4};
    int n = sizeof(arr)/sizeof(arr[0]);
    ListNode* head = createList(arr, n);

    cout << "Original List: ";
    printList(head);

    Solution sol;
    head = sol.removeDuplicates(head);

    cout << "After Removing Duplicates: ";
    printList(head);

    return 0;
}