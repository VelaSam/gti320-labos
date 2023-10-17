/**
 * @file TestsSupplementaire1b.cpp
 *
 * @brief Tests unitaires supplémentaires de la partie 1b
 *
 * Nom: Samuel Velasco
 * Code permanent : VELS66050107
 * Email : samuel.velasco.1@ens.etsmtl.ca
 *
 */

#include "Matrix.h"
#include "Vector.h"
#include "Math3D.h"
#include "Operators.h"

#include <gtest/gtest.h>

using namespace gti320;

 //TEST 1 Addition de matrices generique
TEST(TestSupLabo1b, OperatorAddGoodGeneric) {
	const int rows = 5;
	const int cols = 6;

	Matrix<int, rows, cols>matrix1(rows, cols);
	Matrix<int, rows, cols>matrix2(rows, cols);


	int numberInMatrix1 = 8, numberInMatrix2 = 2;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix1(i, j) = numberInMatrix1;
			matrix2(i, j) = numberInMatrix2;
		}
	}

	Matrix<int, rows, cols> addedMatrix = matrix1 + matrix2;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			EXPECT_EQ(addedMatrix(i, j), numberInMatrix1 + numberInMatrix2);
		}
	}

}

//TEST 2
TEST(TestSupLabo1b, SubtractOperatorStatic) {
	Matrix<double, 2, 2> A;
	A(0, 0) = 1.0;
	A(0, 1) = 2.0;
	A(1, 0) = 3.0;
	A(1, 1) = 4.0;

	Matrix<double, 2, 2> B;
	B(0, 0) = 0.5;
	B(0, 1) = 1.0;
	B(1, 0) = 1.5;
	B(1, 1) = 2.0;

	Matrix<double, 2, 2> result = A - B;

	EXPECT_EQ(result(0, 0), 0.5);
	EXPECT_EQ(result(0, 1), 1.0);
	EXPECT_EQ(result(1, 0), 1.5);
	EXPECT_EQ(result(1, 1), 2.0);
}

// TEST 3 
TEST(TestSupLabo1b, SubtractOperatorColumn) {
	Matrix<int, Dynamic, Dynamic, ColumnStorage> A(3,2);
	A(0, 0) = 10;
	A(0, 1) = 20;
	A(1, 0) = 30;
	A(1, 1) = 40;
	A(2, 0) = 50;
	A(2, 1) = 60;

	Matrix<int, Dynamic, Dynamic, ColumnStorage> B(3,2);
	B(0, 0) = 5;
	B(0, 1) = 15;
	B(1, 0) = 25;
	B(1, 1) = 35;
	B(2, 0) = 45;
	B(2, 1) = 55;

	Matrix<int, Dynamic, Dynamic, ColumnStorage> result = A - B;

	EXPECT_EQ(result(0, 0), 5);
	EXPECT_EQ(result(0, 1), 5);
	EXPECT_EQ(result(1, 0), 5);
	EXPECT_EQ(result(1, 1), 5);
	EXPECT_EQ(result(2, 0), 5);
	EXPECT_EQ(result(2, 1), 5);
}

// TEST 4 
TEST(TestSupLabo1b, SubtractOperatorLine) {
	Matrix<double, Dynamic, Dynamic, RowStorage> A(2, 2);

	A(0, 0) = 1.0;
	A(0, 1) = 2.0;
	A(1, 0) = 3.0;
	A(1, 1) = 4.0;

	Matrix<double, Dynamic, Dynamic, RowStorage> B(2, 2);

	B(0, 0) = 0.5;
	B(0, 1) = 1.0;
	B(1, 0) = 1.5;
	B(1, 1) = 2.0;

	Matrix<double, Dynamic, Dynamic, RowStorage> expected_result(2, 2);
	expected_result(0, 0) = 0.5;
	expected_result(0, 1) = 1.0;
	expected_result(1, 0) = 1.5;
	expected_result(1, 1) = 2.0;

	Matrix<double> result = A - B;

	for (int i = 0; i < A.rows(); ++i) {
		for (int j = 0; j < A.cols(); ++j) {
			EXPECT_DOUBLE_EQ(result(i, j), expected_result(i, j));
		}
	}
}

// TEST 5 
TEST(TestSupLabo1b, MatrixOperatorAddDeath) {

	Matrix<int, Dynamic, Dynamic>matrix1(4, 3);
	Matrix<int, Dynamic, Dynamic>matrix2(3, 4);

	Matrix<int, Dynamic, Dynamic>returnMatrix(3, 3);

	EXPECT_DEBUG_DEATH({ returnMatrix = matrix1 + matrix2; }, "");
}

// TEST 6 
TEST(TestSupLabo1b, VectorOperatorAdd) {
	Vector<double, 3> a;
	a(0) = 1.0;
	a(1) = 2.0;
	a(2) = 3.0;

	Vector<double, 3> b;
	b(0) = 0.5;
	b(1) = 1.0;
	b(2) = 1.5;

	Vector<double, 3> expected_result;
	expected_result(0) = 1.5;
	expected_result(1) = 3.0;
	expected_result(2) = 4.5;

	Vector<double, 3> result = a + b;

	for (int i = 0; i < a.rows(); ++i) {
		EXPECT_DOUBLE_EQ(result(i), expected_result(i));
	}
}

// TEST 7
TEST(TestSupLabo1b, VectorOperatorSub) {
	Vector<double, 3> a;
	a(0) = 3.0;
	a(1) = 5.0;
	a(2) = 7.0;

	Vector<double, 3> b;
	b(0) = 1.0;
	b(1) = 2.0;
	b(2) = 3.0;

	Vector<double, 3> expected_result;
	expected_result(0) = 2.0;
	expected_result(1) = 3.0;
	expected_result(2) = 4.0;

	Vector<double, 3> result = a - b;

	for (int i = 0; i < a.rows(); ++i) {
		EXPECT_DOUBLE_EQ(result(i), expected_result(i));
	}
}

// TEST 8 
TEST(TestSupLabo1b, VectorOperatorAddDeath) {
	Vector<double> a(4);
	a(0) = 1.0;
	a(1) = 2.0;
	a(2) = 3.0;
	a(3) = 69.0;

	Vector<double> b(3);
	b(0) = 0.5;
	b(1) = 1.0;
	b(2) = 1.5;

	Vector <double, Dynamic> result;
	EXPECT_DEBUG_DEATH({ result = a + b; }, "");

}

// TEST 9 
TEST(TestSupLabo1b, MatrixOperatorSubstractDeath) {

	Matrix<int, Dynamic, Dynamic>matrix1(4, 3);
	Matrix<int, Dynamic, Dynamic>matrix2(3, 4);

	Matrix<int, Dynamic, Dynamic>returnMatrix(3, 3);

	EXPECT_DEBUG_DEATH({ returnMatrix = matrix1 - matrix2; }, "");
}

// TEST 10 
TEST(TestSupLabo1b, Matrice4x4AvecVecteur3dPourMatriceIdentite)
{
	Matrix<double, 4, 4, ColumnStorage> identityMatrix;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j)
				identityMatrix(i, j) = 1.0;
			else
				identityMatrix(i, j) = 0.0;
		}
	}

	Vector<double, 3> zeroVector;
	zeroVector.setZero();

	Vector<double, 3> resultVector = identityMatrix * zeroVector;

	for (int i = 0; i < 3; ++i) {
		EXPECT_DOUBLE_EQ(resultVector(i), 0.0);
	}
}
