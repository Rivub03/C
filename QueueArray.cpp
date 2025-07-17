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
    int* array;

    //constructor
    QueueArray(int size) {
        front = rear = -1; // empty queue 
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
            cout << "Overflow! Queue is full" << endl;
            return;
        }
        else {
            this->rear++;
            array[this->rear] = data;
        }
    }

    int DeQueue() {
        if (IsEmpty()) {
            cout << "Underflow! Queue is empty!" << endl;
            return INT32_MIN;
        }
        else {
            int x;
            this->front++;
            x = array[this->front];
            return x;
        }
    }

    int GetSize() {
        return this->rear + 1;
    }

    bool IsFull() {
        return this->rear >= (this->size - 1);
    }

    bool IsEmpty() {
        return this->rear == this->front;
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
        for (int i = (this->front + 1); i <= this->rear; i++) {
            cout << array[i] << ",";
        }
        cout << "]" << endl;
    }
};

int main() {

    QueueArray* Q = new QueueArray(10);
    Q->PrintQueue();
    Q->EnQueue(10); Q->PrintQueue();
    Q->EnQueue(20); Q->PrintQueue();
    Q->EnQueue(30); Q->PrintQueue();
    Q->EnQueue(40); Q->PrintQueue();
    Q->EnQueue(50); Q->PrintQueue();
    Q->EnQueue(60); Q->PrintQueue();
    Q->EnQueue(70); Q->PrintQueue();
    Q->EnQueue(80); Q->PrintQueue();
    Q->EnQueue(90); Q->PrintQueue();
    Q->EnQueue(100); Q->PrintQueue();
    Q->EnQueue(110); Q->PrintQueue();

    cout << "Front of Queue: " << Q->Front() << endl;
    cout << "Rear of Queue: " << Q->Rear() << endl;

    Q->DeQueue(); Q->PrintQueue();
    Q->DeQueue(); Q->PrintQueue();
    cout << "Front of Queue: " << Q->Front() << endl;
    cout << "Rear of Queue: " << Q->Rear() << endl;
    Q->EnQueue(5); Q->PrintQueue();
    Q->DeQueue(); Q->PrintQueue();
    Q->DeQueue(); Q->PrintQueue();
    Q->DeQueue(); Q->PrintQueue();
    Q->DeQueue(); Q->PrintQueue();
    Q->DeQueue(); Q->PrintQueue();
    Q->DeQueue(); Q->PrintQueue();
    Q->DeQueue(); Q->PrintQueue();
    Q->DeQueue(); Q->PrintQueue();
    Q->DeQueue(); Q->PrintQueue();
    cout << "Front of Queue: " << Q->Front() << endl;
    cout << "Rear of Queue: " << Q->Rear() << endl;
    Q->EnQueue(20); Q->PrintQueue();
    delete Q;
    Q->EnQueue(20); Q->PrintQueue();


    return 0;
}

