#include "Messages.hpp"

void Messages::Bienvenue(){
    cout << "\n**** Début de la partie !\n" << endl;
}


void Messages::CarteChoisie(Carte carte){
    cout << "**** Carte choisie : " << carte << "\n" << endl;
}

void Messages::AfficherMainsJoueur(Joueur* joueurs[NOMBREJOUEUR], int JoueurActuel) {

    for(int i = 0; i < NOMBREJOUEUR; i++){
        if(i == (JoueurActuel)) cout << "> " << joueurs[i]->Getnom() << ": ";
        else cout << "- " << joueurs[i]->Getnom() << ": ";
        for (int j = 0; j < joueurs[i]->MainJoueur.size(); j++)
        {
            Carte *carteActuel = &joueurs[i]->MainJoueur.at(j);
            cout << *carteActuel << " ";
            //cout << " " << *carteActuel ;
        }
        cout << endl;
    }
}

void Messages::CarteEffet(int value)
{
    switch (value)
    {
        case 0:
            cout << "**** Effet : changement de sens pour les tours\n" << endl;
            break;
        case 1:
            cout << "**** Attaque : 2 cartes pour le joueur suivant\n" << endl;
            break;
        case 7:
            cout << "**** Effet : changement de couleur\n" << endl;
            break;
        case 9:
            cout << "**** Effet : le joueur actuel rejoue\n" << endl;
            break;
        case 10:
            cout << "**** Effet : le prochain joueur passe son tour\n" << endl;
            break;
        case 13:
            cout << "**** Attaque : 4 cartes pour le joueur suivant\n" << endl;
            break;
    }
}

void Messages::PiocheVide(){
    cout << "**** La pioche est vide : remplissage par le tas !\n" << endl;
}

void Messages::PiocheUneCarte(){
    cout << "\n**** Tu sais pas jouer ? Tu prends 1 carte !" << endl;
}
void Messages::FinDePartie(){
    cout << endl;
    cout << "**** Fin de la partie !" << endl;
}
void Messages::FinDeRound(){
    cout << "**** Fin du round !" << endl;
}