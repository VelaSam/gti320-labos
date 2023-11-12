#include "GraphColoring.h"
#include "ParticleSystem.h"

using namespace gti320;

/**
 * Attribue une couleur � chaque particule de sorte que deux particules reli�es par un ressort aient
 * des couleurs diff�rentes.
 */
void GraphColoring::color(ParticleSystem& particleSystem)
{
    // La palette de couleurs
    ColorList C;
    std::vector<Particle>& particles = particleSystem.getParticles();

    // Initialiser toutes les particules avec color = -1 
    for (Particle& p : particles)
    {
        p.color = -1;
    }

    // TODO Calculer les couleurs de toutes les particules du syst�me. 
    //      Boucler sur chaque particule et appeler la fonction findColor.

    // TODO Construire les partitions qui correspond � chaque couleur. 
    //     Les partitions sont repr�sent�es par un tableau d'indices de particules, un pour chaque couleur. 
    //     Stocker les partitions dans m_partitions.
    for(Particle &p : particles){
        p.color = findColor(p, particles, particleSystem.getSprings(), C);
    }

    m_partitions.clear();
    for (const Particle& p : particles)
    {
        if (p.color >= static_cast<int>(m_partitions.size()))
        {
            m_partitions.resize(p.color + 1);
        }
    }
}

/**
 * Attribue une couleur � la particule p, selon l'algorithme glouton de coloration de graphe.
 */
int GraphColoring::findColor(const Particle& p, const std::vector<Particle>& particles, const std::vector<Spring>& springs, ColorList& C) const
{
    // TODO Trouver la premi�re couleur de la palette C qui n'est pas attribu�e � une particule voisine. 
    //      Si une couleur est introuvable, ajouter une nouvelle couleur � la palette et retournez la couleur. 
    //      Utiliser la fonction findNeighbors pour assembler une liste de particules qui sont directement connect�es � la particule p par un ressort (les voisines).
    int n = C.size();
    NeighborList neighbors = findNeighbors(p, particles, springs);

    std::vector<int> count(n, 0);

    for (const Particle* neighbor : neighbors)
    {
        if (neighbor->color != -1)
        {
            count[neighbor->color]++;
        }
    }

    for (int c = 0; c < n; ++c)
    {
        if (count[c] == 0)
        {
            return c;
        }
    }

    C.push_back(n);
    return n;
}

/**
 * Retourne la liste des particules voisines de p.
 *
 * Deux particules sont dites `voisines` si elle sont reli�es par un ressort.
 */
NeighborList GraphColoring::findNeighbors(const Particle& p, const std::vector<Particle>& particles, const std::vector<Spring>& springs) const
{
    NeighborList N;

    for (const Spring& s : springs)
    {
        if (&particles[s.index0] == &p)
        {
            N.push_back(&particles[s.index1]);
        }
        else if (&particles[s.index1] == &p)
        {
            N.push_back(&particles[s.index0]);
        }
    }

    return N;
}
