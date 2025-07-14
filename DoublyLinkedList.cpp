#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

Node* head;
Node* tail;

Node* GetNewNode(int x) { // just creates a new node and returns it with no populated fields
    Node* newNode = new Node;
    newNode->data = x;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}

void InsertAtHead(int);
void InsertAtTail(int); //appends by traversing the entire list O(n)
void Append(int); // appends using tail pointer O(1)
void PrintForward();
void PrintBackward(); // prints backward by traversing to the end of the list O(n) 
void PrintBackwardTail(); // prints backward by using tail pointer O(n) 
void Insert_at(int, int);
void Delete_at(int);
void DeleteList();
int ListLength();

int main()
{
    Node* newNode = GetNewNode(2); // creates a node 
    head = newNode; // createsa DLL of one node

    Node* secondNode = GetNewNode(3); //creates a DLL of two nodes
    newNode->next = secondNode;
    secondNode->prev = newNode;
    tail = secondNode;

    PrintForward();
    PrintBackward();
    PrintBackwardTail();
    InsertAtHead(1); PrintForward();
    InsertAtTail(4); PrintForward();
    Append(6); PrintForward();
    Insert_at(0, 1); PrintForward();
    Insert_at(5, 6); PrintForward();
    Insert_at(8, 8); PrintForward();
    Insert_at(7, 8); PrintForward();
    Delete_at(1); PrintForward();
    Delete_at(8); PrintForward();
    Insert_at(10, 4); PrintForward(); Delete_at(4); PrintForward();
    PrintBackward(); PrintBackwardTail();
    cout << "Length of list = " << ListLength();
    DeleteList();
    return 0;
}



void PrintForward() {
    Node* temp;
    temp = head;
    cout << "DLL forward: head->";
    while (temp != nullptr) {
        cout << temp->data << "<->";
        if (temp == tail) {
            cout << "tail";
        }
        temp = temp->next;
    }
    cout << endl;
}

void PrintBackward() {
    Node* temp;
    temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    cout << "DLL backward: tail->";
    while (temp != nullptr) {
        cout << temp->data << "<->";
        if (temp == head) {
            cout << "head";
        }
        temp = temp->prev;
    }
    cout << endl;
}

void PrintBackwardTail() {
    Node* temp;
    temp = tail;
    cout << "DLL backward: tail->";
    while (temp != nullptr) {
        cout << temp->data << "<->";
        if (temp == head) {
            cout << "head";
        }
        temp = temp->prev;

    }
    cout << endl;

}

void InsertAtHead(int x) {
    Node* newNode = GetNewNode(x);
    if (head == nullptr) {
        head = tail = newNode; //if list is empty head will point to this new node which will be first node
        return;
    }
    newNode->next = head;  // making newnode point to the previously first node, making it the second node
    head->prev = newNode; // adjusting the previous link of the first node 
    head = newNode; // making head point to this newnode, making it the first node
}
void InsertAtTail(int x) {
    Node* newNode = GetNewNode(x);
    Node* temp = head;
    if (head == NULL) {
        head = tail = newNode;
        return;
    }
    while (temp->next != nullptr) { //travels to the last node and stops
        temp = temp->next;
    }
    temp->next = newNode; // newNode becomes last node
    newNode->prev = temp;
    tail = newNode;
}
void Append(int x) {
    Node* newNode = GetNewNode(x);
    if (head == NULL) {
        head = tail = newNode;
        return;
    }
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
}
void Insert_at(int x, int n) {
    if (n <= 0) {
        cout << "Invalid Postion!" << endl;
        return;
    }
    else if (n == 1) { //if we are inserting at head 
        InsertAtHead(x);
        return;
    }
    else { //if we are not inserting at head. This else block is important or else we'll have an infinite loop since 1-2 =-1 
        Node* temp = head;
        for (int i = 0; i < n - 2 && temp != nullptr; i++) { // travel to the (n-1)th node
            temp = temp->next;
        }
        if (temp == nullptr) {
            cout << "Position out of bounds!" << endl;
            return;
        }
        else if (temp == tail) { // if we are appending or inserting at the end 
            Append(x);
            return;
        }
        else { // if we are inserting in the middle 
            Node* newNode = GetNewNode(x);
            newNode->next = temp->next; //making newnode point to the next node
            newNode->prev = temp; //making newnode point to the previous node
            temp->next->prev = newNode; //making next node point to newnode
            temp->next = newNode; //making previous node point to newnode
        }
    }
}
void Delete_at(int n) {
    if (head == nullptr || n <= 0) {
        cout << "Invalid Deletion!" << endl;
        return;
    }
    else if (n == 1) { // Deleting the head node
        Node* nodeToDelete = head;
        head = head->next; // Move head to the next node
        if (head != nullptr) { // If the list isn't empty after deletion
            head->prev = nullptr; // Set the new head's previous link to NULL
        }
        else {
            tail = nullptr;  // List became empty
        }
        delete nodeToDelete;
        return;
    }
    else { // if we are not deleting at head
        Node* temp = head;
        for (int i = 0; i < n - 2 && temp != nullptr; i++) { // travel to the (n-1)th node
            temp = temp->next;
        }
        if (temp == nullptr || temp->next == nullptr) { // Check for out-of-bounds positions
            cout << "Out of bounds!" << endl;
            return;
        }
        else if (temp->next == tail) { // if we are deleting the last node
            delete temp->next;
            temp->next = nullptr;
            tail = temp;
        }
        else { // if we are deleting a node in the middle
            Node* nodeToDelete = temp->next; // target node to delete
            temp->next->next->prev = temp; // bypassing node to delete, fixing the previous link of the next node
            temp->next = temp->next->next; // bypassing node to delete, fixing next node of the previous node
            delete nodeToDelete; // free memory
        }
    }
}
void DeleteList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
}
int ListLength() {
    int count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}