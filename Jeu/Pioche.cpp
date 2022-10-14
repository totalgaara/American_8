#include <algorithm>
#include <time.h>
#include "Pioche.hpp"

using namespace std;


int RandomCarte (int i) {
    return std::rand()%i;
}

Pioche::~Pioche() {}
Pioche::Pioche() {

    //size_t = indexation de tableaux , comptage de boucles (c'est un int non signé)
    //c'est un type qui peut contenir un nombre assez grand pour représenter la taille du plus grand objet créable
    size_t compteur_faces = 14;
    size_t compteur_symboles = 4;

    for (int i = 0; i < compteur_symboles; i++)
    {
        for (int j = 0; j < compteur_faces-1; j++)
        {
            Carte carte(j, i);
            this->Vecteurpioche.push_back(carte);
        }
        Carte carte((int)compteur_faces-1,4);
        this->Vecteurpioche.push_back(carte);
    }
    Melanger();
    this -> CarteCourante = 0; //CarteCourante vaut 0
}

void Pioche::Melanger() {
    srand(unsigned(time(NULL)));
    random_shuffle(Vecteurpioche.begin(), Vecteurpioche.end(), RandomCarte); //Mélangeur de carte non aléatoire
}

Carte Pioche::donnerCarte()
{
    return this->Vecteurpioche [this->Vecteurpioche.size()-1];  //Récupère l'objet courant de la pioche
}


void Pioche::supprimerCarte()
{
    //Pop back permet de supprimer l'élement x du vecteuri
    this-> Vecteurpioche.pop_back();
}

void Pioche::setCarteCourante() {
    this->CarteCourante = 0;
}

vector<Carte>* Pioche::GetPiocheVector() {
    return &Vecteurpioche;
}

void Pioche::voirPioche()
{
    cout << "Contenu de Pioche:   ";
    for(Carte &cartepioche:Vecteurpioche){ //Appel de référence
        cout <<  " " << cartepioche;
    }
    cout << endl;

}