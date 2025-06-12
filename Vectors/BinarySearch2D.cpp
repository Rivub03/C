#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Approach 1: Treat 2D array as flattened 1D array (fully sorted)
// Works when the 2D array is sorted row-wise and column-wise as one continuous sequence
pair<int, int> BinarySearch2D_Flattened(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) {
        return { -1, -1 };
    }

    int rows = matrix.size();
    int cols = matrix[0].size();
    int left = 0;
    int right = rows * cols - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;

        // Convert 1D index back to 2D coordinates
        int row = middle / cols;
        int col = middle % cols;
        int middle_value = matrix[row][col];

        if (middle_value == target) {
            return { row, col };  // Found! Return coordinates
        }
        else if (middle_value < target) {
            left = middle + 1;
        }
        else {
            right = middle - 1;
        }
    }

    return { -1, -1 };  // Not found
}

// Approach 2: Row-wise sorted matrix (each row sorted, but rows not necessarily related)
// First find which row might contain the target, then search within that row
pair<int, int> BinarySearch2D_RowWise(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) {
        return { -1, -1 };
    }

    int rows = matrix.size();
    int cols = matrix[0].size();

    // Search each row individually
    for (int row = 0; row < rows; row++) {
        // Skip rows where target is clearly not present
        if (target < matrix[row][0] || target > matrix[row][cols - 1]) {
            continue;
        }

        // Binary search within this row
        int left = 0;
        int right = cols - 1;

        while (left <= right) {
            int middle = left + (right - left) / 2;

            if (matrix[row][middle] == target) {
                return { row, middle };
            }
            else if (matrix[row][middle] < target) {
                left = middle + 1;
            }
            else {
                right = middle - 1;
            }
        }
    }

    return { -1, -1 };  // Not found
}

// Approach 3: Staircase search (matrix sorted row-wise and column-wise)
// Start from top-right or bottom-left corner
pair<int, int> BinarySearch2D_Staircase(vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) {
        return { -1, -1 };
    }

    int rows = matrix.size();
    int cols = matrix[0].size();

    // Start from top-right corner
    int row = 0;
    int col = cols - 1;

    while (row < rows && col >= 0) {
        int current_value = matrix[row][col];

        if (current_value == target) {
            return { row, col };  // Found!
        }
        else if (current_value > target) {
            col--;  // Move left (smaller values)
        }
        else {
            row++;  // Move down (larger values)
        }
    }

    return { -1, -1 };  // Not found
}

// Function to sort a 2D array as a flattened sequence
void Sort2DArray_Flattened(vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) return;

    // Flatten the 2D array into 1D
    vector<int> flattened;
    for (const auto& row : matrix) {
        for (int val : row) {
            flattened.push_back(val);
        }
    }

    // Sort the flattened array
    sort(flattened.begin(), flattened.end());

    // Put sorted values back into 2D array
    int index = 0;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            matrix[i][j] = flattened[index++];
        }
    }
}

// Function to sort each row of a 2D array individually
void Sort2DArray_RowWise(vector<vector<int>>& matrix) {
    for (auto& row : matrix) {
        sort(row.begin(), row.end());
    }
}

// Utility function to print a 2D array
void Print2DArray(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Example usage and testing
int main() {
    // Example 1: Fully sorted 2D array (for flattened approach)
    cout << "=== Example 1: Fully Sorted 2D Array (Flattened) ===" << endl;
    vector<vector<int>> matrix1 = {
        {1,  4,  7,  11},
        {12, 15, 18, 21},
        {23, 26, 29, 32},
        {35, 38, 41, 44}
    };

    Print2DArray(matrix1);

    int target1 = 18;
    auto result1 = BinarySearch2D_Flattened(matrix1, target1);
    cout << "Searching for " << target1 << ": ";
    if (result1.first != -1) {
        cout << "Found at (" << result1.first << ", " << result1.second << ")" << endl;
    }
    else {
        cout << "Not found" << endl;
    }

    // Example 2: Row-wise sorted matrix
    cout << "\n=== Example 2: Row-wise Sorted Matrix ===" << endl;
    vector<vector<int>> matrix2 = {
        {1, 3, 5, 7},
        {2, 4, 6, 8},
        {9, 10, 11, 12}
    };

    Print2DArray(matrix2);

    int target2 = 6;
    auto result2 = BinarySearch2D_RowWise(matrix2, target2);
    cout << "Searching for " << target2 << ": ";
    if (result2.first != -1) {
        cout << "Found at (" << result2.first << ", " << result2.second << ")" << endl;
    }
    else {
        cout << "Not found" << endl;
    }

    // Example 3: Matrix sorted both row-wise and column-wise (for staircase)
    cout << "\n=== Example 3: Row and Column Sorted Matrix (Staircase) ===" << endl;
    vector<vector<int>> matrix3 = {
        {1,  4,  7,  11},
        {2,  5,  8,  12},
        {3,  6,  9,  16},
        {10, 13, 14, 17}
    };

    Print2DArray(matrix3);

    int target3 = 5;
    auto result3 = BinarySearch2D_Staircase(matrix3, target3);
    cout << "Searching for " << target3 << ": ";
    if (result3.first != -1) {
        cout << "Found at (" << result3.first << ", " << result3.second << ")" << endl;
    }
    else {
        cout << "Not found" << endl;
    }

    // Example 4: Sorting a 2D array
    cout << "\n=== Example 4: Sorting 2D Arrays ===" << endl;
    vector<vector<int>> unsorted_matrix = {
        {9, 3, 7, 1},
        {8, 2, 6, 4},
        {5, 12, 10, 11}
    };

    cout << "Original matrix:" << endl;
    Print2DArray(unsorted_matrix);

    // Sort as flattened array
    auto matrix_copy1 = unsorted_matrix;
    Sort2DArray_Flattened(matrix_copy1);
    cout << "Sorted as flattened array:" << endl;
    Print2DArray(matrix_copy1);

    // Sort row-wise
    auto matrix_copy2 = unsorted_matrix;
    Sort2DArray_RowWise(matrix_copy2);
    cout << "Sorted row-wise:" << endl;
    Print2DArray(matrix_copy2);

    return 0;
}