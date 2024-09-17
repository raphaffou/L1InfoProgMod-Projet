#include "animal.hpp"
#include "doctest.h"
#include "param.hpp"

int Animal::getId() const{
    return _id;
}

int Animal::getFood() const{
    return _food;
}

int Animal::getAge() const{
    return _age;
}

int Animal::getAgeMort() const{
    return _ageMort;
}

Coord Animal::getCoord() const{
    return _coord;
}
void Animal::setCoord(Coord c){
    //invariants ???
    _coord = c;
}
Espece Animal::getEspece() const{
    return _espece;
}
string Animal::toString() const{
    if(_id < 0) return "0";
    switch (_espece){
        case Espece::Lapin : return "\033[94mL\033[0m";
        case Espece::Renard : return "\033[91mR\033[0m";
        default : return "0";
    }
}
bool Animal::meurt(){
    //les lapins ne peuvent ni manger, ni perdre de nouriture, donc ça ne concerne que les renards
    return _food <= 0 or _age > _ageMort;
}

bool Animal::seReproduit(Ensemble coordVoisins, bool isOppositeRenard, bool isOppositeLapin){
    if(_id < 0) throw runtime_error("animal non initialisé");
    if(_espece == Espece::Renard){
        if(_food>=FoodReprod && !coordVoisins.estVide() &&isOppositeRenard)
            return ((rand()%100) < (ProbBirthRenard*100));
        return false;
    }else{
        if(coordVoisins.cardinal() >= MinFreeBirthLapin && isOppositeLapin)
            return ((rand()%100) < (ProbBirthLapin*100));
        return false;
    }
}
void Animal::mange(){
    if(_food<MaxFood && _espece == Espece::Renard){
        if( _food + FoodLapin > MaxFood ){ //si ça deborde
            _food=MaxFood;
        }else{
            _food+= FoodLapin;
        }
    }
}
void Animal::jeune(){
    if(_espece == Espece::Renard)
        _food--;
}
void Animal::anniversaire(){
    _age++;
}
int Animal::getSexe(){
    return _sexe;
}

TEST_CASE("getID"){
    Animal a(1, Espece::Renard, Coord(0,0));
    CHECK(a.getId() == 1);
}

TEST_CASE("getCoord"){
    Animal a(1, Espece::Renard, Coord(0,0));
    CHECK(a.getCoord() == Coord(0,0));
}

TEST_CASE("setCoord"){
    Animal a(1, Espece::Renard, Coord(0,0));
    a.setCoord(Coord(1,1));
    CHECK(a.getCoord() == Coord(1,1));
}

TEST_CASE("getEspece"){
    Animal a(1, Espece::Renard, Coord(0,0));
    CHECK(a.getEspece() == Espece::Renard);
}

TEST_CASE("toString"){
    Animal a(1, Espece::Renard, Coord(0,0));
    CHECK(a.toString() == "\033[91mR\033[0m");
    a = {1, Espece::Lapin, Coord(0,0)};
    CHECK(a.toString() == "\033[94mL\033[0m");
    a = {-1, Espece::Lapin, Coord(0,0)};
    CHECK(a.toString() == "0");
}

TEST_CASE("meurt"){
    Animal a(1, Espece::Renard, Coord(0,0));
    CHECK(a.meurt() == false);
    for(int i = 0; i < 5; i++) a.jeune();
    CHECK(a.meurt() == true);

    a = {1, Espece::Lapin, Coord(0,0)};
    CHECK(a.meurt() == false);
}

TEST_CASE("seReproduit"){
    Animal a(-1, Espece::Renard, Coord(0,0));
    CHECK_THROWS_AS(a.seReproduit(Ensemble(), false, false), runtime_error);
}

TEST_CASE("mange"){
    Animal a(1, Espece::Renard, Coord(0,0));
    CHECK(a.getFood() == FoodInit);
    a.mange();
    CHECK(a.getFood() == FoodInit+FoodLapin);
    a.jeune();
    a.mange();
    CHECK(a.getFood() == MaxFood); 
}

TEST_CASE("jeune"){
    Animal a(1, Espece::Renard, Coord(0,0));
    CHECK(a.getFood() == FoodInit);
    a.jeune();
    CHECK(a.getFood() == FoodInit-1);
}