#ifndef GRILLE
#define GRILLE
#include <vector>
#include "animal.hpp"


using namespace std;
class Grille {
    private:
        vector<vector<int>> _data;
    public:
        Grille();
        bool caseVide(Coord coord) const;
        int getCase(Coord coord) const;
        void videCase(Coord coord);
        void setCase(Animal a, Coord coord);

};

#endif