#pragma once
#include <vector>
#include "Carte.hpp"
using namespace std;

using std::vector;


class Pioche {
    public:
        int CarteCourante; // Index de carte sur la pile
        Pioche();
        ~Pioche();
        void supprimerCarte();
        Carte donnerCarte();
        vector<Carte> Vecteurpioche;
        vector<Carte>* GetPiocheVector();
        void setCarteCourante();
        void Melanger();

    void voirPioche();
};