/**
 * @file TestsSupplementaire1a.cpp
 *
 * @brief Tests unitaires supplémentaires de la partie 1a
 *
 * Nom: Samuel Velasco
 * Code permanent : VELS66050107
 * Email : samuel.velasco.1@ens.etsmtl.ca
 *
 */

#include "Matrix.h"
#include "Vector.h"

#include <gtest/gtest.h>

using namespace gti320;


//Ce test vérifie la fonctionnalité de redimensionnement (resize) d'un DenseStorage, 
// en s'assurant que la taille, les données et les pointeurs sont mis à jour 
// correctement après le redimensionnement.

TEST(TestSupLabo1a, DenseStorageResize)
{
	int initialSize = 5;
	int newSize = 10;

	DenseStorage<int, gti320::Dynamic> storage(initialSize);

	for (int i = 0; i < storage.size(); i++) {
		storage.data()[i] = 100;
	}

	storage.resize(newSize);

	//Verif si les donnees sont bels et bien changees apres le resize
	for (int i = 0; i < storage.size(); i++) {
		ASSERT_NE(storage.data()[i], 100);
	}

	//Verif si la size sest faite updater correctement;
	ASSERT_EQ(storage.size(), newSize);

	// Check if le pointeur data is not null
	ASSERT_NE(storage.data(), nullptr);

	//Remplit storage avec des donnees et verifier si les donnees sont stockees correctement apres le resize
	for (int i = 0; i < newSize; ++i) {
		storage.data()[i] = i;
	}
	for (int i = 0; i < newSize; ++i) {
		ASSERT_EQ(storage.data()[i], i);
	}
}


//Ce test vérifie que l'opérateur d'assignation fonctionne correctement 
//pour une copie profonde d'un DenseStorage<int, Dynamic>.
TEST(TestSupLabo1a, DenseStorageOperateurAssignation)
{
	int size = 5;
	DenseStorage<int, Dynamic> original(size);

	for (int i = 0; i < size; i++)
		original.data()[i] = i;

	DenseStorage<int, Dynamic> copy;

	copy = original;

	EXPECT_EQ(original.size(), copy.size());

	for (int i = 0; i < size; ++i)
		EXPECT_EQ(original.data()[i], copy.data()[i]);

	//Tester que les adresses memoires ne soient pas identiques (car on veut une copie profonde et non une copie de surface)
	EXPECT_NE(original.data(), copy.data());
}


//Ce test valide le produit scalaire de vecteurs en vérifiant des propriétés mathématiques:
//perpendicularité(doit donner 0), relation avec la norme euclidienne, et
//commutativité du produit scalaire.

TEST(TestSupLabo1a, VecteurProduitScalaire) {
	// La methode dotP sera testee en verifiant si elle concorde avec des proprietees mathematiques connues sur le produit scalaire:
		// SERIE DE VECTEURS PERPENDICULAIRES, LE DOTP DEVRAIT DONNER 0
	{
		// Vecteurs (2D)
		Vector<double, 2> v1;
		v1(0) = 7;
		v1(1) = -2;
		Vector<double, 2> v2;
		v2(0) = 2;
		v2(1) = 7;

		ASSERT_EQ(v1.dot(v2), 0);
	}
	{

		Vector<double, 3> v1;
		v1(0) = 2;
		v1(1) = -3;
		v1(2) = 1;

		Vector<double, 3> v2;
		v2(0) = 1;
		v2(1) = 2;
		v2(2) = 4;

		ASSERT_EQ(v1.dot(v2), 0);

	}
	{
		// Vecteurs 4D
		Vector<double, 4> v1;
		v1(0) = 3;
		v1(1) = 2;
		v1(2) = -1;
		v1(3) = 4;

		Vector<double, 4> v2;
		v2(0) = 2;
		v2(1) = -3;
		v2(2) = 4;
		v2(3) = 1;

	}

	//RELATION ENTRE LA NORME ET LE PRODUIT SCALAIRE
	{
		//Le dotp d'un vecteur avec lui meme devrait donner le carre de sa norme euclidienne
		Vector<double, 4> v1, v2;
		v1(0) = v2(0) = 10;
		v1(1) = v2(1) = -5;
		v1(2) = v2(2) = 4;
		v1(3) = v2(3) = 2;

		ASSERT_EQ(v1.dot(v2), (v1.norm()) * (v1.norm()));
	}

	// COMMUTATIVITE (a*b) == (b*a)
	{

		// Vecteurs 3D
		Vector<double, 3> v1, v2;
		v1(0) = 8;
		v1(1) = 2;
		v1(2) = 10;

		v2(0) = 4;
		v2(1) = 5;
		v2(2) = 3;

		//test de commutation
		ASSERT_EQ(v1.dot(v2), v2.dot(v1));
	}
}
// Ce test vérifie que l'opérateur d'assignation pour un vecteur fonctionne 
// correctement en copiant les données d'un vecteur original dans un vecteur
// copie et en vérifiant que les données sont identiques après l'assignation.
TEST(TestSupLabo1a, VecteurOperateurAssignation) {

	int sizeVecteur = 1000;
	Vector<int> v(sizeVecteur);

	for (int i = 0; i < sizeVecteur; i++) {
		v(i) = i - sizeVecteur;
	}

	Vector<int> copieV(sizeVecteur);
	copieV = v;

	for (int i = 0; i < sizeVecteur; i++) {
		ASSERT_EQ(v.data()[i], copieV.data()[i]);
	}
}

// Ce test valide l'accès en lecture seule aux éléments d'un vecteur en 
// vérifiant que les éléments accessibles correspondent aux valeurs
// calculées et stockées précédemment dans le vecteur.
TEST(TestSupLabo1a, VectorReadOnlyAccess) {
	gti320::Vector<double> vec(5);

	for (int i = 0; i < 5; i++) {
		vec(i) = i * 2.5;
	}

	// Acceder et verifier les elements (read-only)
	for (int i = 0; i < 5; i++) {
		EXPECT_EQ(vec(i), i * 2.5); // Verifier egalite 
	}
}

TEST(TestSupLabo1a, MatriceOperateurAssignationRows) {
	Matrix<int, 4, 4, RowStorage> matrix;

	//remplir avec des valeurs 
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix(i, j) = 10;
		}
	}

	Matrix<int, 4, 4, RowStorage> matrixFromSub;

	matrixFromSub = matrix;

	//tester que les valeurs des deux matrices correspondents
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			EXPECT_EQ(matrixFromSub(i, j), matrix(i, j));
		}
	}

}

//Ce test vérifie que l'opérateur d'assignation pour une matrice(basé sur le stockage par rangées)
// fonctionne correctement en copiant les valeurs de la matrice originale dans une matrice copie, 
// puis en vérifiant que les valeurs sont identiques après l'assignation.
TEST(TestSupLabo1a, MatriceOperateurAssignationColonnes) {
	Matrix<int, 4, 4, ColumnStorage> matrix;

	//remplir avec des valeurs random
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix(i, j) = rand() % 100;
		}
	}

	Matrix<int, 4, 4, ColumnStorage> matrixFromSub;

	matrixFromSub = matrix;

	//tester que les valeurs des deux matrices correspondents
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			EXPECT_EQ(matrixFromSub(i, j), matrix(i, j));
		}
	}

}
// Ce test valide la création et l'accès aux sous-matrices d'une matrice en modifiant
// les valeurs de certaines sous matrices et en vérifiant que ces changements sont 
// reflétés dans la matrice d'origine, tout en s'assurant qu'il n'y a pas de valeur originales
// dans la matrice.
TEST(TestSupLabo1a, SousMatriceOperateurAccesseur) {
	Matrix<int, 4, 4, RowStorage> matrix;

	//remplir avec des valeurs 
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix(i, j) = rand() % 100;
		}
	}

	SubMatrix<int, 4, 4, RowStorage> submatrixOne(matrix, 0, 0, 2, 2);
	SubMatrix<int, 4, 4, RowStorage> submatrixTwo(matrix, 0, 2, 2, 2);
	SubMatrix<int, 4, 4, RowStorage> submatrixThree(matrix, 2, 0, 2, 2);
	SubMatrix<int, 4, 4, RowStorage> submatrixFour(matrix, 2, 2, 2, 2);


	// remplir les valeurs de les sous matrice avec des 1,2,3 ou 4;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			submatrixOne(i, j) = 1;
			submatrixTwo(i, j) = 2;
			submatrixThree(i, j) = 3;
			submatrixFour(i, j) = 4;
		}
	}

	//tester quil ne reste aucun 5 dans la matrice et que toutes les valeurs soient des 1,2,3 ou 4;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			EXPECT_NE(matrix(i, j), 5);
		}
	}

}


//Ce test vérifie que l'opérateur d'assignation pour une sous matrice fonctionne correctement 
//en copiant les valeurs de la sous matrice dans une nouvelle matrice, puis en vérifiant que 
//les valeurs sont identiques après l'assignation.
TEST(TestSupLabo1a, SousMatriceOperateurAssignation) {
	Matrix<int, 4, 4, RowStorage> matrix;

	//remplir avec des valeurs 
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix(i, j) = rand() % 100;
		}
	}

	SubMatrix<int, 4, 4, RowStorage> submatrixOne(matrix, 0, 0, 2, 2);
	Matrix<int, 2, 2, RowStorage> matrixFromSub;

	matrixFromSub = submatrixOne;

	//tester que les valeurs des deux matrices correspondents
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			EXPECT_EQ(submatrixOne(i, j), matrixFromSub(i, j));
		}
	}
}

//Ce test vérifie que la fonction de transposition pour une sous matrice fonctionne 
//correctement en vérifiant que les valeurs correspondent entre la sous matrice et 
//la matrice transposée après la transposition.

TEST(TestSupLabo1a, SubMatrixTranspose) {

	Matrix<int, 10, 10, RowStorage> matrix;

	//remplir avec des valeurs 
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			matrix(i, j) = rand() % 100;
		}
	}

	SubMatrix<int, 10, 10, RowStorage> subMatrixOne(matrix, 0, 0, 2, 2);


	subMatrixOne(0, 1) = rand() % 100;
	subMatrixOne(1, 0) = rand() % 100;

	Matrix<double, 2, 2, 0> transposedMatrix = subMatrixOne.transpose<double, 2, 2, 0>();

	//tester si les valeurs correspondent entre la SousMatrice et la matrice tranposee
	ASSERT_EQ(subMatrixOne(0, 1), transposedMatrix(1, 0));
	ASSERT_EQ(subMatrixOne(1, 0), transposedMatrix(0, 1));
}
