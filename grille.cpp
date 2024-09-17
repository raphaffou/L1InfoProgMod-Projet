#include "grille.hpp"
#include "doctest.h"


Grille::Grille(){
    _data = vector<vector<int>>(TAILLEGRILLE, vector<int>(TAILLEGRILLE, -1));
}

bool Grille::caseVide(Coord coord) const{
    return _data[coord.getY()][coord.getX()] < 0;
}

int Grille::getCase(Coord coord) const{
    return _data[coord.getY()][coord.getX()];
}

void Grille::videCase(Coord coord){
    _data[coord.getY()][coord.getX()] = -1;
}

void Grille::setCase(Animal a, Coord coord){
    int id = a.getId();
    _data[coord.getY()][coord.getX()] = id;
}

TEST_CASE("Grille Constructeur"){
    Grille g;
    for(int i = 0; i < TAILLEGRILLE;i++){
        for(int j = 0; j < TAILLEGRILLE;j++){
            CHECK(g.getCase(Coord(i,j)) == -1);
        }
    }
}

TEST_CASE("caseVide"){
    Grille g;
    CHECK(g.caseVide(Coord(0,0)));
    g.setCase(Animal(1, Espece::Renard, Coord(0,0)), Coord(0,0));
    CHECK_FALSE(g.caseVide(Coord(0,0)));
}

TEST_CASE("getCase"){
    Grille g;
    CHECK(g.getCase(Coord(0,0)) == -1);
    g.setCase(Animal(1, Espece::Renard, Coord(0,0)), Coord(0,0));
    CHECK(g.getCase(Coord(0,0)) == 1);
}

TEST_CASE("videCase"){
    Grille g;
    g.setCase(Animal(1, Espece::Renard, Coord(0,0)), Coord(0,0));
    g.videCase(Coord(0,0));
    CHECK(g.getCase(Coord(0,0)) == -1);
}

TEST_CASE("setCase"){
    Grille g;
    g.setCase(Animal(1, Espece::Renard, Coord(0,0)), Coord(0,0));
    CHECK(g.getCase(Coord(0,0)) == 1);
}

