#include <math.h>
#include "coord.hpp"
#include <string>
#include "doctest.h"
#include <iostream>

Coord::Coord(int x1, int y1){
    //erreurs coordonnées
    if(x1 < 0 || x1 >= TAILLEGRILLE)
        throw std::out_of_range("x = " + std::to_string(x1) + " | x doit être compris entre 0 et " + std::to_string(TAILLEGRILLE - 1));
    if(y1 < 0 || y1 >= TAILLEGRILLE)
        throw std::out_of_range("y = " + std::to_string(y1) + " | y doit être compris entre 0 et " + std::to_string(TAILLEGRILLE - 1));
    x = x1;
    y = y1;
}

Coord::Coord(int n){
    if(n >= pow(TAILLEGRILLE, 2))
    throw std::out_of_range("n = " + std::to_string(n) + " | n doit être compris entre 0 et " + std::to_string(int(pow(TAILLEGRILLE, 2) - 1)));
    x = n % TAILLEGRILLE;
    y = n / TAILLEGRILLE;

}

//Les getters
int Coord::getX() const{
    return x;
}
int Coord::getY() const{
    return y;
}


std::ostream& Coord::affiche(std::ostream& out){
    return out << "(" << x << ", " << y << ")";
}

std::ostream& operator<<(std::ostream& out, Coord &c){
    return c.affiche(out);
}

bool Coord::operator==(const Coord &c) const{
    return (x == c.getX() && y == c.getY());
}

bool Coord::operator!=(const Coord &c) const{
    return !(*this == c);
}



int Coord::toInt() const{
    return y * TAILLEGRILLE + x;
}

Ensemble Coord::voisines(){
    Ensemble ens;

    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            if(i == 0 && j == 0)
                continue;
            try{
                ens.ajoute(Coord(x + i, y + j).toInt());
            }
            catch(std::out_of_range &e){
                //cout << e.what() << endl;
            }
        }
    }
    return ens;
}


TEST_CASE("Constructeur"){
    Coord c(0,0);
    CHECK(c.getX() == 0);
    CHECK(c.getY() == 0);
    CHECK_THROWS_AS(Coord(-1,0), std::out_of_range);
    CHECK_THROWS_AS(Coord(0,-1), std::out_of_range);
    CHECK_THROWS_AS(Coord(TAILLEGRILLE,0), std::out_of_range);
    CHECK_THROWS_AS(Coord(0,TAILLEGRILLE), std::out_of_range);

    Coord c2{TAILLEGRILLE};
    CHECK(c2.getX() == 0);
    CHECK(c2.getY() == 1);

    Coord c3{2};
    CHECK(c3.getX() == 2);
    CHECK(c3.getY() == 0);

    Coord c4{3};
    CHECK(c4.getX() == 3);
    CHECK(c4.getY() == 0);
    
    CHECK_THROWS_AS(Coord(pow(TAILLEGRILLE,2) + 1), std::out_of_range);
}



TEST_CASE("Coordonnées : Voisines"){  
    Coord c(TAILLEGRILLE - 1,TAILLEGRILLE - 1);
    Ensemble ens = c.voisines();
    CHECK(ens.cardinal() == 3);
    CHECK(ens.in(Coord(TAILLEGRILLE - 2,TAILLEGRILLE - 2).toInt()));
    CHECK(ens.in(Coord(TAILLEGRILLE - 1,TAILLEGRILLE - 2).toInt()));
    CHECK(ens.in(Coord(TAILLEGRILLE - 2,TAILLEGRILLE - 1).toInt()));
    // while(!ens.estVide()){
    //     cout << Coord(ens.tire()) << endl;
    // }
    // std::cout << ens << std::endl;
    CHECK(true);
    
   
}