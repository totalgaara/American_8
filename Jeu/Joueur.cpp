#include "Joueur.hpp"
#include "Definitions.h"

Joueur::Joueur() {} //Constructeur par défaut
Joueur::~Joueur() {}

Joueur::Joueur(string nom, int _score) //Nom du joueur, référence pioche
{ 
    this ->nom = nom;
    this ->score = _score;
}

string Joueur::Getnom()
{
    return this->nom;
}


void Joueur::RemplirMain(Pioche* pioche)
{
    for (int i=0; i < 7; i++)
    {
        Carte carte = pioche->donnerCarte();
        this->MainJoueur.push_back(carte);
        pioche->supprimerCarte();
    }
}
void Joueur::CalculerScore()
{
    for (int i =0; i < MainJoueur.size(); i++)
    {
        AjouterScore(AjouterScoreValeur(MainJoueur[i].GetValeurFace()));
    }
}
int Joueur::GetScore(){
    return this->score;
}

void Joueur::AjouterScore(int i){
    this->score = score+i;
}
int Joueur::AjouterScoreValeur(int _vface){
    switch(_vface){

        case AS: return 20; //           Carte AS
        case DEUX: return 20; //           Carte "2"
        case 2: return 3;  //           Carte "3"
        case 3: return 4;  //           Carte "4"
        case 4: return 5;  //           Carte "5"
        case 5: return 6;  //           Carte "6"
        case 6: return 7;  //           Carte "7"
        case HUIT: return 50; //           Carte "8"
        case 8: return 9; //            Carte "9"
        case 9: return 10;//           Carte "10"
        case VALET: return 50; //          Carte "Valet"
        case DAME: return 10;//              Carte "Dame"
        case ROI: return 10;//              Carte "Roi"
        case JOKER: return 50; //          Carte du Joker
        default: return 0;

    }
}
