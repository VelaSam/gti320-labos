#include "ParticleSystem.h"


#define GRAVITY_A (-1*9.81)

using namespace gti320;

/**
 * Calcule des forces qui affectent chacune des particules.
 *
 * Étant donné une particule p, la force est stockée dans le vecteur p.f
 * Les forces prisent en compte sont : la gravité et la force des ressorts.
 */
void ParticleSystem::computeForces()
{
    // TODO 
    //
    // Calcul de la force gravitationnelle sur chacune des particules


    for (Particle& p : m_particles)
    {
        p.f(1) = (float)(p.m * GRAVITY_A);
    }

    // TODO
    //
    // Pour chaque ressort, ajouter la force exercée à chacune des extrémités sur
    // les particules appropriées. Pour un ressort s, les deux particules
    // auxquelles le ressort est attaché sont m_particles[s.index0] et
    // m_particles[s.index1]. On rappelle que les deux forces sont de même
    // magnitude mais dans des directions opposées.
    for (const Spring& s : m_springs)
    {
        auto particule0 = this->m_particles[s.index0];
        auto particule1 = this->m_particles[s.index1];
        auto variationPosition = particule1.x - particule0.x;

        auto alpha0 = s.k * (1 - s.l0/variationPosition.norm());
        auto alpha1 = -1* s.k * (1 - s.l0/variationPosition.norm());

        auto f0 = alpha0*variationPosition;
        auto f1 = alpha1*variationPosition;

        particule0.f = f0 + particule0.f;
        particule1.f = f1 + particule1.f;
    }
}

/**
 * Assemble les données du système dans les vecteurs trois vecteurs d'état _pos,
 * _vel et _force.
 */
void ParticleSystem::pack(
    Vector<float, Dynamic>& _pos,
    Vector<float, Dynamic>& _vel,
    Vector<float, Dynamic>& _force)
{
    /* TODO: Copier les données des particules dans les vecteurs. Attention, si on a
     * changé de modèle, il est possible que les vecteurs n'aient pas la bonne
     taille. Rappel : la taille de ces vecteurs doit être 2 fois le nombre de
     particules. */

    if(this->getParticles().size() != 2*_pos.size()){
        _pos.resize((int)this->m_particles.size()*2);
    }
    if( this->getParticles().size() != 2*_vel.size()){
        _vel.resize((int)this->m_particles.size()*2);
    }
    if(this->getParticles().size() != 2*_force.size()){
        _force.resize((int)this->m_particles.size()*2);
    }

    int index = 0;
    for(auto & m_particle : this->m_particles) {
        _pos(index) = m_particle.x(0);
        _pos(index+1) = m_particle.x(1);

        _vel(index) = m_particle.v(0);
        _vel(index+1) = m_particle.v(1);

        _force(index) = m_particle.f(0);
        _force(index+1) = m_particle.f(1);
        index += 2;
    }
}


void printParticleSystem(const ParticleSystem& particleSystem){

    std::cout << "Particle System: " << std::endl;
    int i = 0;
    for(const Particle& particle : particleSystem.getParticles()){
        std::cout << "Particle number: " << i << ", " << "mass: " << particle.m << " " << std::endl;
        std::cout << "posit = [" << particle.x.data()[0] << ", " << particle.x.data()[1] << "]" << std::endl;
        std::cout << "veloc = [" << particle.v.data()[0] << ", " << particle.v.data()[1] << "]" << std::endl;
        std::cout << "force = [" << particle.f.data()[0] << ", " << particle.f.data()[1] << "]" << std::endl;
        i++;
    }
    std::cout << std::endl;
}

void printVector(const Vector<float, Dynamic> vec, std::string name){
    std::cout << name << std::endl;
    for (int i = 0; i < vec.size()/2; i+=2) {
        std::cout << ": " << vec(i) << " " << vec(i+1) << " ";
        std::cout << std::endl;

    }
    std::cout << std::endl;
}
/**
 * Copie les données des vecteurs d'états dans les particules du système.
 */
void ParticleSystem::unpack(
        const Vector<float, Dynamic>& _pos,
        const Vector<float, Dynamic>& _vel)
{
    // TODO
    //
    // Mise à jour des propriétés de chacune des particules à partir des valeurs
    // contenues dans le vecteur d'état.
    //

    // a re-verifier
    this->m_particles.resize(_pos.size()/2);

    int index = 0;
    for(int i = 0 ; i < this->m_particles.size(); i++) {
        this->m_particles.at(i).x(0) = _pos(index);
        this->m_particles.at(i).x(1) = _pos(index+1);

        this->m_particles.at(i).v(0) = _pos(index);
        this->m_particles.at(i).v(1) = _pos(index+1);
        index+=2;
    }
}

/**
 * Construction de la matrice de masses.
 */
void ParticleSystem::buildMassMatrix(Matrix<float, Dynamic, Dynamic>& M)
{
    const int numParticles = m_particles.size();
    const int dim = 2 * numParticles;
    M.resize(dim, dim);
    M.setZero();

    // TODO 
    // Inscrire la masse de chacune des particules dans la matrice de masses M
    int index = 0;
    for (int i = 0; i < m_particles.size(); i++)
    {
        M(index, index) = this->m_particles.at(i).m;
        M(index+1, index+1) = this->m_particles.at(i).m;

        index+=2;
    }
}


/**
 * Construction de la matrice de rigidité.
 */
void ParticleSystem::buildDfDx(Matrix<float, Dynamic, Dynamic>& dfdx)
{
    const int numParticles = m_particles.size();
    const int numSprings = m_springs.size();
    const int dim = 2 * numParticles;
    dfdx.resize(dim, dim);
    dfdx.setZero();

    // Pour chaque ressort...
    for (const Spring& spring : m_springs)
    {
        // TODO
        //
        // Calculer le coefficients alpha et le produit dyadique tel que décrit au cours.
        // Utiliser les indices spring.index0 et spring.index1 pour calculer les coordonnées des endroits affectés.
        //
        // Astuce: créer une matrice de taille fixe 2 par 2 puis utiliser la classe SubMatrix pour accumuler 
        // les modifications sur la diagonale (2 endroits) et pour mettre à jour les blocs non diagonale (2 endroits).


    }
}
