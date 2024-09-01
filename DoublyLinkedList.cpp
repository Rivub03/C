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

Node* GetNewNode(int x) { // just creates a new node and returns it with no populated fields
    Node* newNode = new Node; 
    newNode->data = x;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void InsertAtHead(int);
void InsertAtTail(int);
void Print();
void ReversePrint();
void Insert_at(int, int);
void Delete_at(int);


int main()
{
    head = NULL;

    InsertAtHead(2); Print(); ReversePrint();
    InsertAtHead(4); Print(); ReversePrint();
    InsertAtTail(8); Print(); ReversePrint();
    Insert_at(7, 2); Print(); ReversePrint();
    Insert_at(10, 5); Print(); ReversePrint();
    Insert_at(12, 1); Print(); ReversePrint();
    Delete_at(3); Print();
    Delete_at(5); Print();
    Delete_at(4); Print();
    Delete_at(1); Print();

    return 0;
}

void InsertAtHead(int x) {
    Node* temp = head; 
    Node* newNode = GetNewNode(x); //pointer to structure since we are dynamically allocating memory for a node
    if (head == NULL) {
        head = newNode; //if list is empty head will point to this new node which will be first node
        return;
    }
    head->prev = newNode; // adjusting the previous link of the first node 
    newNode->next = head; // making newnode point to the previously first node, making it the second node
    head = newNode; // making head point to this newnode, making it the first node

}
void InsertAtTail(int x) { 
    Node* temp = head;  //very easy append function
    Node* newNode = GetNewNode(x);
    if (head == NULL) {
        head = newNode;
        return;
    }
    while (temp->next != NULL) { //travels to the last node and stops
        temp = temp->next; 
    }
    temp->next = newNode; // newNode becomes last node
    newNode->prev = temp; 
}
void Print() {
    Node* temp = head;
    cout << "Forward: " << endl;
    while (temp != NULL) {
        cout << temp->data << "<->";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}
void ReversePrint() {
    Node* temp = head;
    if (temp == NULL) return;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    cout << "Reverse: " << endl;
    while (temp != NULL) {
        cout << temp->data << "<->";
        temp = temp->prev;
    }
    cout <<"NULL" << endl;
}

void Insert_at(int newElement, int position) {
    Node* newNode = GetNewNode(newElement);
    if (position == 1) { //if we are inserting at head 
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    else { //if we are not inserting at head. This else block is important or else we'll have an infinite loop since 1-2 =-1 
        Node* temp = head;
        for (int i = 0; i < position - 2; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next = newNode;
        if (newNode->next != NULL) { //if we are inserting at tail, this won't apply
            newNode->next->prev = newNode; //fixing the link of the next node to point to the previous node 
        }
    }
}

void Delete_at(int position) {
    if (position == 1 && head != NULL) { // Deleting the head node
        Node* nodetoDelete = head;
        head = head->next; // Move head to the next node
        delete nodetoDelete;
        if (head != NULL) { // If the list isn't empty after deletion
            head->prev = NULL; // Set the new head's previous link to NULL
        }
    }
    else { //if we are not deleting at head
        Node* temp = head;
        for (int i = 1; i < position - 1; i++) { // Travel to the (position-1)th node
            if (temp == NULL || temp->next == NULL) { // Check for out-of-bounds positions
                cout << "Position out of bounds." << endl;
                return;
            }
            temp = temp->next;
        }

        Node* nodeToDelete = temp->next; // Target node to delete

        if (nodeToDelete == NULL) { // If position is beyond the list's length
            cout << "Position out of bounds." << endl;
            return;
        }

        temp->next = nodeToDelete->next; // Bypass the node to be deleted

        if (nodeToDelete->next != NULL) { // If we're not at the end. This handles the unique case of deleting at the end
            nodeToDelete->next->prev = temp; // where the next node's previous link will point to the node before the node to be deleted. 
        }

        delete nodeToDelete; // Free the memory of the deleted node
    }
}

