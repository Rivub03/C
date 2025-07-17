#include <iostream>
#include <deque>

using namespace std;

void printStack(deque<int>);
int main() {
    deque<int> stack;

    stack.push_back(10);
    stack.push_back(20);
    stack.push_back(30);
    printStack(stack);
    cout << "Top element is: " << stack.back() << endl;
    cout << stack.back() << " popped from deque" << endl;
    stack.pop_back();
    printStack(stack);

    //we can also pop from front:
    cout << "Top element is: " << stack.front() << endl;
    cout << stack.front() << " popped from deque" << endl;
    stack.pop_front();
    printStack(stack);

    
    return 0;
}

void printStack(deque<int> stack) {
    cout << "Stack: [";
    for (int i = 0; i < stack.size(); i++) {
        cout << stack[i] << ",";
    }
    cout << "]" << endl;
}
