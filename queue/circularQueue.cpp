#include <iostream>
using namespace std;

// Circular Queue implementation using array
class CircularQueue {
    int *arr;        // array to store queue elements
    int front;       // points to front element
    int rear;        // points to last element
    int size;        // total capacity
    int count;       // current number of elements

public:
    // Constructor to initialize queue
    CircularQueue(int n) {
        size = n;
        arr = new int[size];
        front = 0;
        rear = -1;
        count = 0;
    }

    // Add element to queue
    void enqueue(int x) {
        // Time: O(1)
        if (isFull()) {
            cout << "Queue is full\n";
            return;
        }
        // Move rear in circular fashion
        rear = (rear + 1) % size;
        arr[rear] = x;
        count++;
    }

    // Remove element from queue
    void dequeue() {
        // Time: O(1)
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        // Move front in circular fashion
        front = (front + 1) % size;
        count--;
    }

    // Get the front element
    int peek() {
        // Time: O(1)
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return -1;
        }
        return arr[front];
    }

    // Check if queue is empty
    bool isEmpty() {
        // Time: O(1)
        return count == 0;
    }

    // Check if queue is full
    bool isFull() {
        // Time: O(1)
        return count == size;
    }

    // Display all elements (for understanding)
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        cout << "Queue elements: ";
        for (int i = 0; i < count; i++) {
            cout << arr[(front + i) % size] << " ";
        }
        cout << endl;
    }

    // Destructor to free memory
    ~CircularQueue() {
        delete[] arr;
    }
};


int main() {
    CircularQueue q(5); // Queue of size 5

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.display();

    cout << "Front element: " << q.peek() << endl; // 10

    q.dequeue();
    q.dequeue();
    q.display();

    q.enqueue(50);
    q.enqueue(60);
    q.enqueue(70); // Now queue becomes full
    q.display();

    cout << "Front element: " << q.peek() << endl;
    cout << "Is queue full? " << (q.isFull() ? "Yes" : "No") << endl;
    cout << "Is queue empty? " << (q.isEmpty() ? "Yes" : "No") << endl;

    return 0;
}