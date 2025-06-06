#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <cmath>
#include <cstdlib>
using namespace std;

void getOrder(int&);
void getNumber(int*);
void getSales(double*, int);
double totalSales(double*, int);
int* getRandomNumbers(int);

int main() {

	int amount;
	cout << &amount << endl;

	int JellyDonuts;
	getOrder(JellyDonuts);
	cout << JellyDonuts << endl;

	int x = 25;
	int* ptr;
	ptr = &x;
	cout << "The value of x is " << *ptr << endl;
	cout << "The memory address of x is " << ptr << endl;
	*ptr = 100; // changes the value of x since *ptr = x and ptr is pointing to x
	cout << x << endl;
	cout << *ptr << endl;
	cout << ptr << endl; // memory address remains mostly unchanges since ptr = &x

	const int size = 5;
	short numbers[size] = { 10,20,30,40,50 };
	cout << *numbers << endl;

	//Using pointers instead of subscripts
	for (int i = 0; i < size; i++) {
		cout << *(numbers + i) << " ";
	}
	cout << endl;
	//Subscript notation with Pointer
	short* shortptr = numbers;
	for (int i = 0; i < size; i++) {
		cout << shortptr[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < size; i++) {
		cout << *(numbers + i) << " ";
	}
	cout << endl;
	//using address operator for each individual element
	short* ptr1;
	for (int i = 0; i < size; i++) {
		ptr1 = &numbers[i];
		cout << *ptr1 << " ";
	}
	cout << endl;

	//using a while loop to print array forwards and backwards
	int set[8] = { 5,10,15,20,25,30,35,40 };
	int* nums = set;
	cout << "The numbers in the set are: ";
	while (nums <= &set[7]) {
		cout << *nums << " ";
		nums++;
	}
	cout << endl << "The numbers backwards are: ";
	nums--; // because pointer now points to extra memory location after the end of the array
	while (nums >= set) {
		cout << *nums << " ";
		nums--;
	}
	cout << endl;

	int number;
	getNumber(&number);
	cout << number << endl;

	const int QTRS = 4;
	double sales[QTRS];
	getSales(sales, QTRS);
	cout << "The total sales for year are $" << totalSales(sales, QTRS) << endl;

	//Constant Pointers
	int value = 22;
	int* const ptr2 = &value;
	int value2 = 23;
	const int* const ptr3 = &value2;

	//Pointer to a pointer
	int x1 = 5;
	int* p = &x1; //p points to x
	int** q = &p;// q points to p which points to x
	int*** r = &q; // r points to q which points to p which points to x
	cout << "Value of x1: " << x1 << endl;
	cout << "Memory address of p/&x1: " << p << endl;
	cout << "Value of x1: " << *p << endl;
	cout << "Memory address of p: " << *q << endl;
	cout << "Value of x1/*p: " << *(*q) << endl;
	cout << "Value of x1/*p:" << **q << endl;
	cout << "Memory address of q/value of q:" << *r << endl;
	cout << "Memmory address/value of p/" << *(*r) << endl;
	cout << "Value of x1/***r: " << ***r << endl;
	
	//Dynamic Memory Allocation
	int* iptr;
	iptr = new int; // allocates memory for a new int. iptr will contain the address of this new variable
	*iptr = 25;
	cout << *iptr << endl;
	delete iptr; // releasing or freeing memory

	iptr = new int[100]; // 100 element array space being allocated. iptr[i] can then be used to access.
	delete[] iptr; // releasing or deleting or freeing memory

	double* sales1, total = 0, average;
	int numDays, count;
	cout << "How many days of sales figures do you wish to process?";
	cin >> numDays;
	sales1 = new double[numDays]; //dynamically allocates memory for an array of doubles
	cout << "Enter sales figure below" << endl;
	for (count = 0; count < numDays; count++) {
		cout << "Day " << count + 1 << ":";
		cin >> sales1[count];
		total += sales[count];
	}
	average = total / numDays;
	cout << "Average sales: $" << average << endl;
	delete[] sales1;
	sales1 = 0; // good practice to store 0 in a pointer variable after using delete on it

	//Dynamically allocating a 2D array:
	int rows, columns;
	cout << "Enter rows: " << endl;
	cin >> rows;
	cout << "Enter columns: " << endl;
	cin >> columns;
	int** array;
	array = new int* [rows];
	for (int i = 0; i < rows; i++) {
		array[i] = new int[columns];

	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < rows; j++) {
			cout << "Enter element [" << i << "][" << j << "]";
			cin >> array[i][j];
		}
	}
	for (int i = 0; i < rows; i++) {
		delete[]array[i];
	}
	delete[]array;

	// Returning pointers from functions
	int* numbers1;
	numbers1 = getRandomNumbers(5);
	for (int i = 0; i < 5; i++) {
		cout << numbers1[i] << " ";
	}
	cout << endl;
	delete[] numbers1;
	numbers1 = 0;

	return 0;
}

void getOrder(int& donuts) {
	cout << "How many donuts? ";
	cin >> donuts;
}

void getNumber(int* input) {
	cout << "Enter Number ";
	cin >> *input;
}

void getSales(double* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << "Enter sales figure for quarter " << i + 1 << ": ";
		cin >> arr[i];
	}
}
double totalSales(double* arr, int size) {
	double sum = 0;
	for (int i = 0; i < size; i++) {
		sum += *arr;
		arr++;
	}
	return sum;
}

int* getRandomNumbers(int num) {
	int* arr;
	arr = new int[num];
	for (int i = 0; i < num; i++) {
		arr[i] = rand();
	}
	return arr;
}