#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <queue>
#include <stack>
using namespace std;

struct PQNode {
    int data;
    int priority;
    PQNode() : data(), priority() {} // default constructor 
    PQNode(int data, int priority) {
        this->data = data;
        this->priority = priority;
    }
};
// A simplified circular array queue for internal use by the MultiLevelPriorityQueue
// This avoids the Deque features that are not strictly needed for internal queues
// while maintaining circularity.
struct SimpleArrayQueue {
    PQNode* array;
    int front;
    int rear;
    int capacity;
    int count;

    SimpleArrayQueue(int cap) {
        capacity = cap;
        array = new PQNode[capacity];
        front = 0;
        rear = -1; // Indicates empty
        count = 0;
    }

    bool IsEmpty() const { // Added const for consistency
        return count == 0;
    }

    bool IsFull() const { // Added const for consistency
        return count == capacity;
    }

    // Enqueue (adds to rear)
    void EnQueue(const PQNode& node) { // Takes a const reference to PQNode
        if (IsFull()) {
            // In a multi-level PQ, this would ideally mean the whole PQ is "full"
            // or that this specific priority level is full.
            // For now, we'll just print a message.
            // A more robust design might re-prioritize or resize.
            cout << "Warning: Priority queue level full! Cannot enqueue " << node.data << endl;
            return;
        }
        rear = (rear + 1) % capacity;
        array[rear] = node;
        count++;
    }

    // Dequeue (removes from front)
    PQNode DeQueue() {
        if (IsEmpty()) {
            // This should ideally not happen if the MultiLevelPQ checks IsEmpty first.
            // Returns a sentinel in case it's called on an empty queue.
            cout << "Error: Dequeuing from an empty SimpleArrayQueue." << endl;
            return PQNode(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        }
        PQNode dequeuedNode = array[front];
        front = (front + 1) % capacity;
        count--;
        if (count == 0) { // Reset for empty state
            front = 0;
            rear = -1;
        }
        return dequeuedNode;
    }

    PQNode Peek() const { // Added const
        if (IsEmpty()) {
            return PQNode(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        }
        return array[front];
    }

    void PrintQueue() const { // Added const
        cout << "[";
        if (IsEmpty()) {
            cout << "]";
            return;
        }
        for (int i = 0; i < count; ++i) {
            int current_index = (front + i) % capacity;
            cout << array[current_index].data;
            if (i < count - 1) {
                cout << ", ";
            }
        }
        cout << "]";
    }
};
// The main Multi-Level Priority Queue structure
struct MultiLevelPriorityQueue {
    SimpleArrayQueue** priorityQueues; // the 2D array that will alllow us to create the buckets
    int maxPriority; // to keep track of the number of queues
    int queueCapcity; // to keep track of the size of each queue
    int totalElements; // to keep track of the total number of elements 
    MultiLevelPriorityQueue(int numberOfQueues, int queueCapacity) {
        if (numberOfQueues <= 0 || queueCapacity <= 0) {
            cout << "Error: Number of priority levels and queue capacity must be positive." << endl;
            // Handle error, perhaps throw exception or exit
            return;
        }
        // initializing members
        maxPriority = numberOfQueues - 1;
        this->queueCapcity = queueCapacity;
        this->totalElements = 0;
        // dynamically allocating the 2D array
        priorityQueues = new SimpleArrayQueue * [numberOfQueues];
        for (int i = 0; i < numberOfQueues; i++) {
            priorityQueues[i] = new SimpleArrayQueue(queueCapacity);
        }
    }
    ~MultiLevelPriorityQueue() {
        if (priorityQueues) {
            for (int i = 0; i <= maxPriority; i++) {
                delete[] priorityQueues[i];
            }
            delete[] priorityQueues;
            priorityQueues = nullptr;
        }
    }

    bool IsEmpty() const {
        return totalElements == 0;
    }
    bool IsFull() const {
        for (int i = 0; i <= maxPriority; i++) {
            if (!priorityQueues[i]->IsFull()) {
                return false;
            }
        }
        return true;
    }
    int GetSize() const {
        return totalElements;
    }
    void EnQueue(PQNode node) {
        if (node.priority < 0 || node.priority > maxPriority) {
            cout << "Error: Invalid priority " << node.priority << ". Must be between 0 and " << maxPriority << "." << endl;
            return;
        }
        else if (IsFull()) {
            cout << "Overflow! The entire multilevel queue is full! " << endl;
        }
        priorityQueues[node.priority]->EnQueue(node); // enqueueing into proper subqueue based on prioriy
        if (!priorityQueues[node.priority]->IsFull()) { //checking if the subqueue is full or not
            totalElements++; // only increment if element is inserted into subqueue; 
        }
    }
    PQNode DeQueue() {
        if (IsEmpty()) {
            cout << "Multi-Level Priority Queue Underflow! Cannot dequeue." << endl;
            return PQNode(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        }
        PQNode deQueuedElement;
        for (int i = 0; i <= maxPriority; i++) { // start with the highest priority subqueue and start dequeueing from front
            if (!priorityQueues[i]->IsEmpty()) {
                deQueuedElement = priorityQueues[i]->DeQueue(); // dequeue from that specific subqueue i
                totalElements--;
                return deQueuedElement;
            }
        }
        cout << "Error: No elements found despite totalElements > 0. (Logical error)" << endl;
        return PQNode(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    }
    PQNode Peek() const {
        if (IsEmpty()) {
            cout << "Multi-Level Priority Queue is empty! No element to peek." << endl;
            return PQNode(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        }
        for (int i = 0; i <= maxPriority; i++) {
            if (!priorityQueues[i]->IsEmpty()) {
                // found the highest priority element 
                return priorityQueues[i]->Peek();
            }
        }
        // Should not be reached
        return PQNode(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    }
    void PrintQueue() {
        cout << "MultiLevevl Queue (Total Elements " << totalElements << "):" << endl;
        for (int i = 0; i <= maxPriority; i++) {
            cout << "Priority Queue " << i << ": ";
            priorityQueues[i]->PrintQueue();
            cout << endl;
        }
    }
};

int main() {
    // Create a priority queue that supports priorities from 0 to 2 (3 levels)
    // and each individual priority queue can hold up to 3 elements.
    MultiLevelPriorityQueue mlpq(3, 3);

    cout << "Initial Queue State:" << endl;
    mlpq.PrintQueue();
    cout << "Is Empty? " << (mlpq.IsEmpty() ? "Yes" : "No") << ", Size: " << mlpq.GetSize() << endl;

    cout << "\n--- Enqueuing Elements ---" << endl;
    mlpq.EnQueue(PQNode(10, 2)); // Value 10, Priority 2
    mlpq.EnQueue(PQNode(5, 0));  // Value 5, Priority 0 (highest)
    mlpq.EnQueue(PQNode(20, 1)); // Value 20, Priority 1
    mlpq.EnQueue(PQNode(15, 2)); // Value 15, Priority 2
    mlpq.EnQueue(PQNode(30, 0)); // Value 30, Priority 0
    mlpq.EnQueue(PQNode(25, 1)); // Value 25, Priority 1
    mlpq.EnQueue(PQNode(50, 0)); // Value 50, Priority 0
    mlpq.EnQueue(PQNode(100, 1)); // Value 100, Priority 1
    mlpq.EnQueue(PQNode(1, 2));  // Value 1, Priority 2
    mlpq.EnQueue(PQNode(99, 0)); // Attempt to enqueue to P:0, which is now full (3 elements)

    mlpq.PrintQueue();
    cout << "Is Empty? " << (mlpq.IsEmpty() ? "Yes" : "No") << ", Size: " << mlpq.GetSize() << endl;
    cout << "Peek: " << mlpq.Peek().data << endl; // Should be (5, P:0) or (30, P:0) or (50,P:0) depending on sub-queue order


    cout << "\n--- Dequeuing Elements ---" << endl;
    mlpq.DeQueue(); // Should get (5, P:0)
    mlpq.PrintQueue();
    mlpq.DeQueue(); // Should get (30, P:0)
    mlpq.PrintQueue();
    mlpq.DeQueue(); // Should get (50, P:0)
    mlpq.PrintQueue();
    mlpq.DeQueue(); // Should get (20, P:1)
    mlpq.PrintQueue();
    mlpq.DeQueue(); // Should get (25, P:1)
    mlpq.PrintQueue();
    mlpq.DeQueue(); // Should get (100, P:1)
    mlpq.PrintQueue();
    mlpq.DeQueue(); // Should get (10, P:2)
    mlpq.PrintQueue();
    mlpq.DeQueue(); // Should get (15, P:2)
    mlpq.PrintQueue();
    mlpq.DeQueue(); // Should get (1, P:2)
    mlpq.PrintQueue();

    cout << "\n--- After Dequeuing All ---" << endl;
    mlpq.DeQueue(); // Should be underflow
    mlpq.PrintQueue();
    cout << "Is Empty? " << (mlpq.IsEmpty() ? "Yes" : "No") << ", Size: " << mlpq.GetSize() << endl;

    // Test enqueuing after emptying
    mlpq.EnQueue(PQNode(77, 1));
    mlpq.EnQueue(PQNode(88, 0));
    mlpq.PrintQueue();
    cout << "Peek: " << mlpq.Peek().data << endl;

    //delete mlpq.priorityQueues[0]; // Example of manual deletion from main if not using Destructor
    // Make sure to use 'delete mlpq' to call its destructor and free all memory correctly.
    //delete& mlpq; // Correct way to delete a dynamically allocated object, if it was newed.
    // However, mlpq is on the stack in this main, so no 'delete &mlpq' needed.
    // If you had `MultiLevelPriorityQueue* mlpq_ptr = new MultiLevelPriorityQueue(...)`
    // then you would `delete mlpq_ptr;`.
    // The current main function creates `mlpq` on the stack, so its destructor is called automatically.

    return 0;
}
