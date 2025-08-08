#include<iostream>
#include<queue>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <stack>
#include <iomanip> // For std::setw
#include <vector>
using namespace std;


struct Node {
	int data;
	int count;
	Node* left;
	Node* right;
	// default constructor explicitly initializes pointers to nullptr
	Node() : data(0), count(0), left(nullptr), right(nullptr) {};
	Node(int data) {
		this->data = data;
		this->count = 1; // Initialize count to 1 for a new node
		this->left = this->right = nullptr;
	}
};

struct BinarySearchTree {
	Node* root;

	BinarySearchTree() {
		root = nullptr;
	}
	// Helper function for a user-facing Insert
	void Insert(int data) {
		root = Insert(root, data);
	}

	// Complexity O(h) where h is height of tree 
	Node* Insert(Node* root, int data) {
		if (root == NULL || nullptr) {
			root = new Node(data);
			return root;
		}
		else if (data < root->data) {
			root->left = Insert(root->left, data);
		}
		else if (data > root->data) {
			root->right = Insert(root->right, data);
		}
		else if (data == root->data) {
			root->count++;
		}
		return root;
	}

	bool Search(Node* root, int data) { //searches the tree and returns true/false
		// O(h) since it visits each level only once
		if (root == nullptr) {
			return false;
		}
		if (data == root->data) {
			return true;
		}
		else if (data < root->data) {
			return Search(root->left, data); // Return the result of the recursive call
		}
		else { // data > root->data
			return Search(root->right, data); // Return the result of the recursive call
		}
	}

	Node* Find(Node* root, int value) { //finds a node and returns the node
		if (root == nullptr) {
			cout << "Node/value not found!" << endl;
			return nullptr;
		}
		if (root->data == value) {
			return root;
		}
		else if (value > root->data) {
			return Find(root->right, value); // Return the result
		}
		else { // value < root->data
			return Find(root->left, value); // Return the result
		}
	}

	int FindHeight(Node* root) { //Stack Trace the entire thing to understand
		if (root == nullptr) {
			return -1;
		}
		int leftDepth = FindHeight(root->left);
		int rightDepth = FindHeight(root->right);
		if (leftDepth > rightDepth) {
			return (leftDepth + 1);
		}
		else {
			return (rightDepth + 1);
		}
	}
	Node* FindMin(Node* root) { // O(h)
		while (root->left != nullptr) {
			root = root->left;
		}
		return root;
	}
	Node* FindMax(Node* root) { // O(h)
		while (root->right != nullptr) {
			root = root->right;
		}
		return root;
	}

	bool isBSTUtil(Node* root, int min, int max) { // utility function for isBinary Search Tree
		if (root == nullptr) { // Added base case
			return true;
		}
		if (root->data > min && root->data < max &&
			isBSTUtil(root->left, min, root->data) && isBSTUtil(root->right, root->data, max))
		{ // O(n): Checks if left subtree and right subtree are BSTs recursively visiting each node once
			return true;
		}
		else {
			return false;
		}
	}
	bool IsBinarySearchTree(Node* root) {
		return isBSTUtil(root, INT_MIN, INT_MAX);
	}

	Node* Delete(Node* root, int data) { // O(h+h+h) = O(h)
		if (root == nullptr) return root;
		else if (data < root->data) root->left = Delete(root->left, data); // move left 
		else if (data > root->data) root->right = Delete(root->right, data); // move right
		else { // coming to this line will mean element will either be found or not found stored in root
			// assuming element is found:
			if (root->count > 1) { // if duplicates are present
				root->count--;
			}
			else if (root->left == nullptr && root->right == nullptr) { // case 1: leaf node
				delete root;
				root = nullptr;
			}
			//case 2: One child
			else if (root->left == nullptr) {
				Node* temp = root;
				root = root->right;
				delete temp;
			}
			else if (root->right == nullptr) {
				Node* temp = root;
				root = root->left;
				delete temp;

			}
			else { //case 3: Two children
				Node* temp = FindMin(root->right);
				//we want the data & count field to only change to preserve all other links
				root->data = temp->data;
				root->count = temp->count;
				//Set the count to 0 to ensure successor gets deleted by deleteNode call
				temp->count = 0;
				root->right = Delete(root->right, temp->data); // reduces to case 1 where we are deleting leaf
			}
		}
		return root;
	}

	void LevelOrder(Node* root) {
		cout << "Level Order Traversal: ";
		if (root == nullptr) {
			return;
		}
		queue <Node*> Q;
		Q.push(root);
		while (!Q.empty()) {
			Node* current = Q.front();
			cout << current->data << "(" << current->count << ") ";
			Q.pop();
			if (current->left != nullptr) {
				Q.push(current->left);
			}
			if (current->right != nullptr) {
				Q.push(current->right);
			}

		}
		cout << endl;
	}

	void PreOrder(Node* root) {
		if (root == nullptr) {
			return;
		}
		cout << root->data << "(" << root->count << ") ";
		PreOrder(root->left);
		PreOrder(root->right);
	}
	void InOrder(Node* root) {
		if (root == nullptr) {
			return;
		}
		InOrder(root->left);
		cout << root->data << "(" << root->count << ") ";
		InOrder(root->right);
	}
	void PostOrder(Node* root) {
		if (root == nullptr) {
			return;
		}
		PostOrder(root->left);
		PostOrder(root->right);
		cout << root->data << "(" << root->count << ") ";
	}

	Node* GetSuccessor(Node* root, int value) {
		Node* current = Find(root, value);
		if (current == nullptr) { // Added check for non-existent node
			cout << "Node does not exist!" << endl;
			return nullptr;
		}
		if (current->right != nullptr) { // case 1: a right subtree exists
			return FindMin(current->right); // return the minimum of right subtree
		}
		else { // case 2 and 3
			Node* successor = nullptr;
			Node* ancestor = root;
			while (ancestor != current) {
				if (current->data < ancestor->data) { // handles case 2 & 3, successor always > current so go deeper
					successor = ancestor; // if left of parent, so far this is is the deepest node for which current is in left
					ancestor = ancestor->left; // traversing to the deepest possible node while current!=ancestor
				}
				else {
					ancestor = ancestor->right; //if current>ancestor, we need to go right
				}
			}
			return successor;
		}
	}
	Node* GetPredecessor(Node* root, int value) {
		Node* current = Find(root, value);
		if (current == nullptr) { // Added check for non-existent node
			cout << "Node does not exist!" << endl;
			return nullptr;
		}
		if (current->left != nullptr) { // case 1: There is a left subtree
			return FindMax(current->left);
		}
		else if (current->left == nullptr) { // case 2 & 3 handled by taking a walk from root node
			Node* predecessor = nullptr;
			Node* ancestor = root;
			while (ancestor != current) {
				if (current->data > ancestor->data) { // predecessor always < current, hence go deeper
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
	// Helper function to free all memory in the tree
	void DeleteTree(Node* root) {
		if (root == nullptr) {
			return;
		}
		DeleteTree(root->left);
		DeleteTree(root->right);
		delete root;
	}

};


int main() {

	BinarySearchTree bst;
	Node* bstNode = new Node(50);
	bst.root = bstNode;
	bst.root = bst.Insert(bst.root, 20);
	bst.root = bst.Insert(bst.root, 70);
	bst.root = bst.Insert(bst.root, 15);
	bst.root = bst.Insert(bst.root, 25);
	bst.root = bst.Insert(bst.root, 65);
	bst.root = bst.Insert(bst.root, 75);
	bst.root = bst.Insert(bst.root, 100);
	bst.root = bst.Insert(bst.root, 0);
	bst.root = bst.Insert(bst.root, 73);
	bst.root = bst.Insert(bst.root, 21);
	bst.root = bst.Insert(bst.root, 28);
	bst.root = bst.Insert(bst.root, 74);
	bst.root = bst.Insert(bst.root, 78);
	bst.root = bst.Insert(bst.root, 72);
	bst.root = bst.Insert(bst.root, 71);
	// deleting nodes
	bst.LevelOrder(bst.root);
	bst.root = bst.Delete(bst.root, 71);
	bst.LevelOrder(bst.root);
	bst.root = bst.Delete(bst.root, 70);
	bst.LevelOrder(bst.root);
	bst.root = bst.Delete(bst.root, 100);
	bst.LevelOrder(bst.root);

	cout << "Minimum is: " << bst.FindMin(bst.root)->data << endl;
	cout << "Maximum is: " << bst.FindMax(bst.root)->data << endl;
	cout << "Root Node is: " << bst.root->data << endl;
	cout << "Height of the tree is: " << bst.FindHeight(bst.root) << endl;
	cout << "Pre-order traversal: ";
	bst.PreOrder(bst.root);
	cout << endl;
	cout << "In-Order Traversal: ";
	bst.InOrder(bst.root);
	cout << endl;
	cout << "Post-order Traversal: ";
	bst.PostOrder(bst.root);
	cout << endl;
	cout << "Whether Binary Tree is Binary Search Tree: ";
	if (bst.IsBinarySearchTree(bst.root)) cout << "true";
	else cout << "false";
	cout << endl;
	int a;
	cout << "Enter number to search data and to find its successor and predecessor: ";
	cin >> a;
	if (bst.Search(bst.root, a)) cout << "Found" << endl;
	else cout << "Not found" << endl;
	Node* b = bst.GetSuccessor(bst.root, a);
	Node* c = bst.GetPredecessor(bst.root, a);
	cout << "Successor is: " << b->data << "\tPredecessor is: " << c->data << endl;

	bst.root = bst.Insert(bst.root, 20);
	bst.root = bst.Insert(bst.root, 65);
	bst.root = bst.Insert(bst.root, 50);
	bst.LevelOrder(bst.root);
	cout << "Pre-order traversal: ";
	bst.PreOrder(bst.root);
	cout << endl;
	cout << "In-Order Traversal: ";
	bst.InOrder(bst.root);
	cout << endl;
	cout << "Post-order Traversal: ";
	bst.PostOrder(bst.root);
	cout << endl;

	bst.root = bst.Delete(bst.root, 65);
	bst.LevelOrder(bst.root);
	bst.root = bst.Delete(bst.root, 50);
	bst.LevelOrder(bst.root);
	bst.root = bst.Delete(bst.root, 50);
	bst.LevelOrder(bst.root);



	return 0;
}
