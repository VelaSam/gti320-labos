#pragma once

/**
 * @file Math3D.h
 *
 * @brief Fonctions pour l'intinialisation et la manipulation de matrices de
 * rotation, des matrices de transformations en coordonnées homogènes et les
 * vecteurs 3D.
 *
 * Nom: Samuel Velasco
 * Code permanent : VELS66050107
 * Email :  samuel.velasco.1@ens.etsmtl.ca
 *
 */

#include "Matrix.h"
#include "Vector.h"
#include "Operators.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <math.h>


namespace gti320 {

	// Deux types de vecteurs 3D considérés ici
	typedef Vector<double, 3> Vector3d;
	typedef Vector<float, 3> Vector3f;

	// Dans le cadre de ce projet, nous considérons seulement deux
	// transformations géométriques :
	//
	//  - les rotations
	//  - les translations
	//
	// Deux types de matrices en coordonnées homogèes :
	typedef Matrix<double, 4, 4, ColumnStorage> Matrix4d;
	typedef Matrix<float, 4, 4, ColumnStorage> Matrix4f;
	// 
	// Deux types de matrices pour les rotations
	typedef Matrix<double, 3, 3, ColumnStorage> Matrix3d;
	typedef Matrix<float, 3, 3, ColumnStorage> Matrix3f;


	/**
	 * Calcul de la matrice inverse, SPÉCIALISÉ pour le cas d'une matrice de
	 * transformation rigide en coordonnées homogènes.
	 *
	 * (vous pouvez supposer qu'il s'agit d'une matrice de transformation
	 * rigide en coordonnées homogènes)
	 */
	template<>
	inline Matrix4d Matrix4d::inverse() const
	{
		// TODO : implémenter
		SubMatrix<double, 4, 4, ColumnStorage> R = (*this).block(0, 0, 3, 3);
		Matrix<double, 3, 3, RowStorage> transposedR = R.transpose<double, 3, 3, RowStorage>();
		Matrix<double, 4, 4, ColumnStorage> matrix4d();
		Vector<double, 3> t(3);

		for (int i = 0; i < t.cols(); i++)
		{
			t(i) = (*this)(i, this->rows()-1);
		}

		Vector<double, 3> mRt = -1.0 * (transposedR * t);
		Matrix4d newMatrix(this->rows(), this->cols());

		for (int i = 0; i < transposedR.rows(); i++)
		{
			for (int j = 0; j < transposedR.cols(); j++)
			{
				newMatrix(i, j) = transposedR(i,j);
			}
			newMatrix(i, this->cols()-1) = mRt(i);
		}

		return newMatrix;
	}

	/**
	 * Calcul de la matrice inverse, SPÉCIALISÉ pour le cas d'une matrice de rotation.
	 *
	 * (vous pouvez supposer qu'il s'agit d'une matrice de rotation)
	 */
	template<>
	inline Matrix3d Matrix3d::inverse() const
	{
		// TODO : implémenter
		return this->transpose<ColumnStorage>();
	}


	/**
	 * Multiplication d'une matrice 4x4 avec un vecteur 3D où la matrice
	 * représente une transformation en coordonnées homogène.
	 */
	template <typename _Scalar>
	Vector<_Scalar, 3> operator*(const Matrix<_Scalar, 4, 4, ColumnStorage>& A, const Vector<_Scalar, 3>& v)
	{
		// TODO : implémenter
		Matrix<_Scalar, 4, 1> fourByOneMat;

		for (int i = 0; i < v.rows(); i++) {
			fourByOneMat(i, 0) = v(i);
		}
		fourByOneMat(3, 0) = 1;

		auto matrixVec = A * fourByOneMat;

		Vector<_Scalar, 3> returnVector;

		for (int i = 0; i < returnVector.rows(); i++) {
			returnVector(i) = matrixVec(i, 0);
		}

		return returnVector;
	}


	/**
	 * Initialise et retourne la matrice de rotation définie par les angles
	 * d'Euler XYZ exprimés en radians.
	 *
	 * La matrice doit correspondre au produit : Rz*Ry*Rx.
	 */
	template<typename _Scalar>
	static Matrix<_Scalar, 3, 3> makeRotation(_Scalar x, _Scalar y, _Scalar z)
	{
		// TODO : implémenter
		_Scalar sinTht = sin(x);
		_Scalar cosTht = cos(x);
		_Scalar sinPhi = sin(y);
		_Scalar cosPhi = cos(y);
		_Scalar sinPsi = sin(z);
		_Scalar cosPsi = cos(z);

		Matrix<_Scalar, 3, 3> eulerMatrix;

		eulerMatrix(0, 0) = cosPhi * cosPsi;
		eulerMatrix(0, 1) = sinTht * sinPhi * cosPsi - cosTht * sinPsi;
		eulerMatrix(0, 2) = cosTht * sinPhi * cosPsi + sinTht * sinPsi;
		
		eulerMatrix(1, 0) = cosPhi * sinPsi;
		eulerMatrix(1, 1) = sinTht * sinPhi * sinPsi + cosTht * cosPsi;
		eulerMatrix(1, 2) = cosTht * sinPhi * sinPsi - sinTht * cosPsi;	

		eulerMatrix(2, 0) = -1 * sinPhi;
		eulerMatrix(2, 1) = sinTht * cosPhi;
		eulerMatrix(2, 2) = cosTht * cosPhi;

		return eulerMatrix; //	 pas bon, à changer
	}


}
