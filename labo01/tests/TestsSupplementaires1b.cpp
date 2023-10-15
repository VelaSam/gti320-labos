/**
 * @file TestsSupplementaire1b.cpp
 *
 * @brief Tests unitaires supplémentaires de la partie 1b
 *
 * Nom:
 * Code permanent :
 * Email :
 *
 */

#include "Matrix.h"
#include "Vector.h"
#include "Math3D.h"
#include "Operators.h"

#include <gtest/gtest.h>

using namespace gti320;
// TODO vos propres tests ici


TEST(TestSupLabo1b, OperatorAddDeath) {

	Matrix<int, Dynamic, Dynamic>matrix1(4, 3);
	Matrix<int, Dynamic, Dynamic>matrix2(3, 4);

	Matrix<int, Dynamic, Dynamic>returnMatrix(3, 3);

	EXPECT_DEBUG_DEATH({ returnMatrix = matrix1 + matrix2; }, "");
}

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

TEST(TestSupLabo1b, SubtractOperator) {
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



// TEST 2
//

// TEST 3 
//

// TEST 4 
//

// TEST 5 
//

// TEST 6 
//

// TEST 7
//

// TEST 8 
//

// TEST 9 
//

// TEST 10 
//
