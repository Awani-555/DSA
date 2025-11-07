#include <iostream>
#include <stack>
using namespace std;

// Queue implemented using two stacks
class QueueUsingStacks {
    stack<int> stack_in;   // For enqueue operations
    stack<int> stack_out;  // For dequeue operations

public:
    // Add element to the end of the queue
    void enqueue(int x) {
        // Time: O(1)
        stack_in.push(x);
    }

    // Remove element from the front of the queue
    int dequeue() {
        // If stack_out is empty, move elements from stack_in
        // Time: Amortized O(1), Worst O(n)
        if (stack_out.empty()) {
            while (!stack_in.empty()) {
                stack_out.push(stack_in.top());
                stack_in.pop();
            }
        }

        // If still empty, queue is empty
        if (stack_out.empty()) {
            throw runtime_error("Queue is empty");
        }

        int front = stack_out.top();
        stack_out.pop();
        return front;
    }

    // Get the front element without removing it
    int peek() {
        // Time: Amortized O(1)
        if (stack_out.empty()) {
            while (!stack_in.empty()) {
                stack_out.push(stack_in.top());
                stack_in.pop();
            }
        }

        if (stack_out.empty()) {
            throw runtime_error("Queue is empty");
        }

        return stack_out.top();
    }

    // Check if the queue is empty
    bool isEmpty() {
        // Time: O(1)
        return stack_in.empty() && stack_out.empty();
    }
};


int main() {
    QueueUsingStacks q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    cout << "Front element: " << q.peek() << endl; // 10
    cout << "Dequeued: " << q.dequeue() << endl;   // 10
    cout << "Dequeued: " << q.dequeue() << endl;   // 20

    q.enqueue(40);
    cout << "Front element: " << q.peek() << endl; // 30
    cout << "Dequeued: " << q.dequeue() << endl;   // 30
    cout << "Dequeued: " << q.dequeue() << endl;   // 40

    cout << "Is queue empty? " << (q.isEmpty() ? "Yes" : "No") << endl;

    return 0;
}
