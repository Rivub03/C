#include <string>
#include <vector>
#include <ostream>
#include <iostream>
#include <strstream>
#include <sstream>
#include <cstdlib>
#include <array>
using namespace std;

int** twoDimensionalArray(int &, int &); // creates a 2D array and populates it with input. Returns the 2D array which is a pointer to a pointer.
bool ArraysEqual(int[], int[], int, int); // checks if two 1D arrays are equal or not
void freeTwoDimensionalArray(int**, int); // Frees/deletes the memory holding the 2D array
int** MatrixMultiplication(int **, int** , int, int); // multiplying matricses of the same size, returns the new matrice as a pointer to a pointer variable
int main() {
	int n1, n2, *arr1, *arr2;
	cout << "Enter array size 1: ";
	cin >> n1;
	cout << "Enter array size 2: ";
	cin >> n2;

	arr1 = new int[n1];
	arr2 = new int[n2];
	for (int i = 0; i < n1; i++) {
		cout << "Enter element " << (i+1) << " of array1: ";
		cin >> arr1[i];
	}
	for (int i = 0; i < n2; i++) {
		cout << "Enter element " << (i + 1) << " of array2: ";
		cin >> *(arr2+i);
	}
	cout << "Array 1: ";
	for (int i = 0; i < n1; i++) {
		cout << arr1[i] << ",";
	}
	cout << endl << "Array 2: ";
	for (int i = 0; i < n2; i++) {
		cout << arr2[i] << ",";
	}
	cout << endl;

	if (ArraysEqual(arr1, arr2, n1, n2)) {
		cout << "The arrays are the same!"<< endl;
	}

	else {
		cout << "The arrays are different" << endl;
	}

	int rows, columns;
	int **twoDarray = twoDimensionalArray(rows ,columns); 
	cout << endl <<"The array from the main function: ";
	for (int i = 0; i < rows; i++) {
		cout << "[";
		for (int j = 0; j < columns; j++) {
			cout << twoDarray[i][j] << ",";
		}
		cout << "]"<<endl;
	}

	int** twoDarray1 = twoDimensionalArray(rows, columns);
	int** resultantArray = MatrixMultiplication(twoDarray, twoDarray1, rows, columns);
	cout << "The resultant array is:" << endl;
	for (int i = 0; i < rows; i++) {
		cout << "[";
		for (int j = 0; j < columns; j++) {
			cout << resultantArray[i][j];
			cout << ",";
		}
		cout << "]" << endl;
	}

	freeTwoDimensionalArray(twoDarray, rows);
	freeTwoDimensionalArray(twoDarray1, rows);
	freeTwoDimensionalArray(resultantArray, rows);

	delete[]arr1;
	delete[]arr2;

	return 0;
}

bool ArraysEqual(int nums1[], int nums2[], int size1, int size2) {
	bool arraysEqual = true;

	if (size1 != size2) {
		arraysEqual = false;
	}
	else if (size1 == size2){
		int i = 0;
		while (arraysEqual && i < size1) {
			if (nums1[i] != nums2[i]) {
				arraysEqual = false;
				break;
			}
			i++;
		}
	}

	return arraysEqual;
}

int **twoDimensionalArray(int &rows, int &columns) { 
	int **array;
	cout << "Enter number of rows: ";
	cin >> rows;
	cout << "Enter number of columns: ";
	cin >> columns;

	array = new int* [rows];
	for (int i = 0; i < rows; i++) {
		array[i] = new int[columns];
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << "Enter element [" << (i + 1) << "][" << (j + 1)<< "]: ";
			cin >> array[i][j];
		}
	}
	cout << "The inputted 2D array is: " << endl;
	for (int i = 0; i < rows; i++) {
		cout << "[";
		for (int j = 0; j < columns; j++) {
			cout << array[i][j] << ",";
		}
		cout << "]"<<endl;
	}
	return array;

}

void freeTwoDimensionalArray(int** array, int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] array[i];
	}
	delete[] array;
}

int** MatrixMultiplication(int** arr1, int** arr2, int row, int col) {
	int** newArray; //first, let's allocate enough space for the resultant dynamic array
	newArray = new int* [row];
	for (int i = 0; i < row; i++) {
		newArray[i] = new int[col];
	}

	for (int i = 0; i < row; i++) { //now, time to store the resultant array
		for (int j = 0; j < col; j++) {
			newArray[i][j] = 0;
			for (int k = 0; k < row; k++) {
				newArray[i][j] += arr1[i][k] * arr2[k][j];
			}
		}
	}
	return newArray;
}
