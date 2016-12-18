#include<cstdio>
#include<vector>

using namespace std;

// Multiplies the given matrix with the vector and returns a vector.
vector<double> matrixMultplication(vector<vector<double>> matrix, vector<double> vec);

// Checks the dimensions of the matrix and of the vector to see if they can be multiplied.
bool checkMatrixMultiplication(vector<vector<double>> matrix, vector<double> vec);

// Concatenate two vectors into a new vector. You first add vec1 and then add vec2.
vector<double> concatenateTwoVectors(vector<double> vec1, vector<double> vec2);
