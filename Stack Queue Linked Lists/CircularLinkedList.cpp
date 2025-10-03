#include <string>
#include <vector>
#include <ostream>
#include <iostream>
#include <strstream>
#include <sstream>
#include <cstdlib>
#include <array>
#include <iomanip>
#include <cmath>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value) { // constructor for creating a new node
        data = value;
        next = nullptr;
    }
};

Node* head;
Node* tail = nullptr;

int ListLength();
void PrintList();
void InsertAtHead(int);
void InsertAtEnd(int);
void InsertAt(int, int);
void DeleteAt(int);
void DeleteList();
bool IsCircular(); // checks if list is circular or not 
void PrintRecursion(Node*);

int main() {
    Node* first = new Node(2);
    Node* second = new Node(3);
    Node* last = new Node(4);

    first->next = second;
    second->next = last;
    last->next = first;
    head = first;
    tail = last;

    PrintList();
    InsertAtHead(1); PrintList();
    InsertAtEnd(6); PrintList();
    InsertAt(5, 5); PrintList();
    InsertAt(0, 1); PrintList();
    InsertAt(7, 8); PrintList();
    InsertAt(3, 3); PrintList();
    DeleteAt(3); PrintList();
    DeleteAt(1); PrintList();
    DeleteAt(7); PrintList();
    DeleteAt(0); DeleteAt(9); PrintList();
    cout << "Length of list: " << ListLength() << endl;
    if (IsCircular) {
        cout << "Linked list is circular" << endl;
    }
    else {
        cout << "Linked list is not circular" << endl;
    }
    PrintRecursion(head);
    DeleteList(); PrintList();



    return 0;
}

int ListLength() {
    Node* current = head;
    int count = 0;
    if (head == nullptr) {
        return 0;
    }
    do {
        current = current->next;
        count++;
    } while (current != head);

    return count;
}

void PrintList() {
    Node* current = head;
    cout << "head->";
    if (head == nullptr) {
        cout << "null" << endl;
        return;
    }
    do {
        cout << current->data << "->";
        if (current == tail) cout << "tail";
        current = current->next;
    } while (current != head);
    cout << endl;
}

void InsertAtHead(int x) {
    Node* newNode = new Node(x);

    if (head == nullptr) { // if list is empty
        head = tail = newNode;
        newNode->next = newNode;
    }
    else {
        newNode->next = head;
        head = newNode;
        tail->next = newNode;
    }
}
void InsertAtEnd(int x) {
    Node* newNode = new Node(x);

    if (head == nullptr) {
        head = tail = newNode;
        newNode->next = newNode;
    }
    else {
        newNode->next = head;
        tail->next = newNode;
        tail = newNode;
    }
}
void InsertAt(int data, int position) {
    if (position < 1) {
        cout << "Invalid position!" << endl;
        return;
    }
    if (position == 1) {
        InsertAtHead(data);
        return;
    }
    Node* current = head; // second case if it's not beginning
    // Traverse to (position - 1)th node, unless we wrap around
    for (int i = 0; i < position - 2 && current->next != head; i++) {
        current = current->next;
    }
    if (current == tail || current->next == head) { // if we are at the last node
        InsertAtEnd(data);
        return;
    }
    else {
        Node* newNode = new Node(data); // make new node
        newNode->next = current->next; // make new node point to the nth node. this is done first as we will lose this link if done later
        current->next = newNode; // make (n-1)th node point to this new node
    }
}
void DeleteAt(int position) {
    if (position <= 0 || head == nullptr || position > ListLength()) {
        cout << "Invalid Deletion" << endl;
        return;
    }
    else if (position == 1) { // deleting at head
        Node* nodeToDelete = head;
        tail->next = head->next;
        head = head->next;
        nodeToDelete->next = nullptr;
        delete nodeToDelete;
    }
    else { // not deleting at head 
        Node* temp = head;
        for (int i = 0; i < (position - 2); i++) { // travel to the (n-1)th node
            temp = temp->next;
        }
        Node* nodeToDelete = temp->next; // target the node to delete
        if (temp->next == tail) { // if we are deleting the last node
            temp->next = head;
            nodeToDelete->next = nullptr;
            tail = temp; // tail needs to be updated
        }
        else {
            temp->next = temp->next->next;
            nodeToDelete->next = nullptr;
        }
        delete nodeToDelete;
    }
}

void DeleteList() {
    if (head == nullptr) return;

    tail->next = nullptr; // break the circular link
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }

    head = nullptr;
    tail = nullptr;
}
bool IsCircular() {
    if (head == nullptr) return false;
    Node* temp = head->next;
    while (temp != nullptr && temp != head) { // travels to the head node if circular 
        temp = temp->next;
    }
    return temp == head; //temp will be head if circular, won't be head if not circular
}

void PrintRecursion(Node* temp) {
    static bool visitedHead = false;
    if (temp == head && visitedHead) return; // Terminate recursion when back at head
    visitedHead = true;
    cout << temp->data << "->";
    PrintRecursion(temp->next);
}