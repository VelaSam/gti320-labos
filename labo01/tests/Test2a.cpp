/**
 * @file Tests2a.cpp
 *
 * @brief Tests unitaires de la partie 1b
 *
 * Nom: Samuel Velasco
 * Code permanent : VELS66050107
 * Email : samuel.velasco.1@ens.etsmtl.ca
 *
 */

#include "Matrix.h"
#include "Vector.h"
#include "../../labo02/ParticleSystem.h"
#include "../../labo02/ParticleSystem.cpp"

#include <gtest/gtest.h>
#include <chrono>

using namespace gti320;


namespace Lab2Tests {

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

    ParticleSystem &setUpTestSystem() {

        Vector2f x1(1, 11);
        Vector2f v1(2, 22);
        Vector2f f1(3, 33);

        Vector2f x2(4, 44);
        Vector2f v2(5, 55);
        Vector2f f2(6, 66);

        Vector<float, Dynamic> pos(10);
        Vector<float, Dynamic> vel(10);
        Vector<float, Dynamic> force(10);

        Particle particle(x1, v1, f1, 5);
        Particle particle2(x2, v2, f2, 6);
        Particle particle3; // default ctor x=[0,0] y=[0,0] f=[0,0] m = 1.0;

        auto *particleSystem = new ParticleSystem(); //default ctor (and only ctor)

        //add three particles to the system
        particleSystem->addParticle(particle);
        particleSystem->addParticle(particle2);
        particleSystem->addParticle(particle3);

        return *particleSystem;
    }

    TEST(TestLabo2a, PackMethod){

        ParticleSystem particleSystem = setUpTestSystem();
        printParticleSystem(particleSystem);

        ASSERT_EQ(particleSystem.getParticles().size(), 3);

        Vector<float, Dynamic> pos(10);
        for(int i = 0; i < pos.size(); i++){
            pos(i) = 69.0;
        }
        Vector<float, Dynamic> vel(20);
        for(int i = 0; i < vel.size(); i++){
            vel(i) = 420.0;
        }
        Vector<float, Dynamic> force(30);
        for(int i = 0; i < force.size(); i++){
            force(i) = 666.0;
        }

        ASSERT_EQ(pos.size(), 10);
        ASSERT_EQ(vel.size(), 20);
        ASSERT_EQ(force.size(), 30);

        particleSystem.pack(pos, vel, force);

        //assert size
        ASSERT_EQ(pos.size(), 6);
        ASSERT_EQ(vel.size(), 6);
        ASSERT_EQ(force.size(), 6);

        ASSERT_EQ(pos(0), 1);
        ASSERT_EQ(pos(1), 11);
        ASSERT_EQ(pos(2), 4);
        ASSERT_EQ(pos(3), 44);
        ASSERT_EQ(pos(4), 0);
        ASSERT_EQ(pos(5), 0);

        ASSERT_EQ(vel(0), 2);
        ASSERT_EQ(vel(1), 22);
        ASSERT_EQ(vel(2), 5);
        ASSERT_EQ(vel(3), 55);
        ASSERT_EQ(vel(4), 0);
        ASSERT_EQ(vel(5), 0);

        ASSERT_EQ(force(0), 3);
        ASSERT_EQ(force(1), 33);
        ASSERT_EQ(force(2), 6);
        ASSERT_EQ(force(3), 66);
        ASSERT_EQ(force(4), 0);
        ASSERT_EQ(force(5), 0);
    }

    TEST(TestLabo2a, UnpackMethod){

        ParticleSystem particleSystem = setUpTestSystem();
        printParticleSystem(particleSystem);

        ASSERT_EQ(particleSystem.getParticles().size(), 3);

        Vector<float, Dynamic> pos(10);
        for(int i = 0; i < pos.size(); i++){
            pos(i) = 69.0;
        }
        Vector<float, Dynamic> vel(20);
        for(int i = 0; i < vel.size(); i++){
            vel(i) = 420.0;
        }
        Vector<float, Dynamic> force(30);
        for(int i = 0; i < force.size(); i++){
            force(i) = 666.0;
        }

        ASSERT_EQ(pos.size(), 10);
        ASSERT_EQ(vel.size(), 20);
        ASSERT_EQ(force.size(), 30);

        particleSystem.pack(pos, vel, force);

        //assert size
        ASSERT_EQ(pos.size(), 6);
        ASSERT_EQ(vel.size(), 6);
        ASSERT_EQ(force.size(), 6);

        ASSERT_EQ(pos(0), 1);
        ASSERT_EQ(pos(1), 11);
        ASSERT_EQ(pos(2), 4);
        ASSERT_EQ(pos(3), 44);
        ASSERT_EQ(pos(4), 0);
        ASSERT_EQ(pos(5), 0);

        ASSERT_EQ(vel(0), 2);
        ASSERT_EQ(vel(1), 22);
        ASSERT_EQ(vel(2), 5);
        ASSERT_EQ(vel(3), 55);
        ASSERT_EQ(vel(4), 0);
        ASSERT_EQ(vel(5), 0);

        ASSERT_EQ(force(0), 3);
        ASSERT_EQ(force(1), 33);
        ASSERT_EQ(force(2), 6);
        ASSERT_EQ(force(3), 66);
        ASSERT_EQ(force(4), 0);
        ASSERT_EQ(force(5), 0);
    }
}


