#ifndef ENSEMBLE
#define ENSEMBLE
#include <array>
#include <iostream>
using namespace std;

int const TAILLEGRILLE = 20;
int const MAXCARD = TAILLEGRILLE*TAILLEGRILLE;

class Ensemble {
    private:
        array<int, MAXCARD> tab;
        int card;
    public:
        Ensemble();
        ostream& affiche(ostream& out) const;
        int cardinal() const;
        bool estVide() const;
        bool in(int a);
        void ajoute(int o);
        int tire();
};
ostream& operator<<(ostream &out, Ensemble e);
#endif