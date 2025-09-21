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
	Node* left;
	Node* right;
	int height;
	Node() : data(0), left(nullptr), right(nullptr) {};
	Node(int data) {
		this->data = data;
		this->left = this->right = nullptr;
		this->height = 1; // New nodes are leaves, so their initial height is 1
	}
};

struct AVLTree {
	Node* root;
	AVLTree() {
		root = nullptr;
	}
	// Helper function for a user-facing Insert
	void Insert(int data) {
		root = Insert(root, data);
	}
	int FindHeight(Node* N) {
		if (N == nullptr) {
			return 0;
		}
		return N->height;
	}

	Node* LLRightRotate(Node* node) {
		Node* leftc = node->left;
		Node* leftrightc = leftc->right;
		//perform rotation
		leftc->right = node; // since leftc becomes root, it's right child will be previous root node
		node->left = leftrightc; // the right child of the previous left child will become the left child of the previous root node
		// update heights: leftrightchild's height will remain the same. 
		node->height = 1 + max(FindHeight(node->left), FindHeight(node->right)); // height is maximum of left/right subtree + 1
		leftc->height = 1 + max(FindHeight(leftc->left), FindHeight(leftc->right));

		return leftc; // new root 

	}
	Node* RRLeftRotate(Node* node) {
		Node* rightc = node->right;
		Node* rightleftc = rightc->left;
		// perform rotation
		rightc->left = node; // since right child of node becomes root, it's left child will be the previous root 
		node->right = rightleftc; // the left child of the previous right child will become the right right child of the previous root node
		// update heights
		node->height = 1 + max(FindHeight(node->left), FindHeight(node->right));
		rightc->height = 1 + max(FindHeight(rightc->left), FindHeight(rightc->right));

		return rightc; // new root
	}

	int GetBalance(Node* node) {
		if (node == nullptr) {
			return 0;
		}
		return FindHeight(node->left) - FindHeight(node->right);
	}

	Node* Insert(Node* root, int data) {
		// the normal bst insert function 
		if (root == nullptr) {
			return new Node(data);
		}
		if (data < root->data) {
			root->left = Insert(root->left, data);
		}
		else if (data > root->data) {
			root->right = Insert(root->right, data);
		}
		else {
			return root;
		}
		// update height of this ancestor node 
		root->height = 1 + max(FindHeight(root->left), FindHeight(root->right));
		// get the balance factor of the ancestor node 
		int balance = GetBalance(root);
		// if this node becomes unbalanced, then we have the four cases of rotation:

		// if this node becomes unbalanced, then we have the four cases of rotation:
		if (balance > 1 && data < root->left->data) { // Left Left imbalance case
			return LLRightRotate(root);
		}

		if (balance < -1 && data > root->right->data) { // Right Right imbalance case
			return RRLeftRotate(root);
		}

		if (balance > 1 && data > root->left->data) { // Left Right case of double rotation
			root->left = RRLeftRotate(root->left);
			return LLRightRotate(root);
		}

		if (balance < -1 && data < root->right->data) { // Right Left case of double rotation
			root->right = LLRightRotate(root->right);
			return RRLeftRotate(root);
		}

		// return the unchanged root pointer
		return root;
	}

	Node* Delete(Node* root, int data) {
		if (root == nullptr) return root;

		if (data < root->data) { // move left
			root->left = Delete(root->left, data);
		}
		else if (data > root->data) { // move right
			root->right = Delete(root->right, data);
		}
		else { // coming to this line will mean element is found
			// assuming element is found:
			if (root->left == nullptr && root->right == nullptr) { // case 1: leaf node
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
				Node* temp = FindMin(root->right); // find the in-order successor or the smallest in the right subtree
				root->data = temp->data;
				root->right = Delete(root->right, temp->data); // reduces to case 1 where we are deleting leaf
			}
		}

		// If the tree had only one node, then return
		if (root == nullptr) {
			return root;
		}

		// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
		root->height = 1 + max(FindHeight(root->left), FindHeight(root->right));

		// STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether this node became unbalanced)
		int balance = GetBalance(root);

		// Check for the 4 cases of rotation after deletion
		// The logic here should use the balance factor, not the data value
		// after a node has been deleted, you no longer have access to the deleted data value to perform check like in insert function
		if (balance > 1 && GetBalance(root->left) >= 0) { // Left Left imbalance case
			return LLRightRotate(root);
		}
		if (balance > 1 && GetBalance(root->left) < 0) { // Left Right case of double rotation
			root->left = RRLeftRotate(root->left);
			return LLRightRotate(root);
		}
		if (balance < -1 && GetBalance(root->right) <= 0) { // Right Right imbalance case
			return RRLeftRotate(root);
		}
		if (balance < -1 && GetBalance(root->right) > 0) { // Right Left case of double rotation
			root->right = LLRightRotate(root->right);
			return RRLeftRotate(root);
		}

		return root;
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

	void LevelOrder(Node* root) {
		if (root == nullptr) {
			return;
		}
		queue <Node*> Q;
		Q.push(root);
		while (!Q.empty()) {
			Node* current = Q.front();
			Q.pop();
			cout << current->data << " ";
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
		cout << root->data << " ";
		PreOrder(root->left);
		PreOrder(root->right);
	}
	void InOrder(Node* root) {
		if (root == nullptr) {
			return;
		}
		InOrder(root->left);
		cout << root->data << " ";
		InOrder(root->right);
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

	AVLTree avl;
	avl.root = new Node(15); avl.PreOrder(avl.root);

	cout << "--- Testing Insertions and Rotations ---" << endl;

	// Test Case 1: Simple insertions (no rotations)
	cout << "Inserting 10, 20, 30..." << endl;
	avl.Insert(10);
	avl.Insert(20);
	avl.Insert(30);
	cout << "Inorder Traversal: ";
	avl.InOrder(avl.root); // Should be 10 15 20 30
	cout << endl;
	cout << "Level Order Traversal: ";
	avl.LevelOrder(avl.root); // Should be 20 10 30 (after RR rotation)

	// Test Case 2: Left Left Rotation
	cout << "\nInserting 5, 2..." << endl;
	avl.Insert(5);
	avl.Insert(2);
	cout << "Inorder Traversal: ";
	avl.InOrder(avl.root); // Should be 2 5 10 20 30
	cout << endl;
	cout << "Level Order Traversal: ";
	avl.LevelOrder(avl.root); // Should be 20 5 30 2 10

	// Test Case 3: Left Right Rotation
	cout << "\nInserting 15..." << endl;
	avl.Insert(15);
	cout << "Inorder Traversal: ";
	avl.InOrder(avl.root);
	cout << endl;
	cout << "Level Order Traversal: ";
	avl.LevelOrder(avl.root); // Tree should be balanced

	cout << "-----------------------------------" << endl;
	cout << "--- Testing Deletions and Rebalancing ---" << endl;

	// Test Case 4: Delete a leaf node (no rebalancing needed)
	cout << "\nDeleting 2..." << endl;
	avl.root = avl.Delete(avl.root, 2);
	cout << "Inorder Traversal: ";
	avl.InOrder(avl.root);
	cout << endl;
	cout << "Level Order Traversal: ";
	avl.LevelOrder(avl.root);

	// Test Case 5: Delete a node with one child
	cout << "\nDeleting 5..." << endl;
	avl.root = avl.Delete(avl.root, 5);
	cout << "Inorder Traversal: ";
	avl.InOrder(avl.root);
	cout << endl;
	cout << "Level Order Traversal: ";
	avl.LevelOrder(avl.root);

	// Test Case 6: Delete a node with two children (e.g., 20)
	cout << "\nDeleting 20..." << endl;
	avl.root = avl.Delete(avl.root, 20);
	cout << "Inorder Traversal: ";
	avl.InOrder(avl.root);
	cout << endl;
	cout << "Level Order Traversal: ";
	avl.LevelOrder(avl.root);

	// Test Case 7: Complex Deletion that requires rebalancing
	cout << "\nInserting 40, 50, 60..." << endl;
	avl.Insert(40);
	avl.Insert(50);
	avl.Insert(60);
	cout << "Inorder Traversal: ";
	avl.InOrder(avl.root);
	cout << endl;
	cout << "Level Order Traversal: ";
	avl.LevelOrder(avl.root);
	cout << "Deleting 10 to cause a balance issue..." << endl;
	avl.root = avl.Delete(avl.root, 10);
	cout << "Inorder Traversal: ";
	avl.InOrder(avl.root);
	cout << endl;
	cout << "Level Order Traversal: ";
	avl.LevelOrder(avl.root);

	// Clean up memory
	avl.DeleteTree(avl.root);


	return 0;
}