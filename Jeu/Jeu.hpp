#pragma once
#include <iostream>
#include "Carte.hpp"
#include "Tas.hpp"
#include "Joueur.hpp"
#include "Messages.hpp"
#include "Definitions.h"
#include "DB_Controller.hpp"
#include "sql/sqlite3.h"
using namespace std;

class Jeu{

public:
    Jeu();
    ~Jeu();

    Messages Message;
    DB_Controller DB;
    Joueur* joueurs[NOMBREJOUEUR]{};
    Tas* tasdecartes;

    /* Méthodes */
    void ChangerTour();
    void Tour();
    void ChangerSens();
    void Demarrer();
    int vface;
    int symb;


private:
    Pioche *pioche;
    int JoueurActuel = 0;
    bool SensHoraire = true;
    bool ContreRegleJoker = false;
    bool ContreRegleDeux = false;
    void RegleRejouer();
    void FairePiocherCarte(int nombre, int joueur);
    void Regulateur(int _vface);
    void CreerJoueurs(int amount);
    void CreerTas();
    void AfficherDetailsTour();
    bool CarteValide(Carte carte);
    void SiPiocheVide();
    void RemplirPioche();
    void JouerUneCarte();
    void DeposerCarteTas(Carte carte, int j);
    bool FinDePartie();
    bool FinDeRound();
    void DonnerCarte(int NombreDeCarteADonner);
    void AfficherTas();
    void ChangerCouleur();
    void CalculerScoreDesJoueurs();
    void RemettreZeroRound();
    void RemplirLesMains();
    string GetGagnant();

    void RegleContreJoker();

    void RegleContreDeux();
};