#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

struct QueueArray {
    int front, rear;
    int size;
    int count;
    int* array;

    //constructor
    QueueArray(int size) {
        front = rear = count = 0; // empty queue 
        this->size = size; // size = size entered
        array = new int[this->size]; //using this->size instead of just size since this->size can change.
    }
    //destructor
    ~QueueArray() {
        delete[] array;
        array = nullptr;
    }
    // using functions inside structures instead of outside since that makes them easier to write

    void EnQueue(int data) {
        if (IsFull()) {
            cout << "Overflow! Queue is full!" << endl;
            return;
        }
        else {
            this->rear = (this->rear + 1) % this->size; // array rear will come back circularly to 0 if >= to size.
            array[this->rear] = data; // this index is then used to assign value to that index of the array. 
            this->count++;
        }
    }

    int DeQueue() {
        if (IsEmpty()) {
            cout << "Underflow! Queue is empty!" << endl;
            return INT32_MIN;
        }
        else {
            this->front = (this->front + 1) % this->size; // similarly, the front will come back circularly to 0 if >= to size
            count--;
            int x = array[this->front];
            return x;
        }
    }

    int GetSize() {
        return this->count;
    }

    bool IsFull() {
        return this->count >= this->size;
    }

    bool IsEmpty() {
        return count == 0;
    }

    int Front() {
        if (IsEmpty()) {
            return INT32_MIN;
        }
        return array[this->front + 1];
    }

    int Rear() {
        if (IsEmpty()) {
            return INT32_MIN;
        }
        return array[this->rear];
    }
    void PrintQueue() {
        cout << "Queue: [";
        for (int i = 1; i <= this->count; i++) {
            int current_index = (front + i) % size;
            cout << array[current_index] << ",";
        }
        cout << "]" << endl;
    }
};

int main() {

    QueueArray* Q = new QueueArray(5);
    Q->PrintQueue();
    Q->EnQueue(10); Q->PrintQueue();
    cout << "Front of Queue: " << Q->Front() << endl;
    cout << "Rear of Queue: " << Q->Rear() << endl;
    Q->EnQueue(20); Q->PrintQueue();
    Q->EnQueue(30); Q->PrintQueue();
    Q->EnQueue(40); Q->PrintQueue();
    Q->EnQueue(50); Q->PrintQueue();
    cout << "Size of Queue: " << Q->GetSize() << endl;
    cout << "Front of Queue: " << Q->Front() << endl;
    cout << "Rear of Queue: " << Q->Rear() << endl;
    Q->DeQueue(); Q->PrintQueue();
    Q->DeQueue(); Q->PrintQueue();
    cout << "Front of Queue: " << Q->Front() << endl;
    cout << "Rear of Queue: " << Q->Rear() << endl;
    cout << "Size of Queue: " << Q->GetSize() << endl;
    Q->EnQueue(5); Q->PrintQueue();
    cout << "Size of Queue: " << Q->GetSize() << endl;
    cout << "Front of Queue: " << Q->Front() << endl;
    cout << "Rear of Queue: " << Q->Rear() << endl;
    Q->DeQueue(); Q->PrintQueue();
    Q->DeQueue(); Q->PrintQueue();
    cout << "Size of Queue: " << Q->GetSize() << endl;
    Q->DeQueue(); Q->PrintQueue();
    Q->DeQueue(); Q->PrintQueue();
    cout << "Front of Queue: " << Q->Front() << endl;
    cout << "Rear of Queue: " << Q->Rear() << endl;
    Q->EnQueue(20); Q->PrintQueue();
    Q->EnQueue(80); Q->PrintQueue();
    cout << "Front of Queue: " << Q->Front() << endl;
    cout << "Rear of Queue: " << Q->Rear() << endl;
    cout << "Size of Queue: " << Q->GetSize() << endl;
    delete Q;
    Q->EnQueue(20); Q->PrintQueue();
    cout << "Size of Queue: " << Q->GetSize() << endl;


    return 0;
}

