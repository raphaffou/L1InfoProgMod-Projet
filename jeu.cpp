#include "jeu.hpp"
#include "doctest.h"
#include "coord.hpp"
#include <sstream>
#include <fstream> 
#include <iomanip>
#include <math.h>

using namespace std;

ostream& Game::affiche(ostream& out){
    for(int i = 0; i < TAILLEGRILLE; i++){
        for(int j = 0; j < TAILLEGRILLE; j++){
            Coord c = Coord(j, i);
            int id = _grille.getCase(c);
            if(id == -1){
                out<<". ";
            }else{
                Animal a = _population.get(id);
                out << a.toString() << " ";
            }
        }
        out<<endl;
    }
    return out;

}


ostream& operator<<(ostream& out, Game g){
    return g.affiche(out);
}

Coord Game::getRandomCoord(){
    //get valid coord
    int nbcases = TAILLEGRILLE * TAILLEGRILLE;
    Coord c = Coord(rand()%nbcases);
    // coord.affiche(cout);
    while(!_grille.caseVide(c)){
        // cout << c << endl;
        c = Coord(rand()%nbcases);
    }
    return c;
}

void Game::ajouteAnimal(Animal a, Coord coord){
    int id = _population.set(a);
    _grille.setCase(Animal(id, a.getEspece(), coord), coord);
}
	
Game::Game(){
    _grille = Grille();
    long int nbcases = MAXCARD;
    long int nbRenards = (7*nbcases)/100;
    long int nbLapin = (2*nbcases)/10;

    for(int i = 0; i < nbRenards;i++){
        //get valid coord
        Coord c = Coord(rand()%nbcases);
        // coord.affiche(cout);
        while(!_grille.caseVide(c)){
            // cout << c << endl;
            c = Coord(rand()%nbcases);
        }
        //id n'importe pas puisque set automatiqument par Population::set
        Animal r = Animal(0, Espece::Renard, c);
        ajouteAnimal(r, c);
    }
    for(int i = 0; i < nbLapin;i++){
        //get valid coord
        Coord c = Coord(rand()%nbcases);
        while(!_grille.caseVide(c)){
            c = Coord(rand()%nbcases);
        }
        //id n'importe pas puisque set automatiqument par Population::set
        Animal l = Animal(0, Espece::Lapin, c);
        ajouteAnimal(l, c);
    }
    // cout << *this << endl;
}

void Game::verifieGrille(){  
    Ensemble validIds = _population.getIds();
    while(!validIds.estVide()){
        int id = validIds.tire(); 
        Animal a = _population.get(id);
        Coord coordA = a.getCoord();
        if(!(_grille.getCase(coordA) == a.getId())){
            cout<<"grille et population contradictoires : animal numero " << a.getId() << " attendu au point ("<<coordA.getX()<<","<<coordA.getY()<<")"<< "(found "<<_grille.getCase(coordA)<<")"<<endl;
            throw runtime_error("grille non valide");
        }
    }
}

Ensemble Game::voisinsVides(Coord c) const{
    Ensemble voisins = c.voisines();
    Ensemble voisinsVide;
    while(!voisins.estVide()){
        int vInt = voisins.tire();
        Coord v = Coord(vInt);
        int id = _grille.getCase(v);
        if(id<0){
            voisinsVide.ajoute(vInt);
        }
    }
    return voisinsVide;
}

Ensemble Game::voisinsEspece(Coord c, Espece e){
    Ensemble voisins = c.voisines();
    Ensemble voisinsEspece;
    while(!voisins.estVide()){
        int vInt = voisins.tire();
        Coord v = Coord(vInt);
        int id = _grille.getCase(v);
        if(id>=0){
            if(_population.get(id).getEspece() == e){
                voisinsEspece.ajoute(vInt);
            }
        }
    }
    return voisinsEspece;
}

void Game::deplaceSurVoisin(Coord cDep, Coord cArr){
    Ensemble voisinsCDep = cDep.voisines();
    if(not(voisinsCDep.in(cArr.toInt()))){
        throw invalid_argument("ces cases ne sont pas voisines");
    }
    //_population.get(_grille.getCase(cArr)) get animal from coord
    if(_grille.getCase(cArr) != -1){
        throw invalid_argument("arrivée non vide");
    }
    if(_grille.getCase(cDep) == -1){
        throw invalid_argument("départ vide");
    }
    Animal &a = _population.get(_grille.getCase(cDep));
    //modifier grille + modifier infos animal
    a.setCoord(cArr);
    _grille.setCase(Animal(-1, Espece::Lapin, Coord(0, 0)), cDep);
    _grille.setCase(a, cArr);
}

void Game::draw(bool show, bool vieillissement){
	int i,j;
	int r,g,b;
	ostringstream filename;
	// creation d'un nouveau nom de fichier de la forme img347.ppm
	filename << "images/img" << setfill('0') << setw(4) << _cptImg << ".ppm";
	_cptImg++;
	if(show) cout << "\033[1mEcriture dans le fichier : \033[0m" << "\033[92m" << filename.str() << "\033[0m" << endl;
	// ouverture du fichier
	ofstream fic(filename.str(), ios::out | ios::trunc);
	// ecriture de l'entete
	fic << "P3" << endl
		<< TAILLEGRILLE << " " << TAILLEGRILLE << " " << endl
		<< 255 << " " << endl;
	// ecriture des pixels
	for (i = 0; i < TAILLEGRILLE; i++){
		for (j = 0; j < TAILLEGRILLE; j++){
			// calcul de la couleur
			Coord c = Coord(i, j);
			int id = _grille.getCase(c);
			if(id<0) r = g = b = 0;
			else{
				Animal a = _population.get(id);
                int old = 0;
				if(vieillissement) old = float(a.getAge())/a.getAgeMort() * 150.;
                if(a.getEspece() == Espece::Renard){
					switch(a.getSexe()){
                        case true: r = 255; g = b = old; break;
					    case false: r = g = old; b = 255; break;
                        default: r = g = b = 0;
                    }
				}
                else{
					switch(a.getSexe()){
                        case true: r = 255; g = b = old; break;
					    case false: r = g = old; b = 255; break;
                        default: r = g = b = 0;
				    }
                }
                if(!a.getAge() && _cptTour > 1 && vieillissement) g = 140 + (a.getEspece() == Espece::Lapin ? 30 : 0);
			}
			
			// ecriture de la couleur dans le fichier
			fic << r << " " << g << " " << b << "    ";
		}
		// fin de ligne dans l'image
		fic << endl;
	}
	// fermeture du fichier
	fic.close();
	
	return;
}
bool Game::mange(int id){
    if(id == -1){
        throw invalid_argument("un animal n'existant pas ne peux pas manger");
    }
    Animal &a = _population.get(id);
    if(!(a.getEspece() == Espece::Lapin || voisinsEspece(a.getCoord(), Espece::Lapin).estVide())){
        Ensemble lapinsAutour = voisinsEspece(a.getCoord(), Espece::Lapin);
        int coordLapin = lapinsAutour.tire();
        Coord trueCoord = Coord(coordLapin);
        int idLapin = _grille.getCase(trueCoord);
        // cout<< _population.get(idLapin).toString() << endl;
        _grille.videCase(trueCoord);
        _population.supprime(idLapin);
        a.mange();
        deplaceSurVoisin(a.getCoord(), trueCoord);
        return true;
    }
    return false;
}

bool Game::sexeInVoisins(bool sexe, Ensemble voisins){
    bool autreSexe = !sexe;
    while(!voisins.estVide()){
        int vCoord = voisins.tire();
        Coord v = Coord(vCoord);
        int id = _grille.getCase(v);
        Animal a = _population.get(id);
        if(a.getSexe() == autreSexe){
            return true;
        }
    }
    return false;
}

bool Game::reproduction(int id){
    if(id == -1){
        throw invalid_argument("un animal n'existant pas ne peux pas se reproduire");
    }
    Animal &a = _population.get(id);
    Ensemble voisinsRenards = voisinsEspece(a.getCoord(), Espece::Renard);
    Ensemble voisinsLapins = voisinsEspece(a.getCoord(), Espece::Lapin);
    if(a.seReproduit( 
        voisinsVides(a.getCoord()), 
        sexeInVoisins(a.getSexe(), voisinsRenards), sexeInVoisins(a.getSexe(), voisinsLapins) 
        )
    ){
        Coord ancienneCoord = a.getCoord();
        deplaceVideAlea(id);
        int idNewBorn = _population.set(Animal(69, a.getEspece(), ancienneCoord));//id modifiée par set, donc n'importe pas
        _grille.setCase(_population.get(idNewBorn), ancienneCoord);
        return true;
    }
    return false;
}

int Game::recensement(Espece e){
    return _population.recensement(e);
}

void Game::deplaceVideAlea(int id){
    Animal &a = _population.get(id);
    if(voisinsVides(a.getCoord()).estVide()) return;
    deplaceSurVoisin(
            a.getCoord(),
            Coord(voisinsVides(a.getCoord()).tire())
        );
}

void Game::jeune(int id){
    Animal &a = _population.get(id);
    a.jeune();
}

void Game::anniversaire(int id){
    Animal &a = _population.get(id);
    a.anniversaire();
}

void Game::meurt(int id){
    Animal &a = _population.get(id);
    if(a.meurt()){
        _grille.setCase(Animal(-1, Espece::Lapin, Coord(0, 0)), a.getCoord());
        _population.supprime(id);
    }
}

Ensemble Game::keepIdEspece(Ensemble l, Espece e){
    Ensemble res;
    while(!l.estVide()){
        int id = l.tire();
        if(_population.get(id).getEspece() == e){
            res.ajoute(id);
        }
    }
    return res;
}

void Game::coherenceGrilleAnimal(){
    for(int i = 0; i<TAILLEGRILLE*TAILLEGRILLE;i++){
        Coord coordCase = Coord(i);
        int id = _grille.getCase(coordCase);
        if(id == -1)
            continue;
        Animal a = _population.get(id);
        if(a.getCoord() != coordCase)
            throw runtime_error("incoherence de la grille");
    }
}

void Game::tour(bool drawDeplacement, bool vieillissement, string show){
    Ensemble ids = _population.getIds();
    Ensemble idsRenards = keepIdEspece(ids, Espece::Renard);
    Ensemble idsLapins = keepIdEspece(ids, Espece::Lapin);
    _cptTour++;
    if(show == "all" || show == "count") cout << "\033[1;4mTour n°" << _cptTour << ":\033[0m" << endl;
    if(show == "all" || show == "count") cout<<"\t\033[1;91mRenards : \033[0m" << recensement(Espece::Renard) << endl;
    if(show == "all" || show == "count") cout<<"\t\033[1;94mLapins : \033[0m" << recensement(Espece::Lapin) << endl;
    
    bool write = show == "write" || show == "all";

        

    //tour lapins
    while(!idsLapins.estVide()){
        int id = idsLapins.tire();
        if(!reproduction(id)){
            deplaceVideAlea(id);
        }
        if(vieillissement) anniversaire(id);
        meurt(id);
        if(drawDeplacement) draw(write, vieillissement);
    }
    //tour renards
    while(!idsRenards.estVide()){
        int id = idsRenards.tire();
        if(!reproduction(id)){
            if(!mange(id)){
                deplaceVideAlea(id);
                jeune(id);
            }
        }else{ // quand il se reproduit
            jeune(id);
        }
        if(vieillissement) anniversaire(id);
        meurt(id);
        if(drawDeplacement) draw(write, vieillissement);
    }
    verifieGrille(); // coherence animal grille
    coherenceGrilleAnimal();
    if(!drawDeplacement) draw(write, vieillissement);
}

bool Game::fin(){
    return recensement(Espece::Renard) == 0 || _population.getIds().estVide();
}


TEST_CASE("ajoute_animal"){
    Game g;
    Coord c = g.getRandomCoord();
    g.ajouteAnimal({1, Espece::Renard, c}, c);
    CHECK(g.recensement(Espece::Renard) == int(pow(TAILLEGRILLE, 2) * 0.07 + 1));
    CHECK(g.recensement(Espece::Lapin) == int(pow(TAILLEGRILLE, 2) * 0.2));
    CHECK_NOTHROW(g.verifieGrille());
}


