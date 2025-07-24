#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <queue>
#include <stack>
using namespace std;

struct Node {
    int data;
    int priority; // Lower number = Higher priority
    Node* next;

    Node(int data, int priority) {
        this->data = data;
        this->priority = priority;
        this->next = nullptr;
    }

    // For printing Node directly (optional but helpful)
    friend ostream& operator<<(ostream& os, const Node& node) {
        os << "(Data:" << node.data << ",Priority:" << node.priority << ")";
        return os;
    }
};

// Linked List Priority Queue Structure
struct LinkedListPriorityQueue {
    Node* head;
    Node* tail; // Keep track of tail for potential future optimization (or just good practice)

    // Constructor
    LinkedListPriorityQueue() {
        head = nullptr;
        tail = nullptr;
    }

    // Destructor: Frees all allocated nodes to prevent memory leaks
    ~LinkedListPriorityQueue() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current; // Free the memory for the current node
            current = nextNode; // Move to the next node
        }
        head = nullptr; // Ensure head and tail are null after cleanup
        tail = nullptr;
    }

    // Check if the queue is empty
    bool IsEmpty() const { // Added const as it doesn't modify the object
        return head == nullptr; // Only head check is sufficient if tail is always consistent
    }

    // EnQueue: Inserts a new node into the queue based on its priority
    // O(N) in worst case (inserting lowest priority into a queue of N items)
    void EnQueue(int data, int priority) { // Take data and priority directly
        Node* newNode = new Node(data, priority); // Create the new node

        if (IsEmpty()) {
            head = newNode;
            tail = newNode;
            cout << "Enqueued: " << *newNode << " (first element)" << endl;
            return;
        }

        // Case 1: Insert at head (highest priority)
        if (newNode->priority < head->priority) {
            newNode->next = head;
            head = newNode;
            cout << "Enqueued: " << *newNode << " (at head)" << endl;
            return;
        }

        // Case 2: Find insertion point in the middle or at the end
        Node* current = head;
        // Iterate while 'current->next' is not null AND 'newNode' has lower or equal priority
        // than the 'next' node's priority. This finds the node *before* the insertion point.
        // We stop when we find a node whose 'next' has a HIGHER (numerically lower) priority,
        // or if we reach the end of the list.
        while (current->next != nullptr && newNode->priority >= current->next->priority) {
            current = current->next;
        }

        // Now, 'current' is the node *after* which newNode should be inserted.
        // Or, 'current' is the tail if newNode needs to be inserted at the very end.
        newNode->next = current->next;
        current->next = newNode;

        // Case 3: Update tail if inserted at the end
        if (newNode->next == nullptr) { // If new node became the last node
            tail = newNode;
            cout << "Enqueued: " << *newNode << " (at tail)" << endl;
        }
        else {
            cout << "Enqueued: " << *newNode << " (in middle)" << endl;
        }
    }

    // Dequeue: Removes and returns the highest priority element (from head)
    // O(1) operation
    int Dequeue() {
        if (IsEmpty()) {
            cout << "Priority Queue Underflow! Cannot dequeue." << endl;
            return std::numeric_limits<int>::min(); // Sentinel value for error
        }

        Node* temp = head; // Node to be dequeued
        int dequeuedData = temp->data; // Get the data

        head = head->next; // Move head to the next node

        if (head == nullptr) { // If the queue becomes empty after dequeue
            tail = nullptr;   // Reset tail as well
        }

        delete temp; // Free the memory of the dequeued node
        cout << "Dequeued: " << dequeuedData << endl;
        return dequeuedData;
    }

    // Peek: Returns the data of the highest priority element without removing it
    // O(1) operation
    int Peek() const { // Added const
        if (IsEmpty()) {
            cout << "Priority Queue is empty! No element to peek." << endl;
            return std::numeric_limits<int>::min(); // Sentinel value for error
        }
        return head->data;
    }

    // Optional: Print the entire queue
    void PrintQueue() const {
        cout << "PQ: [";
        Node* current = head;
        while (current != nullptr) {
            cout << *current; // Use the overloaded operator<< for Node
            if (current->next != nullptr) {
                cout << "->";
            }
            current = current->next;
        }
        cout << "]" << endl;
    }
};

int main() {
    LinkedListPriorityQueue* pq = new LinkedListPriorityQueue();

    cout << "Initial Queue State:" << endl;
    pq->PrintQueue();
    cout << "Is Empty? " << (pq->IsEmpty() ? "Yes" : "No") << endl;

    cout << "\n--- Enqueuing Elements ---" << endl;
    pq->EnQueue(10, 3); // (10, P:3)
    pq->PrintQueue();

    pq->EnQueue(50, 1); // (50, P:1) should be at head
    pq->PrintQueue();

    pq->EnQueue(20, 4); // (20, P:4) should be at tail
    pq->PrintQueue();

    pq->EnQueue(5, 1);  // (5, P:1) same priority as 50, should be after 50 (FIFO)
    pq->PrintQueue();

    pq->EnQueue(100, 0); // (100, P:0) highest priority
    pq->PrintQueue();

    pq->EnQueue(25, 2); // (25, P:2) should be between P:1 and P:3
    pq->PrintQueue();


    cout << "\nPeek: " << pq->Peek() << endl; // Should be 100

    cout << "\n--- Dequeuing Elements ---" << endl;
    pq->Dequeue(); // Removes 100 (P:0)
    pq->PrintQueue();
    cout << "Peek: " << pq->Peek() << endl; // Should be 50

    pq->Dequeue(); // Removes 50 (P:1)
    pq->PrintQueue();
    pq->Dequeue(); // Removes 5 (P:1)
    pq->PrintQueue();
    pq->Dequeue(); // Removes 25 (P:2)
    pq->PrintQueue();
    pq->Dequeue(); // Removes 10 (P:3)
    pq->PrintQueue();
    pq->Dequeue(); // Removes 20 (P:4)
    pq->PrintQueue();

    cout << "\n--- After Dequeuing All ---" << endl;
    pq->Dequeue(); // Should trigger Underflow
    pq->PrintQueue();
    cout << "Is Empty? " << (pq->IsEmpty() ? "Yes" : "No") << endl;

    // Add some more after emptying
    pq->EnQueue(77, 1);
    pq->EnQueue(88, 0);
    pq->PrintQueue();
    cout << "Peek: " << pq->Peek() << endl;

    delete pq; // Frees the LinkedListPriorityQueue object and its nodes via destructor

    return 0;
}

