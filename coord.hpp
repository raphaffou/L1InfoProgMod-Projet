#ifndef COORD
#define COORD

#include <iostream>
#include "ensemble.hpp"




class Coord {
    private:
        int x;
        int y;
    public:
        //Constructeur
        // Coord();
        Coord(int x, int y);
        Coord(int n);
        //Getters
        int getX() const;
        int getY() const;
        //Opperateurs
        bool operator==(const Coord &) const;
        bool operator!=(const Coord &) const;
        



        //Methodes
        // Ensemble EnsCoord_voisins(Coord c);
        std::ostream& affiche(std::ostream& out);
        int toInt() const;
        Ensemble voisines();



};
std::ostream& operator<<(std::ostream& out, Coord &c);

#endif