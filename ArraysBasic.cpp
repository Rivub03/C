#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <cmath>
using namespace std;

const int col = 3;

void showValues(int[], int); // show a 1D array
void showArray(int[][col], int); // show 2D array
void sumRows(int[][col], int); // sum rows of a 2D array
void sumColumns(int[][col], int); // sum columns of a 2D array
int sumOfAllElements(int[][col], int); // sum all elements of a 2D array

int main() {

    const int months = 12;
    int days[months] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    int highest = days[0];
    for (int i = 0; i < months; i++) {
        if (days[i] > highest) {
            highest = days[i];
        }
    }
    cout << highest << endl;


    double total = 0, average;
    for (int i = 0; i < months; i++) {
        total += days[i];
    }
    average = total / months;
    cout << average << endl;

    int const size = 10;
    int firstArray[size] = { 1,2,3,4,5,6,7,8,9,10 };
    int secondArray[size] = { 1,2,3,4,5,6,7,8,9,11 };
    bool arraysEqual = true;
    int i = 0;
    while (arraysEqual && i < size) {
        if (firstArray[i] != secondArray[i]) {
            arraysEqual = false;
        }
        i++;
    }
    if (arraysEqual) {
        cout << "Arrays are equal";
    }
    else {
        cout << "Arrays are not equal";
    }

    int hours[10] = { 10,12,14,8,12,20,19,19,18,17 };
    double payRate[10] = { 8,8,8,8,4,8,10,10,10,9 };
    cout << "Here is the gross pay for each employee: " << endl;
    for (int i = 0; i < 10; i++) {
        double grossPay = hours[i] * payRate[i];
        cout << "Employee#" << i << ": $" << grossPay << endl;
    }

    showValues(hours, 10);

    const int row = 5, column = 3;
    //initializing an array
    int array[row][column] = { {8,6,5},{2,4,5},{1,2,4},{8,9,3},{7,9,3} };
    cout << "The 2D array is: " << endl;
    for (int i = 0; i < row; i++) {
        cout << "[ ";
        for (int j = 0; j < column; j++) {
            cout << array[i][j] << " ";
        }
        cout << "]" << endl;
    }

    showArray(array, row);
    sumRows(array, row);
    sumColumns(array, row);
    sumOfAllElements(array, row);

    return 0;



}

void showValues(int nums[], int size) {
    for (int i = 0; i < size; i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
}

void showArray(int array[][col], int row) {
    cout << "The 2D array from function is : " << endl;
    for (int i = 0; i < row; i++) {
        cout << "[ ";
        for (int j = 0; j < col; j++) {
            cout << array[i][j] << " ";
        }
        cout << "]" << endl;
    }
}

void sumRows(int array[][col], int row) {
    double total, average; //imagine each row represents a student, and each column a class subject. 
    for (int i = 0; i < row; i++) {
        total = 0; //reinitialized for each row
        for (int j = 0; j < col; j++) {
            total += array[i][j];
        }
        average = total / col;
        cout << "The average of student #" << i << " is: " << average << endl;
    }
}

void sumColumns(int array[][col], int row) {
    double total, average;
    for (int j = 0; j < col; j++) {
        total = 0; //reinitialized for each row
        for (int i = 0; i < row; i++) {
            total += array[i][j];
        }
        average = total / row;
        cout << "Class average for test " << j + 1 << " is " << average << endl;
    }
}

int sumOfAllElements(int array[][col], int row) {
    double total = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            total += array[i][j];
        }
    }
    cout << "The total is: " << total << endl;
    return total;
}



