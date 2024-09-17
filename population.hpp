#ifndef POPULATION
#define POPULATION
#include "animal.hpp"
#include "ensemble.hpp"
#include <vector>
class Population{
    public:
        Population();
        Animal &get(int id); //permet de modifier un animal en particulier
        Ensemble getIds() const;
        int reserve(); //return id
        int set(Animal a); //return id
        void supprime(int id);
        int recensement(Espece e) const;
    private:
        vector<Animal> _pop;

};
#endif