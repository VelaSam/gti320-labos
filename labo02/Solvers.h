#pragma once

/**
 * @file Solvers.hpp
 *
 * @brief Implémentation de plusieurs algorihtmes de solveurs pour un système
 *        d'équations linéaires
 *
 * Nom: Samuel Velasco
 * Code permanent : VELS66050107
 * Email : samuel.velasco.1@ens.etsmtl.ca
 *
 */

#include "Math3D.h"
#include "ParticleSystem.h"
#include "GraphColoring.h"

namespace gti320
{


    // Identification des solveurs
    enum eSolverType { None, GaussSeidel, ColorGaussSeidel, Cholesky };

    // Paramètres de convergences pour les algorithmes itératifs
    static const float eps = 1e-4f;
    static const float tau = 1e-5f;

    /**
     * Résout Ax = b avec la méthode Gauss-Seidel
     */
    static void gaussSeidel(const Matrix<float, Dynamic, Dynamic>& A,
        const Vector<float, Dynamic>& b,
        Vector<float, Dynamic>& x, int k_max)
    {
        // TODO 
        //
        // Implémenter la méthode de Gauss-Seidel
        Vector<float, Dynamic> r = A*x - b;

        bool converged = false;
        int k = 0;

        while(!converged) {
            auto x_prec = x;
            for (int i = 0; i < x.size(); ++i) {
                x(i) = b(i);
                for (int j = 0; j < i; ++j) {
                    x(i) -=  A(i, j) * x(j);
                }
                for (int j = i + 1; j < x.size(); ++j) {
                    x(i) -= A(i, j) * x(j);
                }
                x(i) /= A(i, i);
            }
            r = A * x - b;
            k++;
            if(k == k_max || (x-x_prec).norm()/x.norm() < tau || r.norm()/b.norm() < eps){
                converged = true;
            }
        }

    }

    /**
     * Résout Ax = b avec la méthode Gauss-Seidel parallélisée (coloration de graphe)
     */\
    static void gaussSeidelColor(const Matrix<float, Dynamic, Dynamic>& A, const Vector<float, Dynamic>& b, Vector<float, Dynamic>& x, const Partitions& P, const int maxIter)
    {
        for (int c = 0; c < P.size(); ++c) {
            #pragma omp parallel for
            for (int i = 0; i < P[c].size(); ++i) {

                x(i) = b(i);
                for (int j = 0; j < i; ++j) {
                    x(i) = x(i) - A(i, j) * x(j);
                }
                for (int j = i + 1; j < x.rows(); ++j) {
                    x(i) = x(i) - A(i, j) * x(j);
                }
                x(i) = x(i) / A(i, i);
            }

        }
    }


    /**
     * Résout Ax = b avec la méthode de Cholesky
     */
    static void cholesky(const Matrix<float, Dynamic, Dynamic>& A,
        const Vector<float, Dynamic>& b,
        Vector<float, Dynamic>& x)
    {
        // TODO 
        //
        // Calculer la matrice L de la factorisation de Cholesky
        Matrix<float, Dynamic, Dynamic> L(A.rows(), A.cols());
        for (int j = 0; j < A.rows(); ++j) {
            for (int i = 0; i < A.rows(); ++i) {
                float s = 0;
                for (int k = 0; k < j-1; ++k) {
                    s += L(i,k) * L(j,k);
                }
                if(i==j){
                    L(i,j) = sqrt(A(i,i) - s);
                } else {
                    L(i,j) = (A(i,j) - s)/L(j,j);
                }
            }
        }


        // TODO
        //
        // Résoudre Ly = b
        Vector<float, Dynamic> y(b.rows());
        for (int i = 0; i < A.rows(); ++i) {
            y(i) = b(i);
            for (int j = 0; j < i - 1; ++j) {
                y(i) = y(i) - L(i,j)*y(j);
            }
            y(i) = y(i)/L(i,i);
        }


        // TODO
        //
        // Résoudre L^t x = y
        // 
        // Remarque : ne pas caculer la transposer de L, c'est inutilement
        // coûteux.
        for (int i = A.rows()-1; i >= 0 ; i--) {
            x(i) = y(i);
            for (int j = i+1; j < A.rows(); ++j) {
                x(i) = x(i) - L(j,i)*x(j);
            }
            x(i) = x(i)/L(i,i);
        }


    }


}


