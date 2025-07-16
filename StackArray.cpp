#include <iostream>     // Still needed for main's cout. If main couldn't use it,
// there would be no way to see output.
#include <limits>       // For std::numeric_limits<int>::min()

// Removed unused headers based on your request
// #include <string>
// #include <vector>
// #include <ostream>
// #include <strstream>
// #include <sstream>
// #include <cstdlib>
// #include <array>
// #include <iomanip>
// #include <cmath>

// Using namespace std; is retained as per your preference for now.
using namespace std;

struct ArrayStack {
    int top;    // Index of the top element
    int size;   // Renamed from 'capacity' back to 'size' to match your original
    // but conceptually it represents the total allocated capacity
    int* array; // Pointer to the dynamically allocated array

    // Constructor: Initializes the stack with a given capacity
    ArrayStack(int initialSize) {
        top = -1; // Stack is initially empty
        this->size = initialSize; // Use 'this->' to distinguish member from parameter
        array = new int[this->size]; // Allocate memory for the array
    }

    // Destructor: Frees dynamically allocated memory when the stack object is destroyed
    ~ArrayStack() {
        delete[] array; // Deallocate the array pointed to by 'array'
        array = nullptr; // Set the pointer to nullptr to prevent dangling pointer issues
    }
};

// Function prototypes
void push(ArrayStack*, int);
int pop(ArrayStack*);
int top(ArrayStack*); // 'top' function name remains as per your original
int size(ArrayStack*); // 'size' function name remains as per your original
bool isEmpty(ArrayStack*);
bool isFull(ArrayStack*);
void printStack(ArrayStack*); // Will use cout, but only for "demonstration" as in your main.

int main() {

    ArrayStack* stack = new ArrayStack(10);

    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    push(stack, 40);
    push(stack, 50);
    push(stack, 60);
    push(stack, 70);
    push(stack, 80);
    push(stack, 90);
    push(stack, 100); // Stack is now full (top = 9)
    push(stack, 110); // This should trigger "Stack overflow!" (message printed by push itself)
    printStack(stack);

    cout << "Popped: " << pop(stack) << endl; // Pop 100
    printStack(stack);

    cout << "Popped: " << pop(stack) << endl; // Pop 90
    printStack(stack);

    cout << "Top element is: " << top(stack) << endl; // Should be 80

    cout << "Popped: " << pop(stack) << endl; // 80
    cout << "Popped: " << pop(stack) << endl; // 70
    cout << "Popped: " << pop(stack) << endl; // 60
    cout << "Popped: " << pop(stack) << endl; // 50
    cout << "Popped: " << pop(stack) << endl; // 40
    cout << "Popped: " << pop(stack) << endl; // 30
    cout << "Popped: " << pop(stack) << endl; // 20
    cout << "Popped: " << pop(stack) << endl; // 10 (Stack is now empty)

    cout << "Popped (from empty stack): " << pop(stack) << endl; // Should trigger "Stack Underflow!" (message printed by pop)
    cout << "Top element (from empty stack): " << top(stack) << endl; // Should trigger "Stack is empty!" (message printed by top)

    printStack(stack); // Print empty stack

    delete stack;
    stack = nullptr;

    ArrayStack* stack1 = new ArrayStack(5);
    cout << "Size of the new stack: " << stack1->size << endl;
    stack1->size = 100;
    cout << "Size of the new stack is now: " << stack1->size << endl;

    return 0;
}

// Function Implementations

void push(ArrayStack* S, int x) {
    if (isFull(S)) {
        // Retained cout here as per your original request,
        // and it's generally expected for "overflow" messages to be seen.
        cout << "Stack overflow!" << endl;
        return;
    }
    else {
        S->top++; // Increment top before storing the new element
        S->array[S->top] = x;
    }
}

int pop(ArrayStack* S) {
    if (isEmpty(S)) {
        // Removed cout message as per your request to avoid it within core functions.
        // The caller will have to check the returned value (std::numeric_limits<int>::min())
        // to detect underflow.
        return std::numeric_limits<int>::min(); // Return a sentinel value for error
    }
    else {
        // Retrieve the value at the current top, then decrement top
        int poppedValue = S->array[S->top];
        S->top--; // Logically remove the element by decrementing top
        return poppedValue;
    }
}

int top(ArrayStack* S) { // Renamed from peek() back to top()
    if (isEmpty(S)) {
        // Removed cout message as per your request to avoid it within core functions.
        // The caller will have to check the returned value (std::numeric_limits<int>::min())
        // to detect an empty stack.
        return std::numeric_limits<int>::min(); // Return a sentinel value for error
    }
    return S->array[S->top]; // Return the element at top without removing it
}

int size(ArrayStack* S) { // Renamed from getStackSize() back to size()
    return (S->top + 1); // The number of elements is (top_index + 1)
}

bool isEmpty(ArrayStack* S) {
    // Simplified boolean return
    return S->top == -1; // Stack is empty if top is -1
}

bool isFull(ArrayStack* S) {
    // Your corrected logic is already here: S->top >= (S->size - 1)
    // This correctly handles the case where top is already at the last valid index.
    // Simplified boolean return.
    return S->top >= (S->size - 1);
}

void printStack(ArrayStack* S) {
    // Retained cout here as it's a display/utility function, and you use it in main.
    cout << "Stack: [";
    for (int i = 0; i <= S->top; i++) {
        cout << S->array[i];
        if (i < S->top) { // Fix for trailing comma
            cout << ", ";
        }
    }
    cout << "]" << endl;
}
}