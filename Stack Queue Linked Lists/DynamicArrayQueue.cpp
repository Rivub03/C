#include <iostream>
using namespace std;

#define maxSize 1000

struct DQueue {
    int* array;
    int front; // element must always be removed from the front
    int rear; // element must always be added to the rear. The idea is that front and rear will meet and that will signal that queue is empty
    int size;

    DQueue() : front(-1), rear(-1), size(0), array(nullptr) {} //constructor 

    ~DQueue() {
        delete[] array; // Destructor to clean up memory
    }

    void CreateQueue() {
        cout << "Enter size of queue (maximum size is " << maxSize << "): ";
        cin >> size;
        if (size > maxSize) {
            cout << "Size exceeds max size" << endl;
            size = 0; // Set size to 0 to indicate invalid queue
            return;
        }
        array = new int[size]; //dynamically allocates size to the queue 
    }

    void Enqueue(int x) {
        if (isFull()) {
            cout << "Error: Queue is full" << endl;
            return;
        }
        if (IsEmpty()) {
            front = rear = 0;
        }
        else {
            rear++; //rear is incremented 
        }
        array[rear] = x;
        cout << "Enqueued " << x << endl;
    }

    void Dequeue() {
        if (IsEmpty()) {
            cout << "Error: Queue is Empty" << endl;
            return;
        }
        cout << "Dequeued " << array[front] << endl;
        if (front == rear) {
            front = rear = -1; // Queue becomes empty
        }
        else {
            front++;
        }
    }

    int Front() {
        if (IsEmpty()) {
            cout << "Error: cannot return front from empty queue" << endl;
            return -1; // Return a sentinel value indicating error
        }
        return array[front];
    }

    bool IsEmpty() {
        if (front == -1) {
            return true;
        }
        else {
            return false; 
        }
    }

    bool isFull() {
        return (rear == size - 1); // returns true if rear == size -1, false otherwise
    }

    void Print() {
        if (IsEmpty()) {
            cout << "The Queue is empty." << endl;
            return;
        }
        cout << "The Queue is: [";
        for (int i = front; i <= rear; i++) {
            cout << array[i];
            if (i < rear) cout << ", ";
        }
        cout << "]" << endl;
    }
};

int main() {
    DQueue Q;
    Q.CreateQueue();
    if (Q.size == 0) {
        return 0; // Exit if queue wasn't created properly
    }
    Q.Enqueue(1);
    Q.Enqueue(2);
    Q.Enqueue(3);
    Q.Enqueue(4);
    Q.Enqueue(5);
    Q.Print();
    Q.Dequeue(); Q.Print();
    Q.Dequeue(); Q.Print();
    Q.Dequeue(); Q.Print();
    Q.Dequeue(); Q.Print();
    Q.Dequeue(); Q.Print();
    Q.Dequeue(); Q.Print();

    return 0;
}
