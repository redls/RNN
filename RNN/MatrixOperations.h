#include<cstdio>
#include<vector>
#include<math.h>

using namespace std;

// Multiplies the given matrix with the vector and returns a vector.
vector<double> matrixMultplication(vector<vector<double>> matrix, vector<double> vec);

// Checks the dimensions of the matrix and of the vector to see if they can be multiplied.
bool checkMatrixMultiplicationWithVector(vector<vector<double>> matrix, vector<double> vec);

// Concatenate two vectors into a new vector. You first add vec1 and then add vec2.
vector<double> concatenateTwoVectors(vector<double> vec1, vector<double> vec2);

// Apply the tanh function to every element in the given aray and return a vector with the results.
vector<double> applyTanhElementWise(vector<double> vec);

// Perform inner product of the 2 vectors and return the result back.
double vectorInnerProduct(vector<double> vec1, vector<double> vec2);

// Returns a new matrix which is the input matrix transposed.
vector<vector<double>> getTransposeMatrix(vector<vector<double>> matrix);

// Returns a new matrix which is the Hadamard product of the 2 given products.
vector<vector<double>> getHadamardProduct(vector<vector<double>> matrix1, vector<vector<double>> matrix2);

// Checks if the given matrices have the same number of lines and columns. This is for the Hadamard Product.
bool checkIfTwoMatricesHaveTheSameDimesions(vector<vector<double>> matrix1, vector<vector<double>> matrix2);
