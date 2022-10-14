#pragma once
#include "Pioche.hpp"
#include "Tas.hpp"

using namespace std;

class Joueur {

private:
    string nom;
    int score;
public :
    Joueur();
    ~Joueur();
    Joueur(string nom, int _score); // nom du joueur , ref de pioche
    string Getnom();
    vector<Carte> MainJoueur;
    int AjouterScoreValeur(int _vface);
    void AjouterScore(int i);
    int GetScore();
    void CalculerScore();
    void RemplirMain(Pioche *pioche);
};
