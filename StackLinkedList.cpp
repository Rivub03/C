#include <iostream>     // For input/output operations (cout, endl)
#include <limits>       // For std::numeric_limits<int>::min()

// Using namespace std; is retained as per your preference for now.
using namespace std;

// Define the Node structure for the linked list
struct Node {
    int data;     // Data stored in the node
    Node* next;   // Pointer to the next node in the list
};

// Global top pointer for the stack (as per your original design)
// For a more robust and reusable stack, this would ideally be
// a member of a Stack struct/class.
Node* top = nullptr; // Initialize to nullptr, indicating an empty stack

// Function Prototypes
void push(int);
int pop();
bool isEmpty();
int peek();
void deleteStack(); // For cleaning up all allocated nodes
void printStack();

int main() {
    cout << "--- Stack Operations Test ---" << endl;

    // Test case 1: Pushing elements
    cout << "\nPushing elements onto the stack:" << endl;
    push(10);
    cout << "Pushed: 10" << endl;
    cout << "Stack: ";
    printStack();
    push(20);
    cout << "Pushed: 20" << endl;
    cout << "Stack: ";
    printStack();
    push(30);
    cout << "Pushed: 30" << endl;
    cout << "Stack: ";
    printStack();

    cout << "Is stack empty? " << (isEmpty() ? "Yes" : "No") << endl; // Should be No
    cout << "Top element: " << peek() << endl; // Should be 30
    cout << "Stack: ";
    printStack();
    // Test case 2: Popping elements
    cout << "\nPopping elements from the stack:" << endl;
    cout << "Popped: " << pop() << endl; // Should pop 30
    cout << "Stack: ";
    printStack();
    cout << "Top element: " << peek() << endl; // Should be 20
    cout << "Popped: " << pop() << endl; // Should pop 20
    cout << "Stack: ";
    printStack();
    cout << "Top element: " << peek() << endl; // Should be 10
    // Test case 3: Popping until empty and then underflow
    cout << "\nPopping last element and testing underflow:" << endl;
    cout << "Popped: " << pop() << endl; // Should pop 10
    cout << "Stack: ";
    printStack();
    cout << "Is stack empty? " << (isEmpty() ? "Yes" : "No") << endl; // Should be Yes
    cout << "Stack: " << printStack;
    cout << "Attempting to pop from empty stack:" << endl;
    int popped_val = pop(); // This will print "Stack Underflow!" and return INT_MIN
    if (popped_val == std::numeric_limits<int>::min()) {
        cout << "Pop operation failed due to underflow." << endl;
    }

    // Test case 4: Peeking at an empty stack
    cout << "\nAttempting to peek at an empty stack:" << endl;
    int peeked_val = peek(); // This will print "Stack is empty!" and return INT_MIN
    if (peeked_val == std::numeric_limits<int>::min()) {
        cout << "Peek operation failed because stack is empty." << endl;
    }

    // Test case 5: Pushing again after empty
    cout << "\nPushing elements again:" << endl;
    cout << "Stack: ";
    printStack();
    push(40);
    cout << "Pushed: 40" << endl;
    cout << "Stack: ";
    printStack();
    push(50);
    cout << "Pushed: 50" << endl;
    cout << "Stack: ";
    printStack();
    cout << "Top element: " << peek() << endl; // Should be 50
    // Test case 6: Clean up the stack using deleteStack
    cout << "\nCleaning up the stack with deleteStack()..." << endl;
    deleteStack();
    cout << "Is stack empty after deleteStack? " << (isEmpty() ? "Yes" : "No") << endl;
    cout << "Stack: ";
    printStack();

    // Verify it's truly empty
    cout << "Attempting pop after deleteStack:" << endl;
    pop();
    cout << "Attempting peek after deleteStack:" << endl;
    peek();

    cout << "\n--- Stack Operations Test Complete ---" << endl;

    return 0;
}

// Function Implementations

// Push: Adds an element to the top of the stack (head of the linked list)
void push(int x) {
    Node* newNode = new Node(); // 1. Create a new Node
    newNode->data = x;          // 2. Set the data of the new Node
    newNode->next = top;        // 3. Make the new Node point to the current top
    top = newNode;              // 4. Update top to be the new Node
}

// Pop: Removes and returns the top element from the stack
int pop() {
    if (isEmpty()) {
        cout << "Stack Underflow! Stack is empty, nothing to pop!" << endl;
        // Return a sentinel value when stack is empty and cannot pop
        return std::numeric_limits<int>::min();
    }
    else {
        Node* nodeToDelete = top; // Store pointer to the current top node
        int x = nodeToDelete->data; // Get the data from the top node
        top = top->next;          // Move top to the next node (effectively removing the old top)
        delete nodeToDelete;      // Free the memory of the old top node
        return x;                 // Return the popped data
    }
}

// Peek: Returns the top element without removing it
int peek() {
    if (isEmpty()) {
        cout << "Stack is empty! No element on top to peek." << endl;
        // Return a sentinel value when stack is empty and cannot peek
        return std::numeric_limits<int>::min();
    }
    return top->data; // Return data from the top node
}

// isEmpty: Checks if the stack is empty
bool isEmpty() {
    return top == nullptr; // Simpler and preferred check (nullptr is sufficient)
}

// deleteStack: Frees all nodes in the stack
void deleteStack() {
    Node* current = top;
    Node* nextNode; // Use a distinct name to avoid confusion
    while (current != nullptr) {
        nextNode = current->next; // Store the next node before deleting current
        delete current;           // Delete the current node
        current = nextNode;       // Move to the next node
    }
    top = nullptr; // Important: Reset top to nullptr to indicate stack is empty
}

void printStack() {
    Node* current = top;
    cout << "[";
    while (current != nullptr) {
        cout << current->data << ",";
        current = current->next;
    }
    cout << "]" << endl;
}