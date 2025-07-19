#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int data) {
        this->data = data;
        next = nullptr;
    }
    // Helper functions in the Node structure: These now take pointers by REFERENCE (Node*&)
    // This allows them to modify the original front/rear pointers of the Queue.

    // Append: Adds a new node to the end of the list.
    // In a queue, this is used for EnQueue.
    void Append(Node*& head, Node*& tail, int x) { // head and tail are now references to pointers
        Node* newNode = new Node(x);
        if (head == nullptr) { // List is empty, this is the first node
            head = newNode;
            tail = newNode;
        }
        else { // List is not empty, append to the end
            tail->next = newNode;
            tail = newNode; // Update tail to the new last node
        }
    }
    void Insert_at_end(Node*& head, Node*& tail, int x) {
        Node* newNode = new Node(x); // create new node

        Node* temp1 = head;
        while (temp1->next != nullptr) { //traverse 
            temp1 = temp1->next;
        }
        temp1->next = newNode;
        tail = newNode;
    }
    int Delete(Node*& head, Node*& tail) {
        if (head == nullptr) {
            cout << "Invalid deletion!" << endl;
            return INT32_MIN;
        }
        int x = head->data;
        Node* temp = head;
        head = temp->next; //fixes the link
        delete temp; //frees the memory by deleting the node
        if (head == nullptr) {  // In case List became empty cause there was only 1 node
            tail = nullptr;
        }
        return x;
    }
    int ListLength(Node* head) {
        Node* current = head;
        int count = 0;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }
    void DeleteList(Node*& head, Node*& tail) {
        // Free the allocated memory (optional, but good practice)
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
};
struct Queue {
    Node* front;
    Node* rear;

    Queue() {
        front = rear = nullptr; // Initialize the queue as empty 
    }
    ~Queue() {
        DeleteQueue();
    }

    bool IsEmpty() {
        return this->front == nullptr;
    }
    void Enqueue(int data) {
        Node dummyNode(0); // using a dummy node instead of making append static
        dummyNode.Append(this->front, this->rear, data); // calling member function as this won't need dereferencing
    }
    int DeQueue() {
        if (IsEmpty()) {
            cout << "Undeflow! Queue is empty" << endl;
            return INT32_MIN;
        }
        Node dummyNode(0);
        return dummyNode.Delete(this->front, this->rear);
    }
    int GetSize() {
        if (IsEmpty()) { // Added check for empty queue
            return 0;
        }
        Node dummyNode(0);
        return dummyNode.ListLength(this->front);
    }
    int GetFront() {
        if (IsEmpty()) {
            cout << "List is empty!" << endl;
            return -1;
        }
        return front->data;
    }
    int GetRear() {
        if (IsEmpty()) {
            cout << "List is empty!" << endl;
            return -1;
        }
        return rear->data;
    }
    bool IsFull() {
        Node* testNode = nullptr;
        try {
            testNode = new Node(0); // Try to allocate a node
            delete testNode;        // Immediately deallocate it
            return false;           // If successful, not full
        }
        catch (const std::bad_alloc& e) {
            return true;            // If allocation fails, it's "full" due to memory exhaustion
        }
    }

    void PrintQueue() {
        Node* temp = front;
        cout << "Queue: [";
        while (temp != nullptr) {
            cout << temp->data << ",";
            temp = temp->next;
        }
        cout << "]" << endl;
    }
    void DeleteQueue() {
        if (!IsEmpty()) { // Only try to delete if not already empty
            Node dummy_node(0); // Create a temporary/dummy Node object
            dummy_node.DeleteList(this->front, this->rear);
        }
    }
};

int main() {

    Queue* Q = new Queue();
    cout << "Initial Queue Status:" << endl;
    Q->PrintQueue();
    cout << "Front: " << Q->GetFront() << ", Rear: " << Q->GetRear() << ", Size: " << Q->GetSize() << ", IsEmpty: " << Q->IsEmpty() << endl;

    cout << "\n--- Enqueue Operations ---" << endl;
    Q->Enqueue(10); Q->PrintQueue(); cout << " Front: " << Q->GetFront() << " Rear: " << Q->GetRear() << " Size: " << Q->GetSize() << endl;
    Q->Enqueue(20); Q->PrintQueue(); cout << " Front: " << Q->GetFront() << " Rear: " << Q->GetRear() << " Size: " << Q->GetSize() << endl;
    Q->Enqueue(30);
    Q->Enqueue(40);
    Q->Enqueue(50);
    Q->Enqueue(60);
    Q->Enqueue(70);
    Q->Enqueue(80); Q->PrintQueue(); cout << " Front: " << Q->GetFront() << " Rear: " << Q->GetRear() << " Size: " << Q->GetSize() << endl;
    cout << "\nIs Queue Full? " << (Q->IsFull() ? "Yes" : "No") << endl; // Should be No unless memory exhausted

    cout << "\n--- DeQueue Operations ---" << endl;
    cout << "DeQueuing: " << Q->DeQueue();
    Q->PrintQueue(); cout << " Front: " << Q->GetFront() << " Rear: " << Q->GetRear() << " Size: " << Q->GetSize() << endl;
    cout << "DeQueuing: " << Q->DeQueue();
    Q->PrintQueue(); cout << " Front: " << Q->GetFront() << " Rear: " << Q->GetRear() << " Size: " << Q->GetSize() << endl;
    cout << "DeQueuing: " << Q->DeQueue();
    Q->PrintQueue(); cout << " Front: " << Q->GetFront() << " Rear: " << Q->GetRear() << " Size: " << Q->GetSize() << endl;
    cout << "DeQueuing: " << Q->DeQueue();
    Q->PrintQueue(); cout << " Front: " << Q->GetFront() << " Rear: " << Q->GetRear() << " Size: " << Q->GetSize() << endl;
    cout << "DeQueuing: " << Q->DeQueue();
    Q->PrintQueue(); cout << " Front: " << Q->GetFront() << " Rear: " << Q->GetRear() << " Size: " << Q->GetSize() << endl;
    cout << "DeQueuing: " << Q->DeQueue();
    Q->PrintQueue(); cout << " Front: " << Q->GetFront() << " Rear: " << Q->GetRear() << " Size: " << Q->GetSize() << endl;
    cout << "DeQueuing: " << Q->DeQueue();
    Q->PrintQueue(); cout << " Front: " << Q->GetFront() << " Rear: " << Q->GetRear() << " Size: " << Q->GetSize() << endl;
    cout << "DeQueuing: " << Q->DeQueue();
    Q->PrintQueue(); cout << " Front: " << Q->GetFront() << " Rear: " << Q->GetRear() << " Size: " << Q->GetSize() << endl;
    cout << "DeQueuing: " << Q->DeQueue();
    Q->PrintQueue(); cout << " Front: " << Q->GetFront() << " Rear: " << Q->GetRear() << " Size: " << Q->GetSize() << endl;

    cout << "\n--- Test Empty Queue Conditions ---" << endl;
    cout << "Is Queue Empty? " << (Q->IsEmpty() ? "Yes" : "No") << endl;
    cout << "DeQueuing from empty: " << Q->DeQueue() << endl; // Underflow
    cout << "GetFront from empty: " << Q->GetFront() << endl; // Empty message
    cout << "GetRear from empty: " << Q->GetRear() << endl;   // Empty message
    cout << "GetSize from empty: " << Q->GetSize() << endl;   // Should be 0

    cout << "\n--- Re-enqueue and Delete Queue ---" << endl;
    Q->Enqueue(100); Q->PrintQueue();
    Q->Enqueue(200); Q->PrintQueue();
    cout << "Front: " << Q->GetFront() << " Rear: " << Q->GetRear() << " Size: " << Q->GetSize() << endl;

    Q->DeleteQueue(); // This clears the internal linked list and sets Q->front/Q->rear to nullptr.
    // The Queue object *Q* itself is still valid, though its internal state is empty.
    cout << "After DeleteQueue:" << endl;
    Q->PrintQueue();  // This is perfectly fine. Q is a valid pointer, and PrintQueue correctly handles an empty queue.
    cout << "Is Queue Empty? " << (Q->IsEmpty() ? "Yes" : "No") << endl; // Also perfectly fine.

    delete Q;

    return 0;
}

