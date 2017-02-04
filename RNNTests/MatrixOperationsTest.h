#include <stdio.h>
#include </home/laura/cpptest-1.1.2/src/cpptest.h>
using namespace std;

class MatrixOperationsTest : public Test::Suite {
    public:
        MatrixOperationsTest() {
            TEST_ADD(MatrixOperationsTest::test_matrix_multplication_with_vector);
            TEST_ADD(MatrixOperationsTest::test_concatenate_two_vectors);
            TEST_ADD(MatrixOperationsTest::test_apply_tanh_elementwise);
            TEST_ADD(MatrixOperationsTest::test_vector_inner_product);
            TEST_ADD(MatrixOperationsTest::test_transpose_matrix_patratica);
            TEST_ADD(MatrixOperationsTest::test_transpose_matrix_nepatratica);
            TEST_ADD(MatrixOperationsTest::test_check_two_matrices_have_the_same_dimensions_true);
            TEST_ADD(MatrixOperationsTest::test_check_two_matrices_have_the_same_dimensions_false);
            TEST_ADD(MatrixOperationsTest::test_hadamard_product_of_matrices);
            TEST_ADD(MatrixOperationsTest::test_hadamard_product_of_vectors);
            TEST_ADD(MatrixOperationsTest::test_softmax);
        }
    private:
        void test_matrix_multplication_with_vector();
        void test_concatenate_two_vectors();
        void test_apply_tanh_elementwise();
        void test_vector_inner_product();
        void test_transpose_matrix_patratica();
        void test_transpose_matrix_nepatratica();
        void test_check_two_matrices_have_the_same_dimensions_true();
        void test_check_two_matrices_have_the_same_dimensions_false();
        void test_hadamard_product_of_matrices();
        void test_hadamard_product_of_vectors();
        void test_softmax();
};
