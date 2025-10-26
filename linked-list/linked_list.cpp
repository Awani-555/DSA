#include <iostream>
using namespace std;

/*
 * Singly Linked List implementation in C++
 * Includes:
 *  - Insert at Beginning, Middle, and End
 *  - Delete from Beginning, Middle, and End
 *  - Display function
 *
 */

// ----------------------
// Node Structure
// ----------------------
struct Node {
    int data;     // Value stored in the node
    Node* next;   // Pointer to the next node

    // Constructor for convenience
    Node(int value) : data(value), next(nullptr) {}
};

// ----------------------
// LinkedList Class
// ----------------------
class LinkedList {
private:
    Node* head; // Pointer to the first node

public:
    // Constructor - initializes an empty list
    LinkedList() : head(nullptr) {}

    // ----------------------
    // INSERTION OPERATIONS
    // ----------------------

    // Insert at the beginning
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        newNode->next = head; // Point new node to current head
        head = newNode;       // Move head to new node
    }

    // Insert at the end
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) { // If list is empty
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) { // Traverse to the last node
            temp = temp->next;
        }
        temp->next = newNode; // Link last node to new node
    }

    // Insert at a given position (1-based index)
    void insertAtPosition(int value, int position) {
        if (position <= 0) {
            cout << "Position must be >= 1\n";
            return;
        }

        if (position == 1) { // Insert at beginning
            insertAtBeginning(value);
            return;
        }

        Node* newNode = new Node(value);
        Node* temp = head;
        int currentPos = 1;

        // Traverse to the node before the desired position
        while (temp != nullptr && currentPos < position - 1) {
            temp = temp->next;
            currentPos++;
        }

        if (temp == nullptr) {
            cout << "Position out of range!\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    // ----------------------
    // DELETION OPERATIONS
    // ----------------------

    // Delete from beginning
    void deleteAtBeginning() {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp; // Free memory
    }

    // Delete from end
    void deleteAtEnd() {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }
        if (head->next == nullptr) { // Only one element
            delete head;
            head = nullptr;
            return;
        }
        Node* temp = head;
        while (temp->next->next != nullptr) { // Stop at second last node
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }

    // Delete from a given position (1-based index)
    void deleteAtPosition(int position) {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        if (position <= 0) {
            cout << "Position must be >= 1\n";
            return;
        }

        if (position == 1) { // Delete first node
            deleteAtBeginning();
            return;
        }

        Node* temp = head;
        int currentPos = 1;

        // Traverse to node before the one to delete
        while (temp != nullptr && currentPos < position - 1) {
            temp = temp->next;
            currentPos++;
        }

        if (temp == nullptr || temp->next == nullptr) {
            cout << "Position out of range!\n";
            return;
        }

        Node* nodeToDelete = temp->next;
        temp->next = nodeToDelete->next;
        delete nodeToDelete;
    }

    // ----------------------
    // DISPLAY OPERATION
    // ----------------------
    void display() {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }
        Node* temp = head;
        cout << "Linked List: ";
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    // ----------------------
    // Destructor
    // ----------------------
    ~LinkedList() {
        Node* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// ----------------------
// MAIN FUNCTION
// ----------------------
int main() {
    LinkedList list;

    // Insert elements
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.display();

    // Insert at beginning
    list.insertAtBeginning(5);
    list.display();

    // Insert in the middle (at position 3)
    list.insertAtPosition(15, 3);
    list.display();

    // Delete beginning
    list.deleteAtBeginning();
    list.display();

    // Delete middle (position 3)
    list.deleteAtPosition(3);
    list.display();

    // Delete end
    list.deleteAtEnd();
    list.display();

    return 0;
}
