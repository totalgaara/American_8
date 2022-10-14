#include <iostream>

#include "Jeu/Pioche.hpp"
#include "Jeu/Joueur.hpp"
#include "Jeu/Tas.hpp"
#include "Jeu/Jeu.hpp"
#include "Jeu/sql/sqlite3.h"

using namespace std;


/* On crée les méthodes directement ici car Main ne necessite pas de hpp */
bool ContinuerAJouer();

int main(int argc, char const *argv[])
{
    do{
        Jeu jeu;
        jeu.Demarrer();
    }
    while(ContinuerAJouer());
    return 0;
}


bool ContinuerAJouer(){
    cout << endl;
    cout << "[ =~=~=~=~=~=~=~= "<< JAUNE << "LE 8 AMERICAIN" << RCOULEUR<< " =~=~=~=~=~=~=~= ]" << endl;
    cout << "Voulez vous continuer à jouer ?" << endl;
    cout << "Répondez par :  oui / non" << endl;

    do{

        cout << "> ";
        string choix;
        cin >> choix;

        if(choix == "oui" || choix == "Oui" || choix == "OUI"){
            return true;
        }
        else if(choix =="non" || choix == "Non" || choix == "NON")
        {

            cout << VERT << "Au revoir ! :)" << RCOULEUR << endl;
            return false;
        }
        else
        {
            cout << ROUGE << "Merci de répondre par oui / non uniquement." << RCOULEUR << endl;
        }
    }
    while(true);
}