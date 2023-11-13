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
        for (int c = 0; c < 4; ++c) {

            #pragma omp parallel for
            for (int k = 0; k < P[c].size(); ++k) {
                int i = P[c][k];

                float sum = b(i);

                for (int j = 0; j < i; ++j) {
                    sum -= A(i, j) * x(j);
                }

                for (int j = i + 1; j < A.cols(); ++j) {
                    sum -= A(i, j) * x(j);
                }

                x(i) = sum / A(i, i);
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



        // TODO
        //
        // Résoudre Ly = b



        // TODO
        //
        // Résoudre L^t x = y
        // 
        // Remarque : ne pas caculer la transposer de L, c'est inutilement
        // coûteux.



    }


}


