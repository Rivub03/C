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
};
Node* head;

void createBasicLinkedList(); //Linked List Basic Implementation of two nodes
void Print();
void InsertBeginning(int);
void Insert_at(int, int);
void Delete_at(int);
void Insert_at_end(int);
Node* ReverseIteratively(Node*);
void PrintForwardRecursion(Node*);
void PrintBackwardRecursion(Node*);
void ReverseRecursion(Node*);

int main()
{
    createBasicLinkedList();

    //Insert node at beginning code
    head = NULL;
    cout << "How many numbers? ";
    int n, i, x;
    cin >> n;
    for (i = 0; i < n; i++) {
        cout << "Enter Number: ";
        cin >> x;
        InsertBeginning(x);
        Print();
    }

    //Insert at nth code
    Insert_at(3, 3);
    Insert_at_end(5);
    Print();
    Insert_at(8, 1);
    Print();
    Delete_at(1);
    Print();
    Delete_at(4);
    Print();


    
    return 0;
}

void createBasicLinkedList() { 
    head = NULL;

    // Create the first node and point head to it
    Node* temp = new Node;
    temp->data = 2;
    temp->next = NULL;
    head = temp;

    // Create the second node
    temp = new Node;
    temp->data = 4;
    temp->next = NULL;

    // Find the last node and link the new node to the end of the list
    Node* temp1 = head;
    while (temp1->next != NULL) { //reaches the last node of the list and exits during false check
        temp1 = temp1->next; //traverses the entire list and reaches the last node 
    }
    temp1->next = temp;

    // Print the entire linked list
    temp1 = head;
    while (temp1 != NULL) { // the previous while loop will need to be run again to print the last node. This is because in the temp->next loop, the loop will go to the last node and immediately exit. 
        cout << temp1->data << " "; // this problem could've been overcome by having this line below temp1 = temp1->next
        temp1 = temp1->next;        // but that would make us skip the first element
    }
    cout << endl;

    // Free the allocated memory (optional, but good practice)
    temp1 = head;
    while (temp1 != NULL) { 
        Node* next = temp1->next;
        delete temp1;
        temp1 = next;
    }
}

void InsertBeginning(int x) { // time complexity O(1)
    Node* temp = new Node; // creates new node (remember there are two cases: empty list or 
    temp->data = x; // populates
    temp->next = head; // makes new node point to whatever head node was pointing to, which would be the first nod in the list 
    head = temp; //makes head point to new node instead of first node in the list

}
void Print() {
    Node* temp = head;
    cout << "List is: head->";
    while (temp != NULL) {  //we use temp instead of temp->next here because that will make the fucntion skip the last element
        cout << temp->data << "->";
        temp = temp->next;
    }
    cout << "NULL"<<endl;

    cout << endl;
}
void Insert_at(int data, int n) { //time complexity O(n)
    Node* temp1 = new Node; // make new node
    temp1->data = data;
    temp1->next = NULL;
    if (n == 1) { // first case if we want to insert at beginning
        temp1->next = head; //same code as insert at beginning
        head = temp1;
        return;
    }
    Node* temp2 = head; // second case if it's not beginning
    for (int i = 0; i < n - 2; i++) { // we want to travel to the (n-1)th node. Since we are already at head, we need the 
        temp2 = temp2->next;          // loop to run (n-2) times
    }
    temp1->next = temp2->next; // make new node point to the nth node. this is done first as we will lose this link if done later
    temp2->next = temp1; // make (n-1)th node point to this new node
}
void Insert_at_end(int x) { //time complexity O(n) - this is an apppend function
    Node* temp = new Node; // create new node
    temp->data = x;
    temp->next = NULL;

    Node* temp1 = head;
    while (temp1->next != NULL) { //traverse 
        temp1 = temp1->next;
    }
    temp1->next = temp;

}
void Delete_at(int n) {
    Node* temp1 = head; 
    if (n == 1) { //deletion at head
        head = temp1->next; //fixes the link
        delete temp1; //frees the memory by deleting the node
        return;
    }
    for (int i = 0; i < n - 2; i++) {
        temp1 = temp1->next; //temp1 points to (n-1)th node
        Node* temp2 = temp1->next; //this is the nth node to be deleted
        temp1->next = temp2->next; // temp1 now points to the next node temp2 is pointing at (n+1)th node. We have fixed the link
        delete temp2; //freeing the memory by deleting the node 
    }
}
Node* ReverseIteratively(Node* head) {  
    Node* current, * prev, * next;
    current = head;                    
    prev = NULL;
    while (current != NULL) {
        next = current->next;  // next will be set to current->next always to keep track of what the next node is 
        current->next = prev;     //The current node's link is set to the previous node as we are trying to reverse the list. at the first iteration this will be NULL and this is correct
        prev = current;    // the previous node is set to current once the link has been adjusted
        current = next;    // current node is set to the next node so that we can this process all over again in the next iteration of the while loop
    }
    head = prev;
    return head; 
}

void ReverseRecursion(Node* p) {
    if (p->next == NULL) {
        head = p;
        return;
    }
    ReverseRecursion(p->next);
    Node* q = p->next;
    q->next = p;
    p->next = NULL; 
    
}

void PrintForwardRecursion(Node* p) { //usually will take head as input
    if (p == NULL) {  //base case 
        return;
    }
    cout << p->data; 
    PrintForwardRecursion(p->next);
}

void PrintBackwardRecursion(Node* p) {
    if (p == NULL) {
        return;
    }
    PrintBackwardRecursion(p->next); //uses the stack property by placing this statement before the print statement to print backwards. 
    cout << p->data;

}
