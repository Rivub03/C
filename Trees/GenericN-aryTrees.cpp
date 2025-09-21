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
	Node* firstChild;
	Node* secondChild;
	Node* thirdChild;
	Node* fourthChild;
	Node* fifthChild;
	Node* sixthChild;
};

struct GenericTree{
	Node* root;
	GenericTree() {
		root = nullptr; 
	}
};