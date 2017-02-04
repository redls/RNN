#include <cstdio>
#include<vector>
#include </home/laura/cpptest-1.1.2/src/cpptest.h>
#include "MatrixOperationsTest.h"
#include "../RNN/MatrixOperations.h"
using namespace std;

#define EPSILON 0.000000000001


void MatrixOperationsTest::test_matrix_multplication_with_vector() {
	vector<double> vec;
	vector<vector<double>> matrix;
	for (int i = 1; i < 4; i++) {
		vec.push_back(i);
	}
	vector<double> aux;
	for (int i = 1; i < 4; i++) {
		for (int j = 1; j < 4; j++) {
			aux.push_back(i*j);
		}
		matrix.push_back(aux);
		aux.clear();
	}
	aux.clear();
	aux.push_back(14);
	aux.push_back(28);
	aux.push_back(42);
	vector<double> result = matrixMultplicationWithVector(matrix, vec);
	if (result.size() != aux.size()) {
		cout<<"Multiplication between matrix and vector failed."<<endl;
		exit(0);
	}
	for (int i = 1; i < 4; i++) {
	 TEST_ASSERT(result[i - 1] == aux[i - 1]);
	}
}


void MatrixOperationsTest::test_concatenate_two_vectors() {
	vector<double> vec1;
	vec1.push_back(1);
	vec1.push_back(2);
	vec1.push_back(3);
	vector<double> vec2;
	vec2.push_back(4);
	vec2.push_back(5);
	vec2.push_back(6);
	vector<double> vec3 = concatenateTwoVectors(vec1, vec2);
	for (int i = 0; i < 6; i++) {
        double x = i + 1;
	    TEST_ASSERT(x == vec3[i]);
	}
}

void MatrixOperationsTest::test_apply_tanh_elementwise() {
    vector<double> vec1;
	vec1.push_back(0.1);
	vec1.push_back(0.2);
	vec1.push_back(0.3);

	vector<double> appliedTanh = applyTanhElementWise(vec1);
	if (vec1.size() != appliedTanh.size()) {
		cout<<"Application of the tanh function shanged the size of the vector."<<endl;
		exit(0);
	}
	TEST_ASSERT(tanh(0.1) == appliedTanh[0]);
	TEST_ASSERT(tanh(0.2) == appliedTanh[1]);
	TEST_ASSERT(tanh(0.3) == appliedTanh[2]);

}

void MatrixOperationsTest::test_vector_inner_product() {
    vector<double> vec1;
	vec1.push_back(1);
	vec1.push_back(2);
	vec1.push_back(3);
	vector<double> vec2;
	vec2.push_back(4);
	vec2.push_back(5);
	vec2.push_back(6);

	double result = vectorInnerProduct(vec1, vec2);

	TEST_ASSERT(32 == result);
}


void MatrixOperationsTest::test_transpose_matrix_patratica() {
    vector<vector<double>> dummyMatrix;
    int counter = 0;
    for (int i = 0; i < 3; i++) {
        vector<double> aux;
        for(int j = 0; j < 3; j++) {
            counter++;
            aux.push_back(counter);
        }
        dummyMatrix.push_back(aux);
        aux.clear();
    }
    vector<vector<double>> transposedMatrix = getTransposeMatrix(dummyMatrix);

    for (int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            TEST_ASSERT(dummyMatrix[i][j] == transposedMatrix[j][i]);
        }
    }
}

void MatrixOperationsTest::test_transpose_matrix_nepatratica() {
    vector<vector<double>> dummyMatrix;
    int counter = 0;
    for (int i = 0; i < 2; i++) {
        vector<double> aux;
        for(int j = 0; j < 5; j++) {
            counter++;
            aux.push_back(counter);
        }
        dummyMatrix.push_back(aux);
        aux.clear();
    }
    vector<vector<double>> transposedMatrix = getTransposeMatrix(dummyMatrix);

    for (int i = 0; i < 2; i++) {
        for(int j = 0; j < 5; j++) {
            TEST_ASSERT(dummyMatrix[i][j] == transposedMatrix[j][i]);
        }
    }
}

void MatrixOperationsTest::test_check_two_matrices_have_the_same_dimensions_true() {
    vector<vector<double>> dummyMatrix1;
    vector<vector<double>> dummyMatrix2;
    int counter = 0;
    for (int i = 0; i < 2; i++) {
        vector<double> aux;
        for(int j = 0; j < 5; j++) {
            counter++;
            aux.push_back(counter);
        }
        dummyMatrix1.push_back(aux);
        dummyMatrix2.push_back(aux);
        aux.clear();
    }
    bool matrixHaveSameDim = checkIfTwoMatricesHaveTheSameDimesions(dummyMatrix1, dummyMatrix2);
    TEST_ASSERT(true == matrixHaveSameDim);
}

void MatrixOperationsTest::test_check_two_matrices_have_the_same_dimensions_false() {
    vector<vector<double>> dummyMatrix1;
    vector<vector<double>> dummyMatrix2;
    int counter = 0;
    for (int i = 0; i < 2; i++) {
        vector<double> aux;
        for(int j = 0; j < 5; j++) {
            counter++;
            aux.push_back(counter);
        }
        dummyMatrix1.push_back(aux);
        dummyMatrix2.push_back(aux);
        aux.clear();
    }
    dummyMatrix1[0].push_back(3);
    bool matrixHaveSameDim = checkIfTwoMatricesHaveTheSameDimesions(dummyMatrix1, dummyMatrix2);
    TEST_ASSERT(false == matrixHaveSameDim);
}


void MatrixOperationsTest::test_hadamard_product_of_matrices() {
    vector<vector<double>> dummyMatrix1;
    vector<vector<double>> dummyMatrix2;
    int counter = 0;
    for (int i = 0; i < 2; i++) {
        vector<double> aux1;
        vector<double> aux2;
        for(int j = 0; j < 5; j++) {
            counter++;
            aux1.push_back(counter);
            aux2.push_back(counter + 5);

        }
        dummyMatrix1.push_back(aux1);
        dummyMatrix2.push_back(aux2);
        aux1.clear();
        aux2.clear();
    }

    vector<vector<double>> hadamardProduct = getMatrixHadamardProduct(dummyMatrix1, dummyMatrix2);
    for (int i = 0; i < 2; i++) {
        for(int j = 0; j < 5; j++) {
            TEST_ASSERT(dummyMatrix1[i][j] * dummyMatrix2[i][j] == hadamardProduct[i][j]);
        }
    }
}
void MatrixOperationsTest::test_hadamard_product_of_vectors() {
    vector<double> dummyVector1;
    vector<double> dummyVector2;
    int counter = 0;
    for (int i = 0; i < 4; i++) {
        counter++;
        dummyVector1.push_back(counter);
        dummyVector2.push_back(counter + 5);
    }

    vector<double> hadamardProduct = getVectorHadamardProduct(dummyVector1, dummyVector2);
    for (int i = 0; i < 4; i++) {
        TEST_ASSERT(dummyVector1[i] * dummyVector2[i] == hadamardProduct[i]);
    }
}

void MatrixOperationsTest::test_softmax() {
     vector<double> dummyVector1;
     dummyVector1.push_back(3);
     dummyVector1.push_back(5);

     // Compute the actual values of the dummy vector.
     double sum = exp(3) + exp(5);
     double firstValue = exp(3) / sum;
     double secondValue = exp(5) / sum;

     // Obtain the softamx result by calling the function.
     vector<double> softmaxResult = softmax(dummyVector1);

     TEST_ASSERT(softmaxResult.size() == 2);
     TEST_ASSERT(softmaxResult[0] - firstValue < EPSILON);
     cout<<"1:" <<firstValue<<" "<<softmaxResult[0] <<"  "<<endl;
     cout<<"2:" <<secondValue<<" "<<softmaxResult[1]<<endl;
     TEST_ASSERT(softmaxResult[1] - secondValue < EPSILON);
}
