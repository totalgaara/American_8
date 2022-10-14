#pragma once

#include "sql/sqlite3.h"
#include <iostream>
#include "Joueur.hpp"
#include "Definitions.h"
#include "Carte.hpp"

class DB_Controller {
private:
    sqlite3 * _DATABASE;
    char * _MessageErreur = nullptr;
public:
    int Ouvrir_DB();
    void Fermer_DB();

    void CreerTableScore();

    void CreerTableJoueurs();

    void CreerTableGames();

    void CreerTableCartes();

    void EcrireGames();

    void EcrireJoueurs(Joueur *joueurs[NOMBREJOUEUR]);
    void EcrireCards(int JoueurActuel, Carte Carte);
    void EcrireScore(Joueur *joueurs[NOMBREJOUEUR], string type);


    void SelectScore();
    void SelectVictoire();
    void SelectCartesJouees();

    void UpdateTablePlayersForWinner(Joueur *Gagnant);

    void SelectGetRounds();

    void SelectGetBestWinner();

    void SelectMostPlayedSymbol();
};