#ifndef ANIMAL
#define ANIMAL


#include <iostream>
#include <string>
#include "coord.hpp"
int const FoodInit = 5;
int const EspVie = 10;

enum class Espece {Lapin, Renard};
class Animal{
    private:
        Espece _espece;
        Coord _coord;
        int _id;
        int _food; 
        int _age; 
        int _ageMort;
        bool _sexe;
    public:
        int getSexe();
        int getId() const;
        int getFood() const;
        Coord getCoord() const;
        void setId(int id) { _id = id;}
        void setCoord(Coord c);
        Espece getEspece() const;
        int getAge() const;
        int getAgeMort() const;
        string toString() const;
        bool meurt();
        void mange();
        void jeune();
        void anniversaire();
        bool seReproduit(Ensemble coordVoisins, bool isOppositeRenard, bool isOppositeLapin);
        Animal(int id, Espece espece, Coord coord) : _espece{espece}, _coord{coord}, _id{id} {_food = FoodInit; _age = 0; _ageMort = (EspVie + 3*((rand()%3)-1)); _sexe = rand()%2;};
};
#endif // ANIMAL