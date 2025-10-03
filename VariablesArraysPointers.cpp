// This code demonstrates the different ways to pass arrays, variables as function parameters using pointers and the different ways to print arrays using a 
// combination of pointers and subscript notation. 
#include <iostream>
#include <iomanip>
using namespace std;

void printarray1(int[], int);
void printarray2(int[], int);
void printarray3(int[], int);
void printarray4(int[], int);
void printarray5(int[], int);
void passByReference(int&);
void passPointer(int*); 
void passPointerArray(int*, int);
void passArray(int[], int);
int* returningArray(int*, int);

int main() {

    int size1, size2, *array1, *array2;
    passByReference(size1); // the variable is passed by reference as argument which uses its memory location as parameter 
    passPointer(&size2); // variable's memory location is passed as argument which is caught by the pointer parameter
    cout << "Size of array 1 is: " << size1 << endl;
    cout << "Size of array 2 is: " << size2<< endl;
    
    array1 = new int[size1]; //Dynamic Memory Allocation
    array2 = new int[size2];

    passPointerArray(array1, size1); // One way of passing an array using pointers 
    passArray(array2,size2); // One way of passing an array without using pointers 
    printarray1(array1, size1); // passing array1 the old fashioned way again but using a different printing method
    printarray2(array2, size2); // poassing array2 the old fashioned way again '' ' '' ' ' ' '
    printarray3(array1, size1); // passing array1 ' ' ' ' ' ' ''  ' ' '
    printarray4(array2, size2); // ditto
    printarray5(array1, size1); // ditto 

    returningArray(array1, size1); // returns array multiplied by 2. Maybe a new variable could catch it but not necessary. 
    printarray1(array1, size1); // prints new array multiplied by 2


    delete[] array1;
    delete[] array2;

    return 0;
}

void passArray(int arr[], int size) { 
    for (int i = 0; i < size; i++) {
        cout << "Enter element " << (i + 1) << " : ";
        cin >> arr[i];
    }
}
void passPointerArray(int* arr, int size) { // *arr = sales 
    for (int i = 0; i < size; i++) {
        cout << "Enter the number " << (i+1) << ": ";
        cin >> *arr++; // hence *(arr+1) works here
    }
}
void passByReference(int& val) {
    cout << "Size of the first array: ";
    cin >> val;
}
void passPointer(int* val) {
    cout << "Size of the second array: ";
    cin >> *val;
}
// Multiple ways to print arrays using pointers
void printarray1(int arr[], int size) {
    cout << "The numbers in the array are: ";
    for (int i = 0; i < size; i++) {
        cout << *(arr + i);
    }
    cout << endl;
}
void printarray2(int arr[], int size) {
    int* ptr = arr;
    cout << "The numbers in the array are: ";
    for (int i = 0; i < size; i++) {
        cout << ptr[i] << " ";
    }
    cout << endl;
}
void printarray3(int arr[], int size) {
    int* ptr = arr;
    cout << "The numbers in the array are: ";
    for (int i = 0; i < size; i++) {
        ptr = &arr[i];
        cout << *ptr << " ";
    }
    cout << endl;
}
void printarray4(int arr[], int size) {

    int* nums = arr;
    cout << "The numbers in the array are: " << *nums << " ";
    while (nums < &arr[size-1]){ // size-1 because an array of size 8 will have last element at arr[7] 
        nums++;
        cout << *nums << " ";
    }
    cout << endl;
}
void printarray5(int arr[], int size) { // prints array forwards and backwards
    int* numPtr = arr;
    cout << "The numbers in the set are: ";
    for (int i = 0; i < size; i++) {
        cout << *numPtr << " "; 
        numPtr++; //the two statements become cout << *(numPtr+1)
    }
    for (int i = 0; i < size; i++) {
        numPtr--;
        cout << *numPtr << " ";
    }
    cout << endl;
}
int* returningArray(int* arr, int size) { //multiplies array elements by 2 and returns it
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;
    }
    return arr; // no point returning it since original array is ammended. example is to show functionality. 
}
