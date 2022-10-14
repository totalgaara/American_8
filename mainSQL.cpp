#include "Jeu/Jeu.hpp"
#include "Jeu/sql/sqlite3.h"
#include "Jeu/Definitions.h"
using namespace std;

void cleanup()
{
    for(int i = 0; i < 50; i++){
        cout << endl;
    }
}

int main(int argc, char const *argv[])
{
    DB_Controller Prog_SQL;
    cout << endl;
    cout << "[ =~=~=~=~=~=~=~= "<< JAUNE << "LE 8 AMERICAIN STATISTIQUES " << RCOULEUR<< " =~=~=~=~=~=~=~= ]" << endl;

    do{
        cout << "[=~=~=~=~ MENU PRINCIPAL =~=~=~=~ ]" << endl;
        cout << "1 : Consulter le score par ordre croissant des parties" << endl;
        cout << "2 : Consulter les victoires des joueurs" << endl;
        cout << "3 : Consulter les statistiques des cartes jouées" << endl;
        cout << "4 : Consulter la moyenne de round par partie" << endl;
        cout << "5 : Obtenir le meilleur joueur gagnant" << endl;
        cout << "6 : Taux de jeu de chaque couleur de cartes " << endl;
        cout << "7 : Quitter" << endl;
        cout << "> ";

        int choix;
        cin >> choix;

        switch(choix){
            case 1 : cleanup(); cout << VERT << "Statistiques : [SCORE PAR ORDRE CROISSANT]" << RCOULEUR << endl; Prog_SQL.SelectScore(); break;
            case 2 : cleanup(); cout << VERT << "Statistiques : [JOUEURS]" << RCOULEUR << endl; Prog_SQL.SelectVictoire();break;
            case 3 : cleanup(); cout << VERT << "Statistiques : [CARTES]" << RCOULEUR << endl; Prog_SQL.SelectCartesJouees(); break;
            case 4 : cleanup(); cout << VERT << "Statistiques : [ROUNDS]" << RCOULEUR << endl; Prog_SQL.SelectGetRounds() ; break;
            case 5 : cleanup(); cout << VERT << "Statistiques : [MEILLEUR GAGNANT]" << RCOULEUR << endl; Prog_SQL.SelectGetBestWinner(); break;
            case 6 : cleanup(); cout << VERT << "Statistiques : [CARTES SYMBOLE]" << RCOULEUR << endl; Prog_SQL.SelectMostPlayedSymbol(); break;
            case 7 : cleanup(); cout << VERT << "Au revoir ! :)" << RCOULEUR << endl; return 0;
            default: cleanup(); cout << ROUGE << "Choix invalide." << RCOULEUR << endl; break;
        }

    }
    while(true);
}


