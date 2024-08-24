#include <string>
#include <vector>
#include <ostream>
#include <iostream>
#include <strstream>
#include <sstream>
#include <cstdlib>
#include <array>
using namespace std;

void message(int); // simple recursive function that has a base case and shows how a callstack works
int factorial(int); // simple recursive function that demonstrates base case and recursive case 
int fibonacci(int); // another simple recursive function that demonstrates base case and recusrive case 
int power(int, int); // recursive function to raise an integer to its exponent x^y
int gcd(int,int); // dry run this code to see how it works
int reverseNumber(int, int); //  reverses a given integer recursively
bool isPalindrome(int);// checks if an integer is a palindrome or not non-recursively
int isArrayInSortedOrder(int[], int n); // checks if a given 1D array is sorted recursively

int main() {

	message(5); // code for message
	// code for factorial
	cout << "factorial: " << factorial(100) << endl;
	int x;

	//code for displaying the fibonacci sequence instead of just one number
	cout << "enter the fibonacci numbers you want displayed: " << endl;
	cin >> x;
	cout << "the first " << x <<" fibonacci numbers are : " << endl;
	for (int i = 0; i < x; i++) {
		cout << fibonacci(i) << ","; 
	}
	cout << endl;

	// code for Power
	cout << "The power is: " << power(5, 4);

	// code for HCF
	cout << endl;
	cout << "The HCF is: " << gcd(20, 30) << endl;

	//Code for Palindrome
	cout << "Enter integer to check for palindrome: " << endl;
	int b;
	cin >> b;
	if (isPalindrome(b)) {
		cout << "Number is a palindrome " << endl;
	}
	else if (!isPalindrome(b)) {
		cout << "Number is not a palindrome " << endl;
	}
	else {
		cout << "I don't know what happened xD";
	}

	//code for sorted array
	cout << "Enter the size of the array: " << endl;
	int n, *array;
	cin >> n;
	array = new int[n];
	cout << "Enter array: " << endl;
	for (int i = 0; i < n; i++) {
		cout << "Enter array[" << i + 1 << "]: ";
		cin >> array[i];
	}
	int a = isArrayInSortedOrder(array, n);
	if (a == 0) {
		cout << "False: Array is not soreted";
	}
	else if (a == 1) {
		cout << "True: Array is sorted";
	}
	cout << endl;

	return 0;
}

void message(int times) { // recursive will print 5 times, endline will print 6 times
	if (times > 0) { // because the function is called 6 times, and at message(0), it never enters this block
		cout << "Recursive function:" << times << endl;
		message(times - 1);
	}
	cout << "endline: " << times << endl; // at message(0) this line is reached for the first time. Each other call reaches this line one by one
}	

int factorial(int n) { // complexity O(n)
	if (n == 0) {
		return 1; // base case 
	}
	else {
		return n * factorial(n - 1); // recursive case that returns recursively the result 
	}

}

int fibonacci(int n) { // complexity O(2^n)
	if (n <= 1) {
		return n;
	}
	else {
		return fibonacci(n - 1) + fibonacci(n - 2);
	}
}

int power(int x, int y) { // complexit O(n)
	if (y == 0) {
		return 1;
	}
	else if (y == 1) {
		return x;
	}
	else {
		return x * power(x, y - 1);
	}


}
int gcd(int x, int y) { // complexity O(log n)
	if (x % y == 0) {
		return y;
	}
	else {
		return gcd(y, x % y);
	}
}

int reverseNumber(int num, int temp) { // time complexity O(d) where d is number of digits 
	if (num == 0) {
		return temp;
	}
	else {
		temp = (temp * 10) + (num % 10);
		return reverseNumber(num / 10, temp);
	}
}

bool isPalindrome(int n) {
	int temp;
	temp = reverseNumber(n, 0);
	if (temp == n) {
		return true;
	}
	else if (temp != n) {
		return false;
	}
}

int isArrayInSortedOrder(int A[], int size) { // complexity O(n)
	if (size == 1) {
		return 1;
	}
	else {
		if (A[size - 1] < A[size - 2]) {
			return 0;
		}
		else {
			return isArrayInSortedOrder(A, size - 1);
		}
	}
}
