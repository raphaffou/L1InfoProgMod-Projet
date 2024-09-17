#ifndef JEU
#define JEU
#include "grille.hpp"
#include "population.hpp"
#include "jeu.hpp"


class Game{
    private:
        Grille _grille;
        Population _population;
        int _cptImg = 0;
        int _cptTour = 0;
    public:
        Game();
        void ajouteAnimal(Animal a, Coord coord);
        void verifieGrille();
        void coherenceGrilleAnimal();
        void draw(bool show = false, bool vieillissement = false);
        void anniversaire(int);
        Ensemble voisinsVides(Coord c) const;
        Ensemble voisinsEspece(Coord c, Espece e);
        void deplaceSurVoisin(Coord cDep, Coord cArr);
        bool mange(int id);//si l'animal est un renard non-isolé, alors ça lui fait manger un lapin aleatoire à coté de lui. Return true si il mange, false sinon /!\ fait se dplacer l'animal, ie: ne peut pas utiliser mange et reproduction en meme temps 
        bool reproduction(int id); //true si reproduction, false sinon /!\ fait se dplacer l'animal, ie: ne peut pas utiliser mange et reproduction en meme temps
        void deplaceVideAlea(int id);
        void jeune(int id);
        void meurt(int id); 
        bool sexeInVoisins(bool sexe, Ensemble voisins);
        Ensemble keepIdEspece(Ensemble l, Espece e);
        int recensement(Espece e);
        void tour(bool drawDeplacement = false, bool vieillissement = false, string show = "None");
        ostream& affiche(ostream& out);
        Coord getRandomCoord();
        bool fin();
};      

ostream& operator<<(ostream& out, Game g);

#endif