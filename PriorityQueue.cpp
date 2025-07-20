#include <iostream>
#include <limits> // For std::numeric_limits<int>::min()

using namespace std;

// Structure to hold data and its priority
struct PQNode {
    int value;
    int priority; // Lower number = Higher priority (e.g., 1 is higher than 5)

    PQNode(int val = 0, int prio = 0) : value(val), priority(prio) {}

    // For printing purposes (optional, but helpful for debugging)
    friend ostream& operator<<(ostream& os, const PQNode& node) {
        os << "(" << node.value << ", P:" << node.priority << ")";
        return os;
    }
};

// --- Implementation 1: Enqueue Sorted, Dequeue from Front ---
struct PriorityQueueSortedInsert {
    PQNode* array;
    int capacity;
    int count; // Current number of elements
    int front; // Always 0, or effectively indicates the start of valid data

    PriorityQueueSortedInsert(int cap) {
        capacity = cap;
        array = new PQNode[capacity];
        count = 0;
        front = 0; // Data is always shifted to start from index 0
    }

    ~PriorityQueueSortedInsert() {
        delete[] array;
        array = nullptr;
    }

    bool IsEmpty() {
        return count == 0;
    }

    bool IsFull() {
        return count == capacity;
    }

    int GetSize() {
        return count;
    }

    // Enqueue (Insert): Inserts element while maintaining sorted order (lowest priority first)
    // O(N) operation in worst case due to shifting
    void Enqueue(int value, int priority) {
        if (IsFull()) {
            cout << "Priority Queue Overflow! Cannot enqueue (" << value << ", P:" << priority << ")." << endl;
            return;
        }

        // Find the correct position to insert
        int i;
        // Iterate from the end backwards to find the insertion point
        // and shift elements to make space
        for (i = count - 1; i >= 0 && array[i].priority > priority; i--) {
            array[i + 1] = array[i];
        }

        array[i + 1] = PQNode(value, priority);
        count++;
        cout << "Enqueued: " << PQNode(value, priority) << endl;
    }

    // Dequeue (ExtractMin): Removes and returns the element with the highest priority (lowest priority value)
    // O(1) operation
    PQNode Dequeue() {
        if (IsEmpty()) {
            cout << "Priority Queue Underflow! Cannot dequeue." << endl;
            return PQNode(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()); // Sentinel
        }

        PQNode dequeuedNode = array[front]; // Element at front is the highest priority (lowest value)
        // For this implementation, elements are always shifted down on insert.
        // So, front is always 0. We effectively 'remove' by decrementing count.
        // If we want to physically remove and shift, it would be O(N) here.
        // But since Enqueue already keeps it sorted, simple logical removal is O(1).
        count--; // Simply decrement count. The "removed" element will be overwritten on next Enqueue.
        cout << "Dequeued: " << dequeuedNode << endl;
        return dequeuedNode;
    }

    // Peek/Top: Returns the highest priority element without removing it
    PQNode Peek() {
        if (IsEmpty()) {
            cout << "Priority Queue is empty! No element to peek." << endl;
            return PQNode(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()); // Sentinel
        }
        return array[front]; // Highest priority is always at the front
    }

    void PrintQueue() {
        cout << "PQ (Sorted Insert): [";
        for (int i = 0; i < count; ++i) {
            cout << array[i];
            if (i < count - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
};

// --- Implementation 2: Enqueue in Sequence, Dequeue by Priority ---
struct PriorityQueueSortedDequeue {
    PQNode* array;
    int capacity;
    int count; // Current number of elements
    int rear;  // Next available slot for enqueue

    PriorityQueueSortedDequeue(int cap) {
        capacity = cap;
        array = new PQNode[capacity];
        count = 0;
        rear = -1; // No elements yet
    }

    ~PriorityQueueSortedDequeue() {
        delete[] array;
        array = nullptr;
    }

    bool IsEmpty() {
        return count == 0;
    }

    bool IsFull() {
        return count == capacity;
    }

    int GetSize() {
        return count;
    }

    // Enqueue (Insert): Adds element to the end (like a regular queue)
    // O(1) operation
    void Enqueue(int value, int priority) {
        if (IsFull()) {
            cout << "Priority Queue Overflow! Cannot enqueue (" << value << ", P:" << priority << ")." << endl;
            return;
        }
        rear = (rear + 1) % capacity; // Simple circular enqueue (if not for linear array, will discuss)
        array[rear] = PQNode(value, priority);
        count++;
        cout << "Enqueued: " << PQNode(value, priority) << endl;
    }

    // Dequeue (ExtractMin): Scans for and removes the highest priority element
    // O(N) operation in worst case
    PQNode Dequeue() {
        if (IsEmpty()) {
            cout << "Priority Queue Underflow! Cannot dequeue." << endl;
            return PQNode(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()); // Sentinel
        }

        // Find the index of the highest priority element (lowest priority value)
        int highestPrioIndex = 0;
        // Adjust for circular array if elements are not contiguous from index 0
        // For a simple linear array (non-circular), we find in the 'active' part [0, count-1]
        // If we use circular logic for enqueue (as above), then we need to map to physical indices.
        // To simplify, let's assume a "linear" array where new elements fill from the left,
        // and we keep finding the min and shifting. This fits the "enqueue in sequence"
        // more naturally. For a truly circular array, this becomes more complex.
        // Let's modify Enqueue to be linear (add to end, without wrapping) for simplicity
        // of Dequeue's scan, or Dequeue becomes very complex.

        // Re-thinking Enqueue for this type: if Enqueue is O(1) and just adds to the end,
        // and Dequeue scans, then it's a "min-priority search" on an unsorted array.
        // We'll stick to a simple linear array for this model for clarity of O(N) dequeue.

        // If 'rear' just keeps growing, this requires special care.
        // Let's use 'count' and assume logical contiguous data for scan.
        // The data is conceptually in array[0] to array[count-1]
        // Let's adjust Enqueue to always add to 'count' index and increment count,
        // making it simple linear insert, and Dequeue shifts.

        int actualHighestPrioIndex = -1;
        int minPriorityFound = std::numeric_limits<int>::max();

        for (int i = 0; i < count; ++i) {
            if (array[i].priority < minPriorityFound) {
                minPriorityFound = array[i].priority;
                actualHighestPrioIndex = i;
            }
            else if (array[i].priority == minPriorityFound) {
                // Optional: Tie-breaking rule (e.g., FIFO for same priority)
                // If elements are inserted linearly, and we want FIFO for same priority,
                // we keep the *first* one found with that priority. Our loop does that.
            }
        }

        PQNode dequeuedNode = array[actualHighestPrioIndex];

        // Shift elements to fill the gap (O(N) operation)
        for (int i = actualHighestPrioIndex; i < count - 1; ++i) {
            array[i] = array[i + 1];
        }
        count--;
        rear--; // If rear tracked end of valid data, adjust it

        cout << "Dequeued: " << dequeuedNode << endl;
        return dequeuedNode;
    }

    // Peek/Top: Returns the highest priority element without removing it
    // O(N) operation
    PQNode Peek() {
        if (IsEmpty()) {
            cout << "Priority Queue is empty! No element to peek." << endl;
            return PQNode(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()); // Sentinel
        }

        int highestPrioIndex = -1;
        int minPriorityFound = std::numeric_limits<int>::max();

        for (int i = 0; i < count; ++i) {
            if (array[i].priority < minPriorityFound) {
                minPriorityFound = array[i].priority;
                highestPrioIndex = i;
            }
        }
        return array[highestPrioIndex];
    }

    void PrintQueue() {
        cout << "PQ (Sorted Dequeue): [";
        for (int i = 0; i < count; ++i) {
            cout << array[i];
            if (i < count - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
};

int main() {
    cout << "--- Priority Queue: Enqueue Sorted, Dequeue from Front ---" << endl;
    PriorityQueueSortedInsert pq1(5); // Capacity 5

    pq1.PrintQueue();
    pq1.Enqueue(10, 3); // (10, P:3)
    pq1.PrintQueue(); // [(10, P:3)]
    pq1.Enqueue(50, 1); // (50, P:1), (10, P:3)
    pq1.PrintQueue(); // [(50, P:1), (10, P:3)]
    pq1.Enqueue(20, 4); // (50, P:1), (10, P:3), (20, P:4)
    pq1.PrintQueue(); // [(50, P:1), (10, P:3), (20, P:4)]
    pq1.Enqueue(5, 1); // (50, P:1), (5, P:1), (10, P:3), (20, P:4) - Tie break (FIFO)
    pq1.PrintQueue(); // [(50, P:1), (5, P:1), (10, P:3), (20, P:4)]
    pq1.Enqueue(100, 0); // (100, P:0), (50, P:1), (5, P:1), (10, P:3), (20, P:4)
    pq1.PrintQueue(); // [(100, P:0), (50, P:1), (5, P:1), (10, P:3), (20, P:4)]
    pq1.Enqueue(200, 2); // Overflow
    pq1.PrintQueue();

    cout << "\nPeek: " << pq1.Peek() << endl; // Should be (100, P:0)

    cout << "\nDequeuing from PQ (Sorted Insert):" << endl;
    pq1.Dequeue(); // Removes (100, P:0)
    pq1.PrintQueue();
    pq1.Dequeue(); // Removes (50, P:1)
    pq1.PrintQueue();
    pq1.Dequeue(); // Removes (5, P:1)
    pq1.PrintQueue();
    pq1.Dequeue(); // Removes (10, P:3)
    pq1.PrintQueue();
    pq1.Dequeue(); // Removes (20, P:4)
    pq1.PrintQueue();
    pq1.Dequeue(); // Underflow
    pq1.PrintQueue();


    cout << "\n--- Priority Queue: Enqueue in Sequence, Dequeue by Priority ---" << endl;
    PriorityQueueSortedDequeue pq2(5); // Capacity 5

    pq2.PrintQueue();
    pq2.Enqueue(10, 3); // (10, P:3)
    pq2.PrintQueue(); // [(10, P:3)]
    pq2.Enqueue(50, 1); // (10, P:3), (50, P:1)
    pq2.PrintQueue(); // [(10, P:3), (50, P:1)]
    pq2.Enqueue(20, 4); // (10, P:3), (50, P:1), (20, P:4)
    pq2.PrintQueue(); // [(10, P:3), (50, P:1), (20, P:4)]
    pq2.Enqueue(5, 1); // (10, P:3), (50, P:1), (20, P:4), (5, P:1)
    pq2.PrintQueue(); // [(10, P:3), (50, P:1), (20, P:4), (5, P:1)]
    pq2.Enqueue(100, 0); // (10, P:3), (50, P:1), (20, P:4), (5, P:1), (100, P:0)
    pq2.PrintQueue(); // [(10, P:3), (50, P:1), (20, P:4), (5, P:1), (100, P:0)]
    pq2.Enqueue(200, 2); // Overflow
    pq2.PrintQueue();

    cout << "\nPeek: " << pq2.Peek() << endl; // Should be (100, P:0)

    cout << "\nDequeuing from PQ (Sorted Dequeue):" << endl;
    pq2.Dequeue(); // Removes (100, P:0)
    pq2.PrintQueue();
    pq2.Dequeue(); // Removes (50, P:1) (first with P:1)
    pq2.PrintQueue();
    pq2.Dequeue(); // Removes (5, P:1)
    pq2.PrintQueue();
    pq2.Dequeue(); // Removes (10, P:3)
    pq2.PrintQueue();
    pq2.Dequeue(); // Removes (20, P:4)
    pq2.PrintQueue();
    pq2.Dequeue(); // Underflow
    pq2.PrintQueue();

    return 0;
}