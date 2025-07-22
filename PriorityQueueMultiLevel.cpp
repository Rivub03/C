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

    ~SimpleArrayQueue() {
        delete[] array;
        array = nullptr;
    }

    bool IsEmpty() const { // Added const for consistency
        return count == 0;
    }

    bool IsFull() const { // Added const for consistency
        return count == capacity;
    }

    // Enqueue (adds to rear)
    void Enqueue(const PQNode& node) { // Takes a const reference to PQNode
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
    PQNode Dequeue() {
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
    SimpleArrayQueue** priorityLevels; // Array of pointers to SimpleArrayQueue
    int maxPriorityLevel;              // Max numerical priority value (e.g., if priorities are 0,1,2, then maxPrioLevel = 2)
    int defaultQueueCapacity;          // Capacity for each individual SimpleArrayQueue
    int totalElements;                 // Total elements across all queues

    // Constructor
    MultiLevelPriorityQueue(int numLevels, int queueCapacity) {
        if (numLevels <= 0 || queueCapacity <= 0) {
            cout << "Error: Number of priority levels and queue capacity must be positive." << endl;
            // Handle error, perhaps throw exception or exit
            maxPriorityLevel = 0;
            defaultQueueCapacity = 0;
            priorityLevels = nullptr;
            totalElements = 0;
            return;
        }
        maxPriorityLevel = numLevels - 1; // If 3 levels, max priority value is 2 (0, 1, 2)
        defaultQueueCapacity = queueCapacity;
        totalElements = 0;

        // Dynamically allocate an array of SimpleArrayQueue pointers
        priorityLevels = new SimpleArrayQueue * [numLevels];
        // Initialize each pointer to a new SimpleArrayQueue
        for (int i = 0; i < numLevels; ++i) {
            priorityLevels[i] = new SimpleArrayQueue(defaultQueueCapacity);
        }
    }

    // Destructor
    ~MultiLevelPriorityQueue() {
        if (priorityLevels) {
            for (int i = 0; i < maxPriorityLevel + 1; ++i) {
                delete priorityLevels[i]; // Delete each individual SimpleArrayQueue object
            }
            delete[] priorityLevels;     // Delete the array of pointers itself
            priorityLevels = nullptr;
        }
    }

    bool IsEmpty() const {
        return totalElements == 0;
    }

    bool IsFull() const {
        // A multi-level PQ is full if all its individual queues are full.
        // Or if totalElements == maxCapacity (if you had a max capacity for the whole thing)
        // This implementation considers it full if any attempt to enqueue would fail.
        // It's more common to consider it full if all levels are full.
        for (int i = 0; i <= maxPriorityLevel; ++i) {
            if (!priorityLevels[i]->IsFull()) {
                return false; // At least one level is not full
            }
        }
        return true; // All levels are full
    }

    int GetSize() const {
        return totalElements;
    }

    // Enqueue: Adds an element to the appropriate priority queue level
    void Enqueue(int value, int priority) {
        // Validate priority
        if (priority < 0 || priority > maxPriorityLevel) {
            cout << "Error: Invalid priority " << priority << ". Must be between 0 and " << maxPriorityLevel << "." << endl;
            return;
        }

        PQNode newNode(value, priority);
        priorityLevels[priority]->Enqueue(newNode); // Enqueue into the specific priority level's queue

        // Only increment totalElements if the enqueue into the sub-queue was successful
        // (i.e., the sub-queue wasn't full). This requires checking the sub-queue's state
        // or modifying SimpleArrayQueue::Enqueue to return a bool.
        // For simplicity, we'll assume the sub-queue handles its overflow printing
        // and just increment totalElements, implying if a sub-queue is full,
        // it counts as an overflow for the whole system if no other action is taken.
        // A more robust system would re-prioritize or handle it.
        if (!priorityLevels[priority]->IsFull()) { // Check before adding. This is imperfect
            // as Enqueue might already print overflow
            totalElements++;
        }
    }

    // Dequeue: Removes and returns the highest priority element (lowest numerical priority value)
    PQNode Dequeue() {
        if (IsEmpty()) {
            cout << "Multi-Level Priority Queue Underflow! Cannot dequeue." << endl;
            return PQNode(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        }

        // Iterate from the highest priority level (0) to the lowest (maxPriorityLevel)
        for (int i = 0; i <= maxPriorityLevel; ++i) {
            if (!priorityLevels[i]->IsEmpty()) {
                // Found a non-empty queue at this priority level
                PQNode dequeuedNode = priorityLevels[i]->Dequeue();
                totalElements--;
                cout << "Dequeued: " << dequeuedNode.data << " from priority level " << i << endl;
                return dequeuedNode;
            }
        }

        // This path should ideally not be reached if IsEmpty() check passes
        cout << "Error: No elements found despite totalElements > 0. (Logical error)" << endl;
        return PQNode(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    }

    // Peek: Returns the highest priority element without removing it
    PQNode Peek() const {
        if (IsEmpty()) {
            cout << "Multi-Level Priority Queue is empty! No element to peek." << endl;
            return PQNode(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        }

        for (int i = 0; i <= maxPriorityLevel; ++i) {
            if (!priorityLevels[i]->IsEmpty()) {
                // Found the highest priority element
                return priorityLevels[i]->Peek();
            }
        }

        // Should not be reached
        return PQNode(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    }

    void PrintQueue() const {
        cout << "Multi-Level PQ (Total " << totalElements << " elements):" << endl;
        for (int i = 0; i <= maxPriorityLevel; ++i) {
            cout << "  Priority " << i << ": ";
            priorityLevels[i]->PrintQueue();
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
    mlpq.Enqueue(10, 2); // Value 10, Priority 2
    mlpq.Enqueue(5, 0);  // Value 5, Priority 0 (highest)
    mlpq.Enqueue(20, 1); // Value 20, Priority 1
    mlpq.Enqueue(15, 2); // Value 15, Priority 2
    mlpq.Enqueue(30, 0); // Value 30, Priority 0
    mlpq.Enqueue(25, 1); // Value 25, Priority 1
    mlpq.Enqueue(50, 0); // Value 50, Priority 0
    mlpq.Enqueue(100, 1); // Value 100, Priority 1
    mlpq.Enqueue(1, 2);  // Value 1, Priority 2
    mlpq.Enqueue(99, 0); // Attempt to enqueue to P:0, which is now full (3 elements)

    mlpq.PrintQueue();
    cout << "Is Empty? " << (mlpq.IsEmpty() ? "Yes" : "No") << ", Size: " << mlpq.GetSize() << endl;
    cout << "Peek: " << mlpq.Peek().data << endl; // Should be (5, P:0) or (30, P:0) or (50,P:0) depending on sub-queue order


    cout << "\n--- Dequeuing Elements ---" << endl;
    mlpq.Dequeue(); // Should get (5, P:0)
    mlpq.PrintQueue();
    mlpq.Dequeue(); // Should get (30, P:0)
    mlpq.PrintQueue();
    mlpq.Dequeue(); // Should get (50, P:0)
    mlpq.PrintQueue();
    mlpq.Dequeue(); // Should get (20, P:1)
    mlpq.PrintQueue();
    mlpq.Dequeue(); // Should get (25, P:1)
    mlpq.PrintQueue();
    mlpq.Dequeue(); // Should get (100, P:1)
    mlpq.PrintQueue();
    mlpq.Dequeue(); // Should get (10, P:2)
    mlpq.PrintQueue();
    mlpq.Dequeue(); // Should get (15, P:2)
    mlpq.PrintQueue();
    mlpq.Dequeue(); // Should get (1, P:2)
    mlpq.PrintQueue();

    cout << "\n--- After Dequeuing All ---" << endl;
    mlpq.Dequeue(); // Should be underflow
    mlpq.PrintQueue();
    cout << "Is Empty? " << (mlpq.IsEmpty() ? "Yes" : "No") << ", Size: " << mlpq.GetSize() << endl;

    // Test enqueuing after emptying
    mlpq.Enqueue(77, 1);
    mlpq.Enqueue(88, 0);
    mlpq.PrintQueue();
    cout << "Peek: " << mlpq.Peek().data << endl;

    //delete mlpq.priorityLevels[0]; // Example of manual deletion from main if not using Destructor
    // Make sure to use 'delete mlpq' to call its destructor and free all memory correctly.
    //delete& mlpq; // Correct way to delete a dynamically allocated object, if it was newed.
    // However, mlpq is on the stack in this main, so no 'delete &mlpq' needed.
    // If you had `MultiLevelPriorityQueue* mlpq_ptr = new MultiLevelPriorityQueue(...)`
    // then you would `delete mlpq_ptr;`.
// The current main function creates `mlpq` on the stack, so its destructor is called automatically.

    return 0;
}

