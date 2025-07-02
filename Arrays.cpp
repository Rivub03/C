#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <random>
#include <algorithm>
using namespace std;

// Helper Functions
void print1DArray(int[], int);
void print2DArray(int**, int, int);
int* makeNew1DArray(int);
int** makeNew2DArray(int, int);
int* randomArray(int); //fill an array of n integers with random numbers then find highest, smallest & average value

int LinearSearch1D(int[], int, int); //sequential search that returns position of element if found, -1 otherwise
int LinearSearch2D(int**, int, int, int); // sequential search for 2D arrays
int BinarySearch1D(int[], int, int); // Binary search that returns position of element if found, -1 otherwise

void bubbleSort1D(int[], int); // sorts a 1D array using bubble sort technique
void selectionSort1D(int[], int); // sorts a 1D array using insertion sort technique

bool isPrime_HighlyOptimized(int x) { // Skip even numbers and use 6k±1 pattern
	if (x <= 1) return false;
	if (x <= 3) return true;
	if (x % 2 == 0 || x % 3 == 0) return false;

	int counter = 0;

	// Check only numbers of form 6k±1 up to ?x
	for (int i = 5; i * i <= x; i += 6) {
		if (x % i == 0 || x % (i + 2) == 0) {
			//cout << "Loop executed: " << counter << " times" << endl;
			return false;
		}
		counter++;
	}

	//cout << "Loop executed: " << counter << " times" << endl;
	return true;
}


//Practice Problem Questions: 1D array
void printForwardBackward(int[], int); // make a new array and print it forwards and backwars
int* make25Array(int, int); // take two integers from user and fill an array of size 25 with random values between the two numbers
void question4(); // make new array with input size, fill it with random numbers, search for a number and how many times it is found or not
void floatingPointArraysSort(); // Creating two floating point arrays, fill them with random numbers, print and sort in ascending and descending order
bool sortedOrUnsorted(int*, int); // Check if an array is sorted or not; if sorted, print if it is in ascending/descending
void findmaxminmedian(int[], int); // Find 1st, 2nd maximum, 1st 2nd minimum and median value of an array
void evenOddArray(int[], int); //Given an array, separate even and odd values and store in separate arrays and print 3 arrays
void fibonacciArray(int); // Fill an array of certain size with fibonacci series and print it 
int howManyPrimes(int[], int); // Find how many prime numbers are in an array
void decimaltoBinary(int); // Given a number, convert the decimal number to binary
void numberOfOccurences(int[], int); // Print number of times each number occurs in an array

// Practice Problem Questions: 2D array
int** matrixSubtraction(int**, int, int, int**, int, int);
int** matrixTranspose(int**, int, int);
int** matrixMultiplication(int**, int, int, int**, int, int);
int numberOfPrimes(int**, int, int);
int* twoDimensionaltoOneDimensional(int**, int, int);
int** oneDimensionaltoTwoDimensional(int*, int, int);
void sumOfDiagonals(int**, int, int);



int main() {


	int* arr1 = makeNew1DArray(10);
	int** arr2 = makeNew2DArray(3, 3);
	int* arr3 = randomArray(100);
	print1DArray(arr3, 100);
	print2DArray(arr2, 3, 3);
	cout << "Element [2][2] is: " << arr2[2][2] << endl;

	cout << LinearSearch1D(arr1, 10, 9) << endl;
	cout << LinearSearch2D(arr2, 3, 3, 9) << endl;
	cout << LinearSearch1D(arr1, 10, 20) << endl;
	cout << LinearSearch2D(arr2, 3, 3, 11) << endl;
	cout << BinarySearch1D(arr1, 10, 9) << endl;
	cout << BinarySearch1D(arr1, 10, 11) << endl;

	bubbleSort1D(arr1, 10);
	cout << "The sorted array using bubble sort is: ";
	print1DArray(arr1, 10);
	bubbleSort1D(arr3, 100);
	cout << "The sorted array using bubble sort is: ";
	print1DArray(arr3, 100);
	cout << endl;

	int array4[6] = { 2,8,1,7,10,4 };
	print1DArray(array4, 6);
	selectionSort1D(array4, 6);
	cout << "The printed array using Selection Sort: ";
	print1DArray(array4, 6);


	int* array1 = randomArray(25);
	printForwardBackward(array1, 10);
	int* array2 = make25Array(10, 150);
	question4();
	floatingPointArraysSort();
	sortedOrUnsorted(array1, 10);
	sortedOrUnsorted(array2, 25);
	bubbleSort1D(array2, 25);
	print1DArray(array2, 25);
	sortedOrUnsorted(array2, 25);
	findmaxminmedian(array1, 25);
	evenOddArray(array1, 25);
	fibonacciArray(15);
	cout << "The number of primes in array 1 are: " << howManyPrimes(array1, 25);
	numberOfOccurences(array1, 25);
	int** arrayA = makeNew2DArray(3, 3);
	int** arrayB = makeNew2DArray(3, 3);
	int** array3 = matrixSubtraction(arrayA, 3, 3, arrayB, 3, 3);
	int** arrayC = matrixMultiplication(arrayA, 3, 3, arrayB, 3, 3);
	int** arrayC_T = matrixTranspose(arrayC, 3, 3);
	cout << "Array3 = ArrayA - ArrayB: " << endl;
	print2DArray(array3, 3, 3);
	cout << "ArrayC = ArrayA * ArrayB: " << endl;
	print2DArray(arrayC, 3, 3);
	cout << "Transpose of ArrayC: " << endl;
	print2DArray(arrayC_T, 3, 3);
	cout << "The number of Prime numbers in arrayC are = " << numberOfPrimes(arrayC, 3, 3);
	int* arrayCFlattened = twoDimensionaltoOneDimensional(arrayC, 3, 3);
	cout << "ArrayC Flattened: " << endl;
	print1DArray(arrayCFlattened, 9);
	int** arrayCFlattenededUnflattened = oneDimensionaltoTwoDimensional(arrayCFlattened, 3, 3);
	cout << "Unflattening ArrayC again into a 3x3 matrix: " << endl;
	print2DArray(arrayCFlattenededUnflattened, 3, 3);
	sumOfDiagonals(arrayA, 3, 3);
	sumOfDiagonals(arrayB, 3, 3);
	sumOfDiagonals(arrayC, 3, 3);

	return 0;
}
void print1DArray(int arr[], int size) {
	cout << "Array: [";
	for (int i = 0; i < size; i++) {
		cout << arr[i] << ",";
	}
	cout << "]" << endl;
}
void print2DArray(int** array, int row, int col) {
	cout << "Array:" << endl;
	for (int i = 0; i < row; i++) {
		cout << "[";
		for (int j = 0; j < col; j++) {
			cout << array[i][j] << ",";
		}
		cout << "]" << endl;
	}
}
int* makeNew1DArray(int size) {
	int* array = new int[size];
	for (int i = 0; i < size; i++) {
		cout << "Enter element " << i << " :";
		cin >> array[i];
	}
	return array;
}
int** makeNew2DArray(int row, int col) {
	int** array = new int* [row];
	for (int i = 0; i < row; i++) {
		array[i] = new int[col];
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << "Enter element [" << i << "][" << j << "]:";
			cin >> array[i][j];
		}
	}
	return array;
}
int* randomArray(int size) {
	int* array = new int[size];
	for (int i = 0; i < size; i++) {
		array[i] = rand() % 100; // fills array with random numbers up to 100
	}
	cout << "Array: [";
	for (int i = 0; i < size; i++) {
		cout << array[i] << ",";
	}
	cout << "]" << endl;

	int largest = array[0], smallest = array[0], total = 0;
	double average;
	for (int i = 0; i < size; i++) {
		if (array[i] > largest) {
			largest = array[i];
		}
		if (array[i] < smallest) {
			smallest = array[i];
		}
		total += array[i];
	}
	average = total / size;

	cout << "Largest = " << largest << " Smallest = " << smallest << " Average = " << average << endl;
	return array;
}

int LinearSearch1D(int arr[], int size, int value) {
	int index = 0;
	int position = -1;;
	bool found = false;
	while (index < size && !found) {
		if (arr[index] == value) {
			found = true;
			position = index;
		}
		index++;
	}
	if (found) {
		cout << "Element is found" << endl;
	}
	else {
		cout << "Element is not found" << endl;
	}

	return position;
}
int LinearSearch2D(int** arr, int row, int col, int value) {
	int position = -1;
	bool found = false;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (arr[i][j] == value) {
				position = (i * 10) + j;
				found = true;
				break;
			}
		}
	}
	if (found) {
		cout << "Element is found" << endl;
	}
	else {
		cout << "Element is not found" << endl;
	}

	return position;
}
int BinarySearch1D(int arr[], int row, int value) {
	int first = 0;
	int last = row - 1;
	int middle;
	int position = -1;
	bool found = false;
	while (!found && first <= last) {
		middle = (first + last) / 2;
		if (arr[middle] == value) {
			found = true;
			position = middle;
		}
		else if (arr[middle] > value) {
			last = middle - 1;
		}
		else {
			first = middle + 1;
		}
	}

	if (found) {
		cout << "Element is found" << endl;
	}
	else {
		cout << "Element is not found" << endl;
	}
	return position;
}

void bubbleSort1D(int array[], int size) {
	bool swap;
	int temp;
	do {
		swap = false;
		for (int i = 0; i < size - 1; i++) {
			if (array[i] > array[i + 1]) {
				temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
				swap = true;
			}
		}
	} while (swap);
}
void selectionSort1D(int array[], int size) {
	int startScan, minIndex, minValue;
	for (startScan = 0; startScan < (size - 1); startScan++) {
		minIndex = startScan;
		minValue = array[startScan];
		for (int i = startScan + 1; i < size; i++) {
			if (array[i] < minValue) {
				minValue = array[i];
				minIndex = i;
			}
		}
		array[minIndex] = array[startScan];
		array[startScan] = minValue;
	}
}


void printForwardBackward(int array[], int size) {
	cout << "Array forward: [";
	for (int i = 0; i < size; i++) {
		cout << array[i] << ",";
	}
	cout << "]" << endl;
	cout << "Array backwards: [";
	for (int i = size - 1; i >= 0; i--) {
		cout << array[i] << ",";
	}
	cout << "]" << endl;
}
int* make25Array(int a, int b) {
	int array[25];
	// Seed the Random Number Engine: Seed a random number engine to ensure different sequences of 
	// numbers are generated each time the program runs. A common method is to use the current time.
	// std::mt19937 is a Mersenne Twister pseudo-random number generator, a good general-purpose choice.
	std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> distribution(a + 1, b - 1); // defines the distribution between a & b
	for (int i = 0; i < 25; i++) {
		array[i] = distribution(generator);; // fills array with random numbers between a & b
	}
	cout << "Random Array between values " << a << " and " << b << " : [";
	for (int i = 0; i < 25; i++) {
		cout << array[i] << ",";
	}
	cout << "]" << endl;

	return array;
}
void question4() {
	cout << "Enter size of the array";
	int n, x;
	cin >> n;
	int* array = new int[n];
	cout << "Enter number for array to be bounded by: ";
	cin >> x;
	for (int i = 0; i < n; i++) {
		*(array + i) = rand() % x;
	}
	cout << "Question 4 Array - ";
	print1DArray(array, n);
	cout << "Enter number for search:" << endl;
	int value;
	cin >> value;
	int position = LinearSearch1D(array, n, value);
	if (position == -1) {
		cout << "Element not found!" << endl;
	}
	else {
		cout << "Element is found! Index = " << position << endl;
		int frequency = 0;
		for (int i = 0; i < n; i++) {
			if (array[i] == value) {
				frequency++;
			}
		}
		cout << "Number of times element appears in array: " << frequency << endl;
	}

}
void floatingPointArraysSort() {
	float array1[20];
	for (int i = 0; i < 20; i++) {
		array1[i] = rand() % 100;
	}
	cout << "Array 1: [";
	for (int i = 0; i < 20; i++) {
		cout << array1[i] << ",";
	}
	cout << "]" << endl;

	float array2[30];
	for (int i = 0; i < 30; i++) {
		array2[i] = rand() % 200;
	}
	cout << "Array 2: [";
	for (int i = 0; i < 30; i++) {
		cout << array2[i] << ",";
	}
	cout << "]" << endl;
	// Selection sort to sort the array in ascending order
	int startScan, minValue, minIndex;
	for (int startScan = 0; startScan < (30 - 1); startScan++) {
		minIndex = startScan;
		minValue = array2[startScan];
		for (int i = startScan + 1; i < 30; i++) {
			if (array2[i] < minValue) {
				minValue = array2[i];
				minIndex = i;
			}
		}
		array2[minIndex] = array2[startScan];
		array2[startScan] = minValue;
	}

	// Selection sort to sort the array in descending order
	int maxValue, maxIndex;
	for (startScan = 0; startScan < (20 - 1); startScan++) {
		maxIndex = startScan;
		maxValue = array1[startScan];
		for (int i = startScan; i < 20; i++) {
			if (array1[i] > maxValue) {
				maxValue = array1[i];
				maxIndex = i;
			}
		}
		array1[maxIndex] = array1[startScan];
		array1[startScan] = maxValue;
	}
	cout << "Array 1 sorted descending: [";
	for (int i = 0; i < 20; i++) {
		cout << array1[i] << ",";
	}
	cout << "]" << endl;

	cout << "Array 2 sorted ascending: [";
	for (int i = 0; i < 30; i++) {
		cout << array2[i] << ",";
	}
	cout << "]" << endl;
}
bool sortedOrUnsorted(int* array, int size) {
	bool ascending = true;
	bool descending = true;
	for (int i = 0; i < size - 1; i++) {
		if (array[i] < array[i + 1]) {
			descending = false;
		}
		if (array[i] > array[i + 1]) {
			ascending = false;
		}
	}
	if (ascending) {
		cout << "The array is sorted in ascending order!" << endl;
		return ascending;
	}
	else if (descending) {
		cout << "The array is sorted in descending order" << endl;
		return descending;
	}
	else {
		cout << "The array is not sorted!" << endl;
		return false;
	}
}
void findmaxminmedian(int array[], int size) {
	int firstMax, secondMax, firstMin, secondMin;
	float median;
	firstMax = array[0];
	secondMax = array[0];
	firstMin = array[size - 1];
	secondMin = array[size - 1];
	for (int i = 0; i < size; i++) {
		if (array[i] > firstMax) {
			firstMax = array[i];
		}

		if (array[i] < firstMin) {
			firstMin = array[i];
		}
	}
	for (int i = 0; i < size; i++) {
		if (array[i] > secondMax) {
			if (array[i] < firstMax) {
				secondMax = array[i];
			}
		}
		if (array[i] < secondMin) {
			if (array[i] > firstMin) {
				secondMin = array[i];
			}
		}
	}
	bubbleSort1D(array, size);
	if (size % 2 == 0) {
		median = (array[(size - 1) / 2] + array[size / 2]) / 2.0;
	}
	else if (size % 2 != 0) {
		median = array[(size / 2)];
	}
	cout << "First Maximum: " << firstMax << "\t Second Maximum: " << secondMax << "\t First Minimum: " << firstMin;
	cout << "\t Second Minimum: " << secondMin << "\t Median = " << median << endl;
}
void evenOddArray(int array[], int size) {
	int* oddArray = new int[size];
	int* evenArray = new int[size];
	int oddCount = 0, evenCount = 0;
	for (int i = 0; i < size; i++) {
		if (array[i] % 2 == 0) {
			*(evenArray + evenCount) = array[i];
			evenCount++;
		}
		else if (array[i] % 2 != 0) {
			*(oddArray + oddCount) = array[i];
			oddCount++;
		}
	}
	cout << "The original Array is: ";
	print1DArray(array, size);
	cout << "The even Array is: ";
	print1DArray(evenArray, evenCount);
	cout << "The odd Array is: ";
	print1DArray(oddArray, oddCount);
}
void fibonacciArray(int size) {
	int* array = new int[size];
	int zero = 0, first = 1, previous = 1, current = zero + first, next;
	array[0] = zero;
	array[1] = first;
	array[2] = current;
	for (int i = 3; i < size; i++) {
		next = previous + current;
		previous = current;
		current = next;
		array[i] = current;
	}
	print1DArray(array, size);
}
int howManyPrimes(int array[], int size) {
	int counter = 0;
	for (int i = 0; i < size; i++) {
		if (isPrime_HighlyOptimized(array[i])) {
			counter++;
		}
	}
	return counter;
}
void decimaltoBinary(int number) {
	if (number == 0) {
		cout << "0" << endl;
		return;
	}

	char binary[32]; // Enough for 32-bit integer
	int index = 0;

	while (number > 0) {
		int bit = number % 2;
		binary[index++] = '0' + bit; // adds 0 if 0 (0+0 = 0), 1 if 1 (0+1=1). 
		number /= 2;
	}

	// Print in reverse order (no string reversal needed)
	for (int i = index - 1; i >= 0; i--) {
		cout << binary[i];
	}
	cout << endl;
}
void numberOfOccurences(int array[], int size) {
	// Arrays to store unique numbers and their counts
	int* unique = new(nothrow) int[size];
	int* count = new(nothrow) int[size];
	int uniqueCount = 0;

	// Check if memory allocation was successful
	if (unique == nullptr || count == nullptr) {
		cout << "Memory allocation failed!" << endl;
		return;
	}

	// Count occurrences of each number
	for (int i = 0; i < size; i++) {
		int currentNum = *(array + i);
		bool found = false;

		// Check if number already exists in unique array
		for (int j = 0; j < uniqueCount; j++) {
			if (*(unique + j) == currentNum) {
				*(count + j) += 1;  // Increment count
				found = true;
				break;
			}
		}

		// If number not found, add it to unique array
		if (!found) {
			*(unique + uniqueCount) = currentNum;
			*(count + uniqueCount) = 1;
			uniqueCount++;
		}
	}

	// Print results
	cout << "\nNumber occurrences:" << endl;
	cout << "Number\tCount" << endl;
	cout << "--------------" << endl;
	for (int i = 0; i < uniqueCount; i++) {
		cout << *(unique + i) << "\t" << *(count + i) << endl;
	}

	// Free allocated memory
	delete[] unique;
	delete[] count;
}

int** matrixSubtraction(int** array1, int row1, int col1, int** array2, int row2, int col2) {
	int** array3 = new int* [row1];
	for (int i = 0; i < row1; i++) {
		array3[i] = new int[col1];
	}
	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < col1; j++) {
			array3[i][j] = array1[i][j] - array2[i][j];
		}
	}

	return array3;

}
int** matrixTranspose(int** array, int rows, int columns) {
	int** arrayT = new int* [columns];
	for (int i = 0; i < columns; i++) {
		arrayT[i] = new int[rows];
	}
	// The outer loop iterates through the new rows (original columns)
	for (int i = 0; i < columns; ++i) {
		// The inner loop iterates through the new columns (original rows)
		for (int j = 0; j < rows; ++j) {
			arrayT[i][j] = array[j][i]; // Correct assignment:
			// The element at old_row 'j' and old_col 'i'
			// goes to new_row 'i' and new_col 'j'.
		}
	}
	return arrayT;
}
int** matrixMultiplication(int** arrayA, int rowsA, int columnsA,
	int** arrayB, int rowsB, int columnsB) {

	if (columnsA != rowsB) {
		cout << "Matrix Multiplication not possible!";
		return nullptr;
	}
	int** arrayC = new int* [rowsA];
	for (int i = 0; i < rowsA; i++) {
		arrayC[i] = new int[columnsB];
	}
	for (int i = 0; i < rowsA; i++) {
		for (int j = 0; j < columnsB; j++) {
			arrayC[i][j] = 0; // initializing the resultant array
			for (int k = 0; k < columnsA; k++) {
				arrayC[i][j] += arrayA[i][k] * arrayB[k][j];
			}
		}

	}
	return arrayC;
}

int numberOfPrimes(int** array, int row, int col) {
	int count = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (isPrime_HighlyOptimized(array[i][j])) {
				count++;
			}
		}
	}

	return count;
}
int* twoDimensionaltoOneDimensional(int** array, int row, int col) {
	int dimension = row * col;
	int* flattenedArray = new int[dimension];
	int index1D = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			flattenedArray[index1D] = array[i][j];
			index1D++;
		}
	}
	return flattenedArray;

}
int** oneDimensionaltoTwoDimensional(int* array, int row, int column) {
	int** array2D = new int* [row];
	for (int i = 0; i < row; i++) {
		array2D[i] = new int[column];
	}
	int totalElements = row * column;
	for (int k = 0; k < totalElements; k++) {
		// Think about these two formulas. They make sense because integer division will give you the row
		// while modulo will give you column. 0-2/3 = 0 row. 0%3 = 0 column, 1 % 3 = 1 column, ... so on. 
		int rowIndex = k / column;
		int columnIndex = k % column;
		array2D[rowIndex][columnIndex] = array[k];
	}
	return array2D;
}
void sumOfDiagonals(int** array, int row, int column) {
	int sum1 = 0, sum2 = 0;
	for (int i = 0; i < row; i++) { // main diagonal has both subscripts equal
		sum1 += array[i][i];
	}
	for (int i = 0, j = column - 1; i < row, j >= 0; i++, j--) { // other diagonal is a bit different. 
		sum2 += array[i][j];
	}
	cout << "Sum of main diagonal 1 = " << sum1 << endl;
	cout << "Sum of main diagonal 2 = " << sum2 << endl;
}
