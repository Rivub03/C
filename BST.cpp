/* Binary tree - Level Order Traversal */
#include<iostream>
#include<queue>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;
};

// Function to print Nodes in a binary tree in Level order
void LevelOrder(Node* root) {
	if (root == NULL) return;
	queue<Node*> Q;
	Q.push(root);
	//while there is at least one discovered node
	while (!Q.empty()) {
		Node* current = Q.front();
		Q.pop(); // removing the element at front
		cout << current->data << " ";
		if (current->left != NULL) Q.push(current->left);
		if (current->right != NULL) Q.push(current->right);
	}
}
void Preorder(struct Node* root) {
	// base condition for recursion
	// if tree/sub-tree is empty, return and exit
	if (root == NULL) return;

	printf("%i ", root->data); // Print data
	Preorder(root->left);     // Visit left subtree
	Preorder(root->right);    // Visit right subtree
}

void Inorder(Node* root) {
	if (root == NULL) return;

	Inorder(root->left);       //Visit left subtree
	printf("%i ", root->data);  //Print data
	Inorder(root->right);      // Visit right subtree
}

void Postorder(Node* root) {
	if (root == NULL) return;

	Postorder(root->left);    // Visit left subtree
	Postorder(root->right);   // Visit right subtree
	printf("%i ", root->data); // Print data
}
int findMin(Node* root) {
	if (root == NULL) {
		cout << "Error: Tree is Empty";
		return -1;
	}
	Node* current = root;
	while (current->left != NULL) {
		current = current->left;
	}
	return current->data;
}
int findMax(Node* root) {
	if (root == NULL) {
		return 0;
	}
	Node* current = root;
	while (current->right != NULL) {
		current = current->right;
	}
	return current->data;
}
int FindHeight(Node* root) {
	if (root == NULL) {
		return -1;
	}
	int leftdepth = FindHeight(root->left);
	int rightdepth = FindHeight(root->right);
	if (leftdepth > rightdepth) {
		return (leftdepth + 1);
	}
	else {
		return (rightdepth + 1);
	}
}

// Function to Insert Node in a Binary Search Tree
Node* Insert(Node* root, int data) {
	if (root == NULL) {
		root = new Node();
		root->data = data;
		root->left = root->right = NULL;
	}
	else if (data <= root->data) root->left = Insert(root->left, data);
	else root->right = Insert(root->right, data);
	return root;
}
//To search an element in BST, returns true if element is found
bool Search(Node* root, int data) {
	if (root == NULL) {
		return false;
	}
	else if (root->data == data) {
		return true;
	}
	else if (data <= root->data) {
		return Search(root->left, data);
	}
	else {
		return Search(root->right, data);
	}
}

bool IsSubtreeGreater(Node* root, int value) {
	if (root == NULL) return true;
	if (root->data > value && IsSubtreeGreater(root->left, value)
		&& IsSubtreeGreater(root->right, value)) {
		return true;
	}
	else {
		return false;
	}

}
bool IsSubtreeLesser(Node* root, int value) {
	if (root == NULL) return true;
	if (root->data < value && IsSubtreeLesser(root->left, value)
		&& IsSubtreeLesser(root->right, value)) {
		return true;
	}
	else {
		return false;
	}

}

bool IsBinarySearchTree(Node* root) {
	if (root == NULL) return true;
	if (IsSubtreeLesser(root->left, root->data) && IsSubtreeGreater(root->right, root->data)
		&& IsBinarySearchTree(root->left) && IsBinarySearchTree(root->right)) {
		return true;
	}
	else {
		return false;
	}
}

bool isBSTUtil(Node* root, int minValue, int maxValue) {
	if (root == NULL) {
		return true;
	}
	if (root->data > minValue && root->data < maxValue &&
		isBSTUtil(root->left, minValue, root->data) && isBSTUtil(root->right, root->data, maxValue)) {

		return true;
	}
	else {
		return false;
	}
}

bool isbst(Node* root) {
	return isBSTUtil(root, INT_MIN, INT_MAX); //passes the minimum and maximum values of integers which is pre-defined as macros
}

Node* FindMin(Node* root) //returns Node instead of node->data
{
	while (root->left != NULL) root = root->left;
	return root;
}

Node* FindMax(Node* root) //returns Node instead of node->data
{
	while (root->right != NULL) root = root->right;
	return root;
}


Node* Delete(Node* root, int data) {
	if (root == NULL) return root;
	else if (data < root->data) root->left = Delete(root->left, data);
	else if (data > root->data) root->right = Delete(root->right, data);
	// Wohoo... I found you, Get ready to be deleted	
	else {
		// Case 1:  No child
		if (root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
		}
		//Case 2: One child 
		else if (root->left == NULL) {
			Node* temp = root;
			root = root->right;
			delete temp;
		}
		else if (root->right == NULL) {
			Node* temp = root;
			root = root->left;
			delete temp;
		}
		// case 3: 2 children
		else {
			Node* temp = FindMin(root->right);
			root->data = temp->data;
			root->right = Delete(root->right, temp->data);
		}
	}
	return root;
}

//Function to find some data in the tree
Node* Find(Node* root, int data) {
	if (root == NULL) return NULL;
	else if (root->data == data) return root;
	else if (root->data < data) return Find(root->right, data);
	else return Find(root->left, data);
}

//Function to find Inorder Successor in a BST
Node* Getsuccessor(Node* root, int data) {

	if (!Search(root, data)) { //handling exceptions
		exit(0);
	}
	// Search the Node - O(h)
	Node* current = Find(root, data);
	if (current == NULL) return NULL;
	if (current->right != NULL) {  //Case 1: Node has right subtree
		return FindMin(current->right); // O(h)
	}
	else {   //Case 2: No right subtree  - O(h)
		Node* successor = NULL;
		Node* ancestor = root;
		while (ancestor != current) {
			if (current->data < ancestor->data) {
				successor = ancestor; // so far this is the deepest node for which current node is in left
				ancestor = ancestor->left;
			}
			else
				ancestor = ancestor->right;
		}
		return successor;
	}
}

Node* GetPredecessor(Node* root, int value) {
	Node* current = Find(root, value);
	if (current->left != NULL) {
		return FindMax(current->left);
	}
	else if (current->left = NULL) {
		Node* ancestor = root;
		Node* predecessor = NULL;
		while (ancestor != current) {
			if (ancestor->data < current->data) {
				predecessor = ancestor;
				ancestor = ancestor->right;
			}
			else {
				ancestor = ancestor->left;
			}
		}
		return predecessor;
	}


}


int main() {
	Node* root = NULL;
	//root = Insert(root, 50);
	//srand(time(0)); // to randomly generate numbers without repetition
	/*for (int i = 0; i < 15; i++) {
		int x = rand() % 100;
		root = Insert(root, x);
		cout << x << ", ";
	}
	cout << endl; */
	root = Insert(root, 50);
	root = Insert(root, 20);
	root = Insert(root, 70);
	root = Insert(root, 15);
	root = Insert(root, 25);
	root = Insert(root, 65);
	root = Insert(root, 75);
	root = Insert(root, 100);
	root = Insert(root, 0);
	root = Insert(root, 73);
	root = Insert(root, 21);
	root = Insert(root, 28);
	root = Insert(root, 74);
	root = Insert(root, 78);
	root = Insert(root, 72);
	root = Insert(root, 71);
	root = Delete(root, 70);
	root = Delete(root, 15);
	cout << "Minimum is: " << findMin(root) << endl;
	cout << "Maximum is: " << findMax(root) << endl;
	cout << "Root Node is: " << root->data << endl;
	cout << "Height of the tree is: " << FindHeight(root) << endl;
	cout << "Level order traversal: ";
	LevelOrder(root);
	cout << endl;
	cout << "Pre-order traversal: ";
	Preorder(root);
	cout << endl;
	cout << "In-Order Traversal: ";
	Inorder(root);
	cout << endl;
	cout << "Post-order Traversal: ";
	Postorder(root);
	cout << endl;
	cout << "Whether Binary Tree is Binary Search Tree: ";
	if (isbst(root)) cout << "true";
	else cout << "false";
	cout << endl;
	cout << "Whether Binary Tree is Binary Search Tree (inefficient): ";
	if (IsBinarySearchTree(root)) cout << "true";
	else cout << "false";
	cout << endl;
	int a;
	cout << "Enter number to search data and to find its successor and predecessor: ";
	cin >> a;
	if (Search(root, a)) cout << "Found" << endl;
	else cout << "Not found";
	Node* b = Getsuccessor(root, a);
	Node* c = GetPredecessor(root, a);
	cout << "Successor is: " << b->data << "\tPredecessor is: " << c->data << endl;

}
