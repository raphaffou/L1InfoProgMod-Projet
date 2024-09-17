#include "population.hpp"
#include "doctest.h"

Population::Population(){
    _pop = {{}};
}

Animal &Population::get(int id){
    if(id > _pop.size() || _pop[id].getId() == -1){
        throw std::invalid_argument("Aucun animal ayant cet id trouvé");
    }
    return _pop[id];
}

Ensemble Population::getIds() const{
    Ensemble E;
    for(int i=0; i<_pop.size();i++){
        int id = _pop[i].getId();
        if(id != -1){
            E.ajoute(id);
        }
    }
    return E;
}

int Population::reserve(){
    for(int i = 0; i<_pop.size(); i++){
        if(_pop[i].getId() == -1){
            return i;
        }    
    } //si il y a pas de -1
    _pop.push_back(Animal(-1, Espece::Lapin, Coord(0, 0)));
    return _pop.size()-1;
}

int Population::set(Animal a){
    int id = reserve();
    a.setId(id);
    _pop[id] = a;
    return id;
}

void Population::supprime(int id){
    //_pop[id].setId(-1); dans mes reves
    _pop[id] = Animal(-1, Espece::Lapin, Coord(0, 0));
}

int Population::recensement(Espece e) const{
    int i = 0;
    for(auto a : _pop){
        if(a.getEspece() == e && a.getId() != -1){
            i++;
        }
    }
    return i;
}

TEST_CASE("Population constructeur"){
    Population p;
    CHECK(p.getIds().estVide());
}

TEST_CASE("get"){
    Population p;
    int id = p.set(Animal(1, Espece::Lapin, Coord(0, 0)));
    CHECK(p.get(id).getId() == id);
    CHECK_THROWS(p.get(-1));
}

TEST_CASE("getIds"){
    Population p;
    CHECK(p.getIds().estVide());
    int id = p.set(Animal(1, Espece::Lapin, Coord(0, 0)));
    CHECK_FALSE(p.getIds().estVide());
    CHECK(p.getIds().in(id));
}

TEST_CASE("reserve"){
    Population p;
    CHECK(p.reserve() == 0);
    p.set(Animal(1, Espece::Lapin, Coord(0, 0)));
    CHECK(p.reserve() == 1);
}

TEST_CASE("set"){
    Population p;
    int id = p.set(Animal(1, Espece::Lapin, Coord(0, 0)));
    CHECK(p.get(id).getId() == id);
}

TEST_CASE("supprime"){
    Population p;
    int id = p.set(Animal(1, Espece::Lapin, Coord(0, 0)));
    p.supprime(id);
    CHECK_THROWS(p.get(id).getId());
}

TEST_CASE("recensement"){
    Population p;
    CHECK(p.recensement(Espece::Lapin) == 0);
    p.set(Animal(1, Espece::Lapin, Coord(0, 0)));
    CHECK(p.recensement(Espece::Lapin) == 1);
    p.set(Animal(2, Espece::Lapin, Coord(0, 0)));
    CHECK(p.recensement(Espece::Lapin) == 2);
    p.set(Animal(3, Espece::Lapin, Coord(0, 0)));
    CHECK(p.recensement(Espece::Lapin) == 3);
    p.set(Animal(4, Espece::Renard, Coord(0, 0)));
    CHECK(p.recensement(Espece::Lapin) == 3);
    CHECK(p.recensement(Espece::Renard) == 1);
}