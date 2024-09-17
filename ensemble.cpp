#include "ensemble.hpp"
#include <array>
#include <iostream>
#include "doctest.h"

using namespace std;
ostream& Ensemble::affiche(ostream& out) const{
    out<<'[';
    for(int i = 0; i < card;i++){
        out<<tab[i]<<",";
    }
    out<<']';
    return out;
}
ostream& operator<<(ostream &out, Ensemble E){
    return E.affiche(out);
}
Ensemble::Ensemble(){
    card = 0;
}
int Ensemble::cardinal() const{
    return card;
}
bool Ensemble::estVide() const{
    return card == 0;
}
void Ensemble::ajoute(int o){
    if(!(card < MAXCARD)){
        throw std::invalid_argument("ensemble plein");
    }
    tab[card] = o;
    card++;
}
int Ensemble::tire(){
    if(card == 0){
        throw std::invalid_argument("ensemble vide");
    }
    int i = rand()%card;
    int mov = tab[card-1];
    int ret = tab[i];
    tab[i] = mov;
    card--;
    return ret;
}
bool Ensemble::in(int a){
    for(auto i: tab){
        if(i == a){
            return true;
        }
    }
    return false;
}


TEST_CASE("affiche ensemble"){
    Ensemble E;
    for (int i = 0; i <MAXCARD; i++){
        E.ajoute(i);
    }
    // cout<<E<<endl;
    // Ensemble F;
    // cout<<F<<endl;
}
TEST_CASE("ajoute/tire ensemble"){
    Ensemble E;
    for (int i = 0; i <MAXCARD; i++){
        E.ajoute(i);
    }
    Ensemble F;
    CHECK_THROWS_AS(F.tire(), invalid_argument);
    CHECK_THROWS_AS(E.ajoute(18), invalid_argument);
    while(!E.estVide()){
        int prevCard = E.cardinal();
        int a = E.tire();
        CHECK(a<MAXCARD);
        CHECK(a>=0);
        CHECK(E.cardinal() == prevCard -1);
    }
}