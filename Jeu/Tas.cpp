#include "Tas.hpp"

Tas::Tas(){}
Tas::~Tas(){}
Tas::Tas(Pioche &pioche){
    Carte carte;
    do
    {
        carte = pioche.donnerCarte();
        this->TasDeCartes.push_back(carte);
        pioche.supprimerCarte();
    }
    while (carte.GetValeurFace() == JOKER); // comparaison de la carte déposée sur le tas. Si joker (13) alors on continue la boucle et on dépose une autre carte.

     //Supprime la carte existante de la pioche -> Elle a été distribuée
}


Carte& Tas::DerniereCarte()
{
    return this->TasDeCartes.back();
}

void Tas::AfficherLeTas(){
    for(Carte &alt:TasDeCartes){
        cout <<  alt << " ";
    }
}
