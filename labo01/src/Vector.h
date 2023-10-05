#pragma once

/**
 * @file Vector.h
 *
 * @brief Implémentation de vecteurs simples
 *
 * Nom: Samuel Velasco
 * Code permanent : VELS66050107
 * Email : samuel.velasco.1@ens.etsmtl.ca
 *
 */

 /**
  * Ce fichier déclare et implémente la classe `Vector`.
  */

#include <cmath>
#include "MatrixBase.h"

namespace gti320 {

	/**
	 * Classe vecteur générique.
	 *
	 * Cette classe réutilise la classe `MatrixBase` et ses spécialisations de
	 * templates pour les manipulation bas niveau.
	 */
	template <typename _Scalar = double, int _Rows = Dynamic>

	class Vector : public MatrixBase<_Scalar, _Rows, 1> {
	public:

		/**
		 * Constructeur par défaut
		 */
		Vector() : MatrixBase<_Scalar, _Rows, 1>() { }

		/**
		 * Contructeur à partir d'un taille (rows).
		 */
		explicit Vector(int rows) : MatrixBase<_Scalar, _Rows, 1>(rows, 1) { }

		/**
		 * Constructeur de copie
		 */
		Vector(const Vector& other) : MatrixBase<_Scalar, _Rows, 1>(other) { }

		/**
		 * Destructeur
		 */
		~Vector() { }

		/**
		 * Opérateur de copie
		 */
		Vector& operator=(const Vector& other)
		{
			// TODO implémenter
			assert(other.size() == this->size() && other.size() > 0);
			for (int i = 0; i < this->size(); i++) {
				(*this)(i) = other(i);
			}
			return *this;
		}

		/**
		 * Accesseur à une entrée du vecteur (lecture seule)
		 */
		_Scalar operator()(int i) const
		{
			// TODO implémenter
			assert(i > -1 && i < this->size());
			_Scalar readValue = this->m_storage.data()[i];
			return readValue;
		}

		/**
		 * Accesseur à une entrée du vecteur (lecture et écriture)
		 */
		_Scalar& operator()(int i)
		{
			// TODO implémenter
			assert(i > -1 && i < this->size());
			return this->m_storage.data()[i];
		}

		/**
		 * Modifie le nombre de lignes du vecteur
		 */
		void resize(int _rows)
		{
			MatrixBase<_Scalar, _Rows, 1>::resize(_rows, 1);
		}

		/**
		 * Produit scalaire de *this et other.
		 */
		inline _Scalar dot(const Vector& other) const
		{
			// TODO implémenter
			assert(this->size() == other.size());
			_Scalar dotPAnswer = 0;

			for (int i = 0; i < this->size(); i++) {
				dotPAnswer += this->data()[i] * other.data()[i];
			}

			return dotPAnswer;
		}

		/**
		 * Retourne la norme euclidienne du vecteur
		 */
		inline _Scalar norm() const
		{
			// TODO implémenter
			_Scalar norm = 0;
			for (int i = 0; i < this->size(); i++) {
				norm += (this->data()[i]) * (this->data()[i]);
			}
			return sqrt((_Scalar)norm);
		}
	};
}
