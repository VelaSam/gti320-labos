#pragma once

/**
 * @file Matrix.h
 *
 * @brief Implémentation de matrices simples.
 *
 * Nom: Samuel Velasco
 * Code permanent : VELS66050107
 * Email : samuel.velasco.1@ens.etsmtl.ca
 *
 */

 /**
  * Ce fichier déclare et implémente les classes `Matrix` et `SubMatrix`.
  */


#include "MatrixBase.h"

namespace gti320
{
	enum StorageType
	{
		ColumnStorage = 0,
		RowStorage = 1
	};

	// Déclaration avancée
	template <typename _Scalar, int _RowsAtCompile, int _ColsAtCompile, int _StorageType>
	class SubMatrix;

	/**
	 * Classe Matrix spécialisée pour un stockage par colonnes.
	 *
	 * Le cas d'un stockage par ligne fait l'objet d'une spécialisation de patron, le cas général
	 * (défini ici) considère donc uniquement le cas d'un stockage par colonnes.
	 */
	template <typename _Scalar = double, int _RowsAtCompile = Dynamic, int _ColsAtCompile = Dynamic, int _StorageType = ColumnStorage>
	class Matrix : public MatrixBase<_Scalar, _RowsAtCompile, _ColsAtCompile> {
	public:

		/**
		 * Constructeur par défaut
		 */
		Matrix() : MatrixBase<_Scalar, _RowsAtCompile, _ColsAtCompile>() { }

		/**
		 * Constructeur de copie
		 */
		Matrix(const Matrix& other) : MatrixBase<_Scalar, _RowsAtCompile, _ColsAtCompile>(other) { }

		/**
		 * Constructeur avec spécification du nombre de ligne et de colonnes
		 */
		explicit Matrix(int _rows, int _cols) : MatrixBase<_Scalar, _RowsAtCompile, _ColsAtCompile>(_rows, _cols) {}

		/**
		 * Destructeur
		 */
		~Matrix() { }

		/**
		 * Opérateur de copie à partir d'une sous-matrice.
		 *
		 * Exemple :
		 *    Matrix<...> A(...);
		 *    Matrix<...> B(...);
		 *    B = A.block(i,j,m,n);
		 */
		template<typename _OtherScalar, int _OtherRows, int _OtherCols, int _OtherStorage>
		Matrix& operator= (const SubMatrix<_OtherScalar, _OtherRows, _OtherCols, _OtherStorage>& submatrix)
		{
			// TODO copier les données de la sous-matrice.
			//   Note : si les dimensions ne cor`respondent pas, la matrice doit être redimensionnée.
			//   Vous pouvez présumer qu'il s'agit d'un stockage par colonnes.

			assert(submatrix.rows() > 0 && submatrix.cols() > 0);

			if (submatrix.cols() != this->cols() || submatrix.rows() != this->rows()) {
				this->resize(submatrix.rows(), submatrix.cols());
			}

			for (int i = 0; i < this->rows(); i++) {
				for (int j = 0; j < this->cols(); j++) {
					this->data()[(i - 1) * this->cols() + (j)] = submatrix.data()[(i)*this->cols() + (j)];
				}
			}
			return *this;
		}

		/**
		 * Accesseur à une entrée de la matrice (lecture seule)
		 */
		_Scalar operator()(int i, int j) const
		{
			assert(i > -1 && i < this->rows() && j > -1 && j < this->cols());
			_Scalar getValue = this->data()[(j)*this->rows() + (i)];
			return getValue;

		}

		/**
		* Accesseur à une entrée de la matrice (lecture ou écriture)
		*/
		_Scalar& operator()(int i, int j)
		{
			assert(i > -1 && i < this->rows() && j > -1 && j < this->cols());
			return this->m_storage.data()[(j)*this->rows() + (i)];
		}


		/**
		 * Crée une sous-matrice pour un block de taille (rows, cols) à partir de l'index (i,j).
		 */
		SubMatrix<_Scalar, _RowsAtCompile, _ColsAtCompile, _StorageType> block(int i, int j, int rows, int cols) const
		{
			return SubMatrix<_Scalar, _RowsAtCompile, _ColsAtCompile, _StorageType>(*this, i, j, rows, cols);
		}

		/**
		 * Calcule l'inverse de la matrice
		 */
		Matrix inverse() const
		{
			// Do nothing.
			return *this;
		}

		/**
		 * Retourne la transposée de la matrice
		 */
		template<int _OtherStorage = RowStorage>
		Matrix<_Scalar, _ColsAtCompile, _RowsAtCompile, _OtherStorage> transpose() const
		{
			// TODO calcule et retourne la transposée de la matrice.
			Matrix<_Scalar, _ColsAtCompile, _RowsAtCompile, _OtherStorage> transposedMatrix;

			transposedMatrix.resize(this->cols(), this->rows());

			for (int i = 0; i < this->rows(); i++) {
				for (int j = 0; j < this->cols(); j++) {
					transposedMatrix(j, i) = (*this)(i, j);
				}
			}

			return transposedMatrix;
		}

		/**
		 * Affecte l'identité à la matrice
		 */
		inline void setIdentity()
		{
			// TODO affecter la valeur 0.0 partour, sauf sur la diagonale principale où c'est 1.0..
			//      Votre implémentation devrait aussi fonctionner pour des matrices qui ne sont pas carrées.
			this->setZero();
			for (int i = 0; i < this->rows() && i < this->cols(); i++) {
				(*this)(i, i) = 1.0;
			}
		}

	};

	/**
	 * Classe Matrix spécialisée pour un stockage par lignes
	 */
	template <typename _Scalar, int _RowsAtCompile, int _ColsAtCompile>
	class Matrix< _Scalar, _RowsAtCompile, _ColsAtCompile, RowStorage> : public MatrixBase<_Scalar, _RowsAtCompile, _ColsAtCompile> {

	public:
		/**
		 * Constructeur par défaut
		 */
		Matrix() : MatrixBase<_Scalar, _RowsAtCompile, _ColsAtCompile>() { }

		/**
		 * Constructeur de copie
		 */
		Matrix(const Matrix& other) : MatrixBase<_Scalar, _RowsAtCompile, _ColsAtCompile>(other) { }

		/**
		 * Constructeur avec spécification du nombre de ligne et de colonnes
		 */
		explicit Matrix(int rows, int cols) : MatrixBase<_Scalar, _RowsAtCompile, _ColsAtCompile>(rows, cols) { }

		/**
		 * Destructeur
		 */
		~Matrix() { }

		/**
		 * Opérateur de copie à partir d'une sous-matrice.
		 *
		 * Exemple :
		 *    Matrix<...> A(...);
		 *    Matrix<...> B(...);
		 *    B = A.block(i,j,m,n);
		 */
		template<typename _OtherScalar, int _OtherRows, int _OtherCols, int _OtherStorage>
		Matrix& operator= (const SubMatrix<_OtherScalar, _OtherRows, _OtherCols, _OtherStorage>& submatrix)
		{
			// TODO copier les données de la sous-matrice.
			//   Note : si les dimensions ne correspondent pas, la matrice doit être redimensionnée.
			//   Vous pouvez présumer qu'il s'agit d'un stockage par lignes.

			assert(submatrix.rows() > 0 && submatrix.cols() > 0);

			if (submatrix.cols() != this->cols() || submatrix.rows() != this->rows()) {
				this->resize(submatrix.rows(), submatrix.cols());
			}

			for (int i = 0; i < this->rows(); i++) {
				for (int j = 0; j < this->cols(); j++) {
					(*this)(i, j) = submatrix(i, j);
				}
			}
			return *this;

		}

		/**
		 * Accesseur à une entrée de la matrice (lecture seule)
		 */
		_Scalar operator()(int i, int j) const
		{
			// TODO implementer
			assert(i > -1 && i < this->rows() && j > -1 && j < this->cols());
			_Scalar getValue = this->data()[(i)*this->cols() + (j)];
			return getValue;

		}

		/**
		 * Accesseur à une entrée de la matrice (lecture ou écriture)
		 */
		_Scalar& operator()(int i, int j)
		{
			// TODO implementer
			assert(i > -1 && i < this->rows() && j > -1 && j < this->cols());
			return (_Scalar)this->data()[(i)*this->cols() + (j)];
		}

		/**
		 * Crée une sous-matrice pour un block de taille (rows, cols) à partir de l'index (i,j).
		 */

		SubMatrix<_Scalar, _RowsAtCompile, _ColsAtCompile, RowStorage> block(int i, int j, int rows, int cols) const {
			return SubMatrix<_Scalar, _RowsAtCompile, _ColsAtCompile, RowStorage>(*this, i, j, rows, cols);
		}

		/**
		 * Calcule l'inverse de la matrice
		 */
		Matrix inverse() const
		{
			// Do nothing.
			return *this;
		}

		/**
		 * Retourne la transposée de la matrice
		 */
		template<int _OtherStorage = ColumnStorage>
		Matrix<_Scalar, _ColsAtCompile, _RowsAtCompile, _OtherStorage> transpose() const {

			// TODO calcule et retourne la transposée de la matrice.
			Matrix<_Scalar, _ColsAtCompile, _RowsAtCompile, _OtherStorage> transposedMatrix(this->cols(), this->rows());

			for (int i = 0; i < this->rows(); i++) {
				for (int j = 0; j < this->cols(); j++) {
					transposedMatrix(j, i) = (*this)(i, j);
				}
			}

			return transposedMatrix;
		}

		/**
		 * Affecte l'identité à la matrice
		 */
		inline void setIdentity()
		{
			// TODO affecter la valeur 0.0 partour, sauf sur la diagonale principale où c'est 1.0..
			//      Votre implémentation devrait aussi fonctionner pour des matrices qui ne sont pas carrées.
			this->setZero();
			for (int i = 0; i < this->rows() && i < this->cols(); i++) {
				(*this)(i, i) = 1.0;
			}
		}

	};

	/**
	 * Classe pour accéder à une sous-matrice.
	 *
	 * Un sous-matrice ne copie pas les données. Au lieu de cela, elle conserve une
	 * référence à la matrice originale.
	 */
	template <typename _Scalar, int _RowsAtCompile, int _ColsAtCompile, int _StorageType>
	class SubMatrix
	{
	private:
		// Référence à la matrice originale
		Matrix<_Scalar, _RowsAtCompile, _ColsAtCompile, _StorageType>& m_matrix;

		// Constructeur par défaut (privé)
		SubMatrix() {}

		// (i,j) est le coin supérieur gauche de la sous-matrice
		int m_i;        // Décalage en ligne 
		int m_j;        // Décalage en colonne

		// la sous-matrice est de dimension : m_rows x m_cols
		int m_rows;     // Hauteur de la sous-matrice (nombre de lignes)
		int m_cols;     // Largeur de la sous-matrice (nombre de colonnes)

	public:

		/**
		 * Constructeur à partir d'une référence en lecture seule à une matrice.
		 */
		SubMatrix(const Matrix<_Scalar, _RowsAtCompile, _ColsAtCompile, _StorageType>& _matrix, int _i, int _j, int _rows, int _cols) :
			m_matrix(const_cast<Matrix<_Scalar, _RowsAtCompile, _ColsAtCompile, _StorageType>&>(_matrix)),
			m_i(_i), m_j(_j), m_rows(_rows), m_cols(_cols)
		{
		}

		/**
		 * Constructeur à partir d'une référence en lecture et écriture à une matrice.
		 */
		explicit SubMatrix(Matrix<_Scalar, _RowsAtCompile, _ColsAtCompile, _StorageType>& _matrix, int _i, int _j, int _rows, int _cols) :
			m_matrix(_matrix),
			m_i(_i), m_j(_j), m_rows(_rows), m_cols(_cols)
		{
		}

		/**
		 * Constructeur de copie
		 */
		SubMatrix(const SubMatrix& other) :
			m_matrix(other.m_matrix),
			m_i(other.m_i), m_j(other.m_j), m_rows(other.m_rows), m_cols(other.m_cols)
		{
		}

		/**
		 * Destructeur
		 */
		~SubMatrix() { }

		/**
		 * Opérateur de copie (à partir d'une matrice)
		 *
		 * Copies toutes les entrées de la matrice dans la sous-matrice.
		 *
		 * Note : la taille de la matrice doit correspondre à la taille de la
		 * sous-matrice.
		 */
		template<typename _OtherScalar, int _OtherRows, int _OtherCols, int _OtherStorage>
		SubMatrix& operator= (const Matrix<_OtherScalar, _OtherRows, _OtherCols, _OtherStorage>& matrix)
		{

			// TODO Copie les valeurs de la matrice dans la sous-matrice.
			//      Note les dimensions de la matrice doivent correspondre à celle de
			//      la sous-matrice.
			assert(matrix.cols() == this->cols() && matrix.rows() == this->rows());
			for (int i = 0; i < this->rows(); i++) {
				for (int j = 0; j < this->cols(); j++) {
					this->m_matrix(i + m_i, j + m_j) = matrix(i, j);
				}
			}
			return *this;

		}

		/**
		 * Accesseur aux entrées de la sous-matrice (lecture seule)
		 *
		 * Note : il faut s'assurer que les indices respectent la taille de la
		 * sous-matrice
		 */
		_Scalar operator()(int i, int j) const
		{
			assert(i > -1 && i < this->rows() && j > -1 && j < this->cols());
			_Scalar returnValue = m_matrix(m_i + i, m_j + j);
			return returnValue;
		}

		/**
		 * Accesseur aux entrées de la sous-matrice (lecture et écriture)
		 *
		 * Note : il faut s'assurer que les indices respectent la taille de la
		 * sous-matrice
		 */
		_Scalar& operator()(int i, int j)
		{
			assert(i >= 0 && i < this->rows() && j >= 0 && j < this->cols());
			return m_matrix(m_i + i, m_j + j);
		}

		/**
		 * Retourne la transposée de la sous-matrice sous la forme d'une matrice.
		 */
		template<typename _OtherScalar, int _OtherRows, int _OtherCols, int _OtherStorage>
		Matrix<_OtherScalar, _OtherRows, _OtherCols, _OtherStorage> transpose() const
		{
			// TODO implémenter
			Matrix<_OtherScalar, _OtherRows, _OtherCols, _OtherStorage> transposedMatrix(this->rows(), this->cols());

			for (int i = 0; i < this->rows(); i++) {
				for (int j = 0; j < this->cols(); j++) {
					transposedMatrix(j, i) = (*this)(i, j);
				}
			}

			return transposedMatrix;
		}

		inline int rows() const { return m_rows; }
		inline int cols() const { return m_cols; }

	};

}
