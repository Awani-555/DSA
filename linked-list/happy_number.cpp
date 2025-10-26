#include <iostream>
using namespace std;

/* ---------------------------------------------------------------
   OPTIMIZED APPROACH (Floyd’s Cycle Detection)
   ---------------------------------------------------------------
   Idea:
   * Treat sequence of numbers as nodes in a linked list.
   * Slow moves 1 step, fast moves 2 steps (sumOfSquares applied).
   * If fast reaches 1 → happy number.
   * If slow == fast → cycle detected → not happy.

     Time Complexity: O(log n) per step, total steps <= constant
       → Maximum sum of squares reduces number quickly
     Space Complexity: O(1)
       → No extra memory, just two pointers
--------------------------------------------------------------- */

// Function to calculate sum of squares of digits
int findSquare(int n){
    int sum=0;
    while(n>0){
        int digit=n/10;
        sum+=digit*digit;
        n/=10;
    }
    return sum;
}

bool isHappy(int n){
    int slow=n;
    int fast=n;
    do{
        slow=findSquare(slow);
        fast=findSquare(findSquare(fast));
    }while(slow!=fast && fast!=1);

    return fast==1;
}

/* ================================================================
   MAIN
================================================================ */
int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    if (isHappy(n))
        cout << n << " is a Happy Number!\n";
    else
        cout << n << " is NOT a Happy Number!\n";

    return 0;
}
