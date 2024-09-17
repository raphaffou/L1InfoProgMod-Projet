#define DOCTEST_CONFIG_IMPLEMENT
#include "jeu.hpp"
#include "doctest.h"
#include <iostream>
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */
#include <iomanip>
#include <stdlib.h>

using namespace std;

bool in_argv(int argc, const char *argv[], const char *c){
    for(int i=0; i<argc; i++){
        // cout << "argv[" << i << "]: " << argv[i] << endl;
        if(strcmp(argv[i], c) == 0)
            return true;
    }
    return false;
}

int next_arg(int argc, const char *argv[], const char *c){
    for(int i=0; i<argc; i++){
        // cout << "argv[" << i << "]: " << argv[i] << endl;
        if(strcmp(argv[i], c) == 0){
            if(argv[i+1] != NULL)
                return strtol(argv[i+1], NULL, 10);
            return -2;
        }
    }
    return -1;
}

void help(string lang = "en"){
    system("clear");
    cout << "\033[91mUsage: ./main [options]\033[0m" << endl;
    cout << "Options:" << endl;
    if(lang == "fr"){
        cout << "    -h, -help                    : affiche l'aide" << endl;
        cout << "    -s                           : sauvegarde en générant le gif" << endl;
        cout << "    -d <delay>                   : délai entre deux images dans le gif" << endl;
        cout << "    -v -vieux                    : active le mode vieillissement" << endl;
        cout << "    -step                        : active le mode deplacement par deplacement" << endl;
        cout << "    -show [all|count|write|grid] : grid  -> affiche la grille dans le terminal à chaque tour" << endl;
        cout << "                                   count -> affiche le nombre de lapins et de renards à chaque tour" << endl;
        cout << "                                   write -> affiche l'écriture des fichiers (ppm)" << endl;
        cout << "                                   all   -> affiche count et write" << endl;
        cout << "    -target -t <filename>.gif    : pour spécifier la cible du fichier gif" << endl;
        cout << "    -lang [en|fr]                : choisir la langue de la documentation (default : en)" << endl;
    }
    else{
        cout << "    -h, -help                    : show this help" << endl;
        cout << "    -s                           : save/generate the gif" << endl;
        cout << "    -d <delay>                   : time between each picture of the gif" << endl;
        cout << "    -v -vieux                    : activate the aging mode" << endl;
        cout << "    -step                        : activate the step by step mode" << endl;
        cout << "    -show [all|count|write|grid] : grid  -> display at every turn the grid in the terminal" << endl;
        cout << "                                   count -> display the number of rabbits and fox at every turn" << endl;
        cout << "                                   write -> show the writting file (ppm)" << endl;
        cout << "                                   all   -> show count and write" << endl;
        cout << "    -target -t <filename>.gif    : to specify the gif file" << endl;
        cout << "    -lang [en|fr]                : choose the language of the documentation (default : en)" << endl;
    }
    return;
}

string next_arg_str(int argc, const char *argv[], const char *c){
    for(int i=0; i<argc; i++){
        // cout << "argv[" << i << "]: " << argv[i] << endl;
        if(strcmp(argv[i], c) == 0){
            if(argv[i+1] != NULL)
                return argv[i+1];
            return "-2";
        }
    }
    return "-1";
}


int main(int argc, char const *argv[]){

    system("rm -f images/*");
    system("rm -rf images");
    system("mkdir images");
    string lang = next_arg_str(argc, argv, "-lang") == "fr" ? "fr" : "en";
    if(in_argv(argc, argv, "-h") || in_argv(argc, argv, "-help")) {help(lang); return 0;};

    bool step = in_argv(argc, argv, "-step");
    bool vieux = in_argv(argc, argv, "-vieux") || in_argv(argc, argv, "-v");
    bool show_process = in_argv(argc, argv, "-show");
    string show = "None";
    if(show_process){
        show = next_arg_str(argc, argv, "-show");
        if(show == "-2" || show == "-1" || (show != "all" || show != "write" || show != "count" || show != "grid"))
            show_process = false;
    }

    srand(time(NULL));
    Game g;
    int i = 0;
    while(!g.fin() && i < 100){
        // cout << g << endl;
        i++;
        g.tour(step, vieux, show);
        if(show == "grid") cout << g << endl;
    }
    g.tour(step, vieux, show);
    
   
   


    if(in_argv(argc, argv, "-s")) {
        int d = next_arg(argc, argv, "-d");
        d = (d <= 0) ? 10 : d;
        string target = next_arg_str(argc, argv, "-target");
        target = target  == "-2" || target == "-1" ? "movie" : target;
        cout << "\n\033[1;92mDelay :\033[0m " << d << "\033[0m" << endl;
        cout << "\033[1;92mMode :\033[0m " << boolalpha << (step ? "déplacement" : "tour") << "\033[0m" << endl;
        cout << "\033[1;92mVieillissement :\033[0m " << boolalpha << vieux << "\033[0m" << endl;
        cout << "\033[1;92mNom gif :\033[0m " << boolalpha << target << ".gif\033[0m" << endl;
        cout << "\033[94mConverting to gif... \033[0m" << flush;
        string s = "convert -scale 300 -delay " + std::to_string(d) + " images/img*.ppm " + target + ".gif";
        system(s.c_str());
        cout << "\033[92mSuccess !\033[0m" << endl;
    }
    return 0;
}