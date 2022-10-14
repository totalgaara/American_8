#pragma once
#include <vector>
#include "Pioche.hpp"

using namespace std;

using std::vector;

class Tas {
    public :
    Tas();
    ~Tas();

    Carte& DerniereCarte();

    vector<Carte> TasDeCartes;
    Tas (Pioche &pioche);

    void AfficherLeTas();
};