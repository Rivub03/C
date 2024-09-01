#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

#define maxSize 1000;
int top = -1;

using namespace std; 

struct DStack {
	int* array;

	void CreateStack() {
		int size; 
		cout << "Enter size of stack (maximum size is 1000): ";
		cin >> size; 
		if (size > 1000) {
			cout << "Size exceeds max size";
			return;
		}
		array = new int[size];
	}
	void Push(int x) {
		if (top > 1000) {
			cout << "Error: Stack OverFlow";
			return;
		}
		array[++top] = x;
	}

	void Pop() {
		if (top == -1) {
			cout << "error, no elemt to pop";
			return;
		}
		else {
			top--;
		}
	}

	int Top() {
		return array[top];
	}

	bool IsEmpty() {
		if (top == -1) {
			return true;
		}
		else {
			return false;
		}
	}

	void Print() {
		cout << "The stack is: [";
		for (int i = 0; i <= top; i++) {
			cout << array[i] << ",";
		}
		cout << "]" << endl;
	}

};



int main() {

	DStack stack;
	stack.CreateStack();
	stack.Push(1);
	stack.Push(2);
	stack.Print();
	stack.Pop();
	stack.Print();
	cout << stack.Top();

}

