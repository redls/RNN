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

// Returns a new matrix which is the Hadamard product of the 2 given matrices.
vector<vector<double>> getMatrixHadamardProduct(vector<vector<double>> matrix1, vector<vector<double>> matrix2);

// Returns a new matrix which is the Hadamard product of the 2 given vectors.
vector<double> getVectorHadamardProduct(vector<double> vect1, vector<double> vect2);

// Checks if the given matrices have the same number of lines and columns. This is for the Hadamard Product.
bool checkIfTwoMatricesHaveTheSameDimesions(vector<vector<double>> matrix1, vector<vector<double>> matrix2);

// Compute the softmax of a vector container.
vector<double> softmax(vector<double> vec);

/**
 * Substract, elemnt-wise 2 vector and return vector containing the result of this operation. This assumes
 * that the 2 vectors have the same dimensions.
 */
vector<double> substractTwoVectors(vector<double> firstVector, vector<double> secondVector);

/**
 * Add, elemnt-wise 2 vector and return vector containing the result of this operation. This assumes
 * that the 2 vectors have the same dimensions.
 */
vector<double> addTwoVectors(vector<double> firstVector, vector<double> secondVector);


// Obtain the derivative of the tanh function using (tanh x)' = 1 - ((tanh x)^2) (entry-wise).
vector<double> getTanhDerivativeFunction(vector<double> vec);

// Create a vector containing d elements, all equal to 0.
vector<double> getZeros(int d);


// Print the elements in a vector container.
void printElementsOfVector(vector<double> vec);

