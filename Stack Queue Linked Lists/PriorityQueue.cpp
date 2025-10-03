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

struct PriorityQueueSortedInsert {
    int front, rear;
    int size;
    int count;
    PQNode* array;
    PriorityQueueSortedInsert(int size) {
        this->size = size;
        this->front = this->rear = this->count = 0;
        this->array = new PQNode[size];
    }
    ~PriorityQueueSortedInsert() {
        delete[] array;
        array = nullptr;
    }

    void EnQueue(PQNode node) {
        if (IsFull()) {
            cout << "Overflow! Queue is full!" << endl;
            return;
        }
        cout << "Enqueueing " << node.data << endl;
        int index; // index to insert (actually, as seen below, it will find index - 1)
        if (count == 0) {
            array[0] = node;
            count++;
            return;
        }
        // we need to iterate from the end of the queue, moving left and checking each element until we can match priorities
        for (index = rear; index >= 0 && node.priority < array[index].priority; index--) {
            array[index + 1] = array[index]; // will shift all the elements to the right until it reaches an element of equal priority
        }

        array[index + 1] = node; // array[index] will be pointing to an element of equal priority, hence [index + 1]
        count++;
        rear++;

    }

    int DeQueue() {
        if (IsEmpty()) {
            cout << "Underflow! Queue is empty!" << endl;
            return INT32_MIN;
        }
        else {
            PQNode x;
            x = array[this->front];
            this->front++;
            cout << "Dequeueing " << x.data << " with priority " << x.priority << endl;
            return x.data;
        }
    }
    int GetSize() {
        return this->rear - this->front;
    }

    bool IsFull() {
        return this->rear >= (this->size - 1);
    }

    bool IsEmpty() {
        return this->rear < this->front;
    }

    int Front() {
        if (IsEmpty()) {
            cout << "Empty " << endl;
            return INT32_MIN;
        }
        cout << "Front: " << array[this->front].data << endl;
        return array[this->front].data;
    }

    int Rear() {
        if (IsEmpty()) {
            cout << "Empty " << endl;
            return INT32_MIN;
        }
        cout << "Rear: " << array[this->rear].data << endl;
        return array[this->rear].data;
    }
    void PrintQueue() {
        cout << "Queue: [";
        for (int i = this->front; i <= this->rear; i++) {
            cout << array[i].data << ",";
        }
        cout << "]" << endl;
    }
};

struct PriorityQueueSortedDequeue {
    int front, rear;
    int size;
    int count;
    PQNode* array;
    PriorityQueueSortedDequeue(int size) {
        this->size = size;
        this->front = this->rear = this->count = 0;
        this->array = new PQNode[size];
    }
    ~PriorityQueueSortedDequeue() {
        delete[] array;
        array = nullptr;
    }

    void EnQueue(PQNode node) {
        if (IsFull()) {
            cout << "OverFlow! Queue is full" << endl;
            return;
        }
        array[rear] = node;
        rear++;
        count++;
    }

    int DeQueue() {
        if (IsEmpty()) {
            cout << "Underflow! Queue is empty" << endl;
            return NULL;
        }
        int minPriorityIndex = 0;
        int minPriority = array[0].priority;
        int value = array[0].data;
        // we will scan through the entire queue to find the element with the lowest priority
        for (int i = 0; i < count; i++) {
            if (array[i].priority < minPriority) {
                minPriority = array[i].priority;
                minPriorityIndex = i;
            }
        }
        value = array[minPriorityIndex].data;
        // once found, we will need to shift the elements to the left from that index till end of the queue
        for (int i = minPriorityIndex; i < count - 1; i++) {
            array[i] = array[i + 1];
        }
        rear--;
        count--;
        cout << "Dequeuing " << value << " with priority " << minPriority << endl;
        return value;

    }
    int GetSize() {
        return this->rear - this->front;
    }

    bool IsFull() {
        return this->rear >= this->size;
    }

    bool IsEmpty() {
        return this->rear < this->front;
    }

    int Peek() {
        if (IsEmpty()) {
            cout << "Empty " << endl;
            return INT32_MIN;
        }
        //same logic as dequeue, only no shifting required. 
        front = 0;
        int minPriority = array[0].priority;
        int value = array[0].data;
        for (int i = 0; i <= count - 1; i++) {
            if (array[i].priority < minPriority) {
                minPriority = array[i].priority;
                front = i;
            }
        }
        cout << "Front: " << array[front].data << endl;
        return array[front].data;
    }

    int Rear() {
        if (IsEmpty()) {
            cout << "Empty " << endl;
            return INT32_MIN;
        }
        cout << "Rear: " << array[this->rear - 1].data << endl;
        return array[this->rear - 1].data;
    }
    void PrintQueue() {
        cout << "Queue: [";
        for (int i = 0; i <= count - 1; i++) {
            cout << array[i].data << ",";
        }
        cout << "]" << endl;
    }
};



int main() {

    cout << "--------------Sorted Enqueue------------------" << endl;
    PriorityQueueSortedInsert* Q = new PriorityQueueSortedInsert(8);

    //Enqueuing
    Q->EnQueue(PQNode(5, 1)); Q->EnQueue(PQNode(8, 1));
    Q->EnQueue(PQNode(7, 3)); Q->EnQueue(PQNode(9, 2));
    Q->PrintQueue(); Q->Front(); Q->Rear();
    Q->EnQueue(PQNode(11, 1)); Q->EnQueue(PQNode(12, 3));
    Q->EnQueue(PQNode(13, 2)); Q->EnQueue(PQNode(2, 1));
    Q->PrintQueue(); Q->Front(); Q->Rear();
    Q->EnQueue(PQNode(32, 2)); Q->PrintQueue();
    // Dequeueing 
    Q->DeQueue();  Q->DeQueue();  Q->DeQueue();  Q->DeQueue();
    Q->PrintQueue(); Q->Front(); Q->Rear();
    Q->DeQueue();  Q->DeQueue();  Q->DeQueue();  Q->PrintQueue();
    Q->DeQueue(); Q->PrintQueue();
    Q->DeQueue();
    delete Q;

    cout << "--------------Sorted Dequeue------------------" << endl;
    PriorityQueueSortedDequeue* Q1 = new PriorityQueueSortedDequeue(8);

    //Enqueuing
    Q1->EnQueue(PQNode(5, 1)); Q1->EnQueue(PQNode(8, 1));
    Q1->EnQueue(PQNode(7, 3)); Q1->EnQueue(PQNode(9, 2));
    Q1->PrintQueue(); Q1->Peek(); Q1->Rear();
    Q1->EnQueue(PQNode(11, 1)); Q1->EnQueue(PQNode(12, 3));
    Q1->EnQueue(PQNode(13, 2)); Q1->EnQueue(PQNode(2, 1));
    Q1->PrintQueue(); Q1->Peek(); Q1->Rear();
    Q1->EnQueue(PQNode(32, 2)); Q1->PrintQueue();
    // Dequeueing 
    Q1->DeQueue(); Q1->PrintQueue();
    Q1->DeQueue(); Q1->PrintQueue();
    Q1->DeQueue(); Q1->PrintQueue();
    Q1->DeQueue(); Q1->PrintQueue();
    Q1->Peek(); Q1->Rear();
    Q1->DeQueue(); Q1->PrintQueue();
    Q1->DeQueue(); Q1->PrintQueue();
    Q1->DeQueue(); Q1->PrintQueue();
    Q1->DeQueue(); Q1->PrintQueue();
    Q1->DeQueue(); Q1->PrintQueue();
    delete Q1;

    return 0;
}