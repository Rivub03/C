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

struct BinaryTree {
	Node* root;
	BinaryTree() {
		root = nullptr;
	}

	Node* Insert(Node* root, int data) {
		//if tree is empty, create root node
		if (root == nullptr) {
			root = new Node(data);
			return root;
		}
		// else traverse the tree in level order and find where to insert 
		queue <Node*> q;
		q.push(root);
		while (!q.empty()) {
			Node* current = q.front();
			q.pop();

			// Check for duplicates first
			if (current->data == data) {
				current->count++;
				return root;
			}

			// Then check left if left is null and insert node in left otherwise check for right
			if (current->left != nullptr) {
				q.push(current->left);
			}
			else {
				current->left = new Node(data);
				return root;
			}

			if (current->right != nullptr) {
				q.push(current->right);
			}
			else {
				current->right = new Node(data);
				return root;
			}
		}
		// This line should technically be unreachable
		return root;
	}

	bool Search(Node* root, int data) { // Using recursion to search for an element in the binary tree
		bool temp;
		if (root == nullptr) { // base case 1: If tree is empty or we have reached beyond a leaf node
			return false;
		}
		else {
			if (data == root->data) { // base case 2: we have found element 
				return true;
			}
			else { // recursive case: recurse down subtrees
				temp = Search(root->left, data);
				if (temp) {
					return temp;
				}
				else {
					return Search(root->right, data);
				}
			}
		}
		return false;
	}
	Node* Find(Node* root, int data) { // using level order traversal to find an element in the binary tree 
		Node* temp;
		queue <Node*> q;
		q.push(root);
		while (!q.empty()) {
			temp = q.front();
			if (temp->data == data) {
				return temp;
			}
			q.pop();
			if (temp->left != nullptr) {
				q.push(temp->left);
			}
			if (temp->right != nullptr) {
				q.push(temp->right);
			}
		}
		return nullptr;
	}

	Node* FindDeepestNode(Node* root) {
		// exact same code as level order traversal except the return statement
		Node* temp = nullptr;
		queue <Node*> q;
		if (!root) {
			return temp;
		}
		q.push(root);
		while (!q.empty()) {
			temp = q.front();
			q.pop();
			if (temp->left != nullptr) {
				q.push(temp->left);
			}
			if (temp->right != nullptr) {
				q.push(temp->right);
			}
		}
		return temp; // returns the last node in the queue which is the deepest
	}

	Node* FindParent(Node* root, Node* target) {
		if (root == nullptr || root == target) {
			return nullptr;
		}
		queue<Node*> q;
		q.push(root);
		while (!q.empty()) {
			Node* current = q.front();
			q.pop();
			if (current->left == target || current->right == target) {
				return current;
			}
			if (current->left) {
				q.push(current->left);
			}
			if (current->right) {
				q.push(current->right);
			}
		}
		return nullptr;
	}

	Node* Delete(Node* root, int data) {
		if (root == nullptr) {
			cout << "Tree is empty!" << endl;
			return nullptr;
		}
		Node* keyNode = Find(root, data);
		if (keyNode == nullptr) {
			cout << "Element is not in the tree!" << endl;
			return root;
		}
		// Handle duplicate values: decrement count instead of deleting
		if (keyNode->count > 1) {
			keyNode->count--;
			return root;
		}
		Node* dNode = FindDeepestNode(root);
		Node* parentOfDeepest = FindParent(root, dNode);
		// Case: The tree has only one node (keyNode is dNode)
		if (dNode == root) {
			delete root;
			return nullptr;
		}

		// Step 1: Replace the data of the keyNode with the data of the deepest node
		keyNode->data = dNode->data;
		// Step 2: Handle duplicate counts of the deepest node (dNode)
		// This is necessary because dNode's data is moved to keyNode.
		// We'll give dNode's count to keyNode before we delete dNode.
		keyNode->count = dNode->count;

		// Step 3: Safely unlink and delete the deepest node from its parent

		if (parentOfDeepest->right == dNode) {
			parentOfDeepest->right = nullptr;
		}
		else {
			parentOfDeepest->left = nullptr;
		}

		delete dNode;
		return root;
	}


	void inorder(Node* curr) {
		if (curr == nullptr)
			return;
		inorder(curr->left);
		cout << curr->data << ' ';
		inorder(curr->right);
	}
	void PreOrder(Node* root) {
		if (root == nullptr) {
			return;
		}
		cout << root->data << " ";
		PreOrder(root->left);
		PreOrder(root->right);

	}
	void PostOrder(Node* root) {
		if (root == nullptr) {
			return;
		}
		PostOrder(root->left);
		PostOrder(root->right);
		cout << root->data << " ";
	}
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

	// Constructing the binary tree
	//          10
	//        /    \ 
    //       11     9
	//      /      / \
    //     7      15   8
	BinaryTree bt;

	bt.root = new Node(10);
	bt.root->left = new Node(11);
	bt.root->right = new Node(9);
	bt.root->left->left = new Node(7);
	bt.root->right->left = new Node(15);
	bt.root->right->right = new Node(8);
	bt.inorder(bt.root);
	// After insertion 12 in binary tree
	//          10
	//        /    \ 
    //       11     9
	//      /  \   / \
    //     7   12 15  8
	cout << "\n After inserting 12: " << endl;
	bt.root = bt.Insert(bt.root, 12);
	bt.inorder(bt.root);
	cout << endl << "Searching 8: " << bt.Search(bt.root, 8) << endl;
	cout << "Finding 12: " << bt.Find(bt.root, 12) << endl;
	cout << "Finding 5: " << bt.Find(bt.root, 5) << endl;
	cout << "Searching 5: " << bt.Search(bt.root, 5) << endl;
	bt.root = bt.Delete(bt.root, 11);
	cout << "After deleting 11: Inorder - " << endl;
	bt.inorder(bt.root);
	cout << "\nPreOrder: " << endl;
	bt.PreOrder(bt.root);
	cout << "\nPostOrder: " << endl;
	bt.PostOrder(bt.root);
	bt.DeleteTree(bt.root);

	return 0;
}