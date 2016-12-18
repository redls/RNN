#include<cstdio>
#include "MatrixOperations.h"

using namespace std;

// Checks the dimensions of the matrix and of the vector to see if they can be multiplied.
bool checkMatrixMultiplication(vector<vector<double>> matrix, vector<double> vec) {
    int n = matrix.size(); // number of lines
    if (n == 0) return false;
    int m = matrix[0].size(); // number of columns
    int d = vec.size(); // number of elements in the array

    if (m == d) return true;
    return false;
}

// Multiplies the given matrix with the vector and returns a vector.
vector<double> matrixMultplication(vector<vector<double>> matrix, vector<double> vec) {
    vector<double> result;
    if (!checkMatrixMultiplication(matrix, vec)) return result;

    int n = matrix.size(); // number of lines
    int m = matrix[0].size(); // number of columns
    int d = vec.size(); // number of elements in the array

    double s = 0; // current sum
    for (int i = 0; i < n; i++) {
        s = 0;
        for (int j = 0;j < m; j++) {
            s = s + matrix[i][j] * vec[j];
        }
        result.push_back(s);
        s = 0;
    }
    return result;
}

// Concatenate two vectors into a new vector. You first add vec1 and then add vec2.
vector<double> concatenateTwoVectors(vector<double> vec1, vector<double> vec2) {
    vector<double> result;
    for (int i = 0; i < vec1.size(); i++) {
        result.push_back(vec1[i]);
    }
    for (int i = 0; i < vec2.size(); i++) {
        result.push_back(vec2[i]);
    }
    return result;
}
