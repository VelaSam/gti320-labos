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
    }

    /**
     * Résout Ax = b avec la méthode Gauss-Seidel parallélisée (coloration de graphe)
     */
    static void gaussSeidelColor(const Matrix<float, Dynamic, Dynamic>& A, const Vector<float, Dynamic>& b, Vector<float, Dynamic>& x, const Partitions& P, const int maxIter)
    {
        // TODO 
        //
        // Implémenter la méthode de Gauss-Seidel avec coloration de graphe.
        // Les partitions avec l'index de chaque particule sont stockées dans la table des tables, P.

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
