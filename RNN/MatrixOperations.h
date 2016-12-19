#include<cstdio>
#include<vector>
#include<math.h>

using namespace std;

// Multiplies the given matrix with the vector and returns a vector.
vector<double> matrixMultplication(vector<vector<double>> matrix, vector<double> vec);

// Checks the dimensions of the matrix and of the vector to see if they can be multiplied.
bool checkMatrixMultiplication(vector<vector<double>> matrix, vector<double> vec);

// Concatenate two vectors into a new vector. You first add vec1 and then add vec2.
vector<double> concatenateTwoVectors(vector<double> vec1, vector<double> vec2);

// Apply the tanh function to every element in the given aray and return a vector with the results.
vector<double> applyTanhElementWise(vector<double> vec);

// Perform inner product of the 2 vectors and return the result back.
double vectorInnerProduct(vector<double> vec1, vector<double> vec2);
