#include<cstdio>
#include "MatrixOperations.h"

using namespace std;

// Checks the dimensions of the matrix and of the vector to see if they can be multiplied.
bool checkMatrixMultiplicationWithVector(vector<vector<double>> matrix, vector<double> vec) {
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
    if (!checkMatrixMultiplicationWithVector(matrix, vec))  {
        perror("The matrix multiplication with the vector could not be computed. The 2 given inputs cannot be multiplied.");
        //return result;
    }
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

// Apply the tanh function to every element in the given aray and return a vector with the results.
vector<double> applyTanhElementWise(vector<double> vec) {
    vector<double> result;
     for (int i = 0; i < vec.size(); i++) {
        result.push_back(tanh(vec[i]));
    }
    return result;
}

// Perform inner product of the 2 vectors and return the result back.
double vectorInnerProduct(vector<double> vec1, vector<double> vec2) {
    double result;
    for (int i = 0; i < vec1.size(); i++) {
        result = result + vec1[i]*vec2[i];
    }
    return result;
}

// Returns a new matrix which is the input matrix transposed.
vector<vector<double>> getTransposeMatrix(vector<vector<double>> matrix) {
    vector<vector<double>> result;
    int numberOfLines = matrix.size();
    int numberOfColumns = 0;
    if (numberOfLines != 0) numberOfColumns = matrix[0].size();
    // Transpose the first line, in order to obtain the lines of the transpose matrix in order
    // to create the entry vectors for each line.
    for(int i = 0; i < numberOfColumns; i++) {
        vector<double> numberToInsert;
        numberToInsert.push_back(matrix[0][i]);
        result.push_back(numberToInsert);
    }

    // Transpose the rest of the matrix.
    for(int i = 1; i < numberOfLines; i++) {
        for(int j = 0; j < numberOfColumns; j++) {
            result[j].push_back(matrix[i][j]);
        }
    }
    return result;
}

// Checks if the given matrices have the same number of lines and columns. This is for the Hadamard Product.
bool checkIfTwoMatricesHaveTheSameDimesions(vector<vector<double>> matrix1, vector<vector<double>> matrix2) {
    int l1 = matrix1.size();
    int l2 = matrix2.size();
    if (l1 != l2) return false;
    if (l1 > 0) {
        int c1 = matrix1.size();
        int c2 = matrix2.size();
        if (c1 != c2) return false;
        else return true;
    }
    return true;
}

 // Returns a new matrix which is the Hadamard product of the 2 given matrices.
vector<vector<double>> getMatrixHadamardProduct(vector<vector<double>> matrix1, vector<vector<double>> matrix2) {
    vector<vector<double>> result;
    if (!checkIfTwoMatricesHaveTheSameDimesions(matrix1, matrix2)) {
        perror("The 2 matrices don't have the same dimesions. Cannot obtain their Hadamard product.");
    }
    int numberOfColumns = matrix1[0].size();
    int numberOfLines = matrix1.size();

    // Multiply the first line, in order to obtain the lines of the transpose matrix in order
    // to create the entry vectors for each line.
    for(int i = 0; i < numberOfLines; i++) {
        vector<double> numberToInsert;
        for(int j = 0; j < numberOfColumns; j++) {
            numberToInsert.push_back(matrix1[i][j] * matrix2[i][j]);
        }
        result.push_back(numberToInsert);
    }
    return result;
}


// Returns a new matrix which is the Hadamard product of the 2 given vectors.
vector<double> getVectorHadamardProduct(vector<double> vect1, vector<double> vect2) {
    vector<double> result;
    double numberToInsert;
    for(int i = 0; i < vect1.size(); i++) {
        numberToInsert = vect1[i] *vect2[i];
        result.push_back(numberToInsert);
    }
    return result;
}


// Compute the softmax of a vector container.
vector<double> softmax(vector<double> vec) {
    double sum = 0;
    double temp;
    for (int i = 0; i < vec.size(); i++) {
        sum = sum + exp(vec[i]);
    }
    vector<double> result;
    for (int i = 0; i < vec.size(); i++) {
        temp = exp(vec[i]) / sum;
        result.push_back(temp);
    }
    return result;
}


/**
 * Substract, elemnt-wise 2 vector and return vector containing the result of this operation. This assumes
 * that the 2 vectors have the same dimensions.
 */
vector<double> substractTwoVectors(vector<double> firstVector, vector<double> secondVector) {
    vector<double> result;
    double difference;
    for (int i = 0; i < firstVector.size(); i++) {
        difference = firstVector[i] - secondVector[i];
        result.push_back(difference);
    }
    return result;
}

/**
 * Add, elemnt-wise 2 vector and return vector containing the result of this operation. This assumes
 * that the 2 vectors have the same dimensions.
 */
vector<double> addTwoVectors(vector<double> firstVector, vector<double> secondVector) {
    vector<double> result;
    double addition;
    for (int i = 0; i < firstVector.size(); i++) {
        addition = firstVector[i] + secondVector[i];
        result.push_back(addition);
    }
    return result;
}


// Obtain the derivative of the tanh function using (tanh x)' = 1 - ((tanh x)^2) (entry-wise).
vector<double> getTanhDerivativeFunction(vector<double> vec) {
    vector<double> result;
    double aux;
    double currentElement;
    for (int i = 0; i < vec.size(); i++) {
        currentElement = vec[i];
        aux = 1 - (currentElement * currentElement);
        result.push_back(aux);
    }
    return result;
}
