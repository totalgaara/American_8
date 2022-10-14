#include "Carte.hpp"

Carte::Carte() {} //Constructeur par défaut 
Carte::~Carte() {}

Carte::Carte(int valeurFace, int symbole) 
{
    this->valeurFace = valeurFace;
    this->symbole = symbole;
}

int Carte::GetValeurFace() {
    return this->valeurFace;
}

int Carte::GetSymbole() {
    return this->symbole;
}
string Carte::GetSymbolAtIndex(int Index)
{
    return symboles[Index];
}


string Carte::faces[14] = {"As", "2", "3", "4", "5", "6", "7", "8",
                         "9", "10", "V", "D", "R", "J"};
/*
Symboles unicodes :
u2660 == Pique , u2665 == Coeur
u2663 == Trefle , u2666 == Carreau
*/
string Carte::symboles[4] = {u8"\u2660", ROUGE u8"\u2665" RCOULEUR, u8"\u2663", ROUGE u8"\u2666" RCOULEUR};

//Surcharge de l'opérateur de flux. Permet de retourner une référence et non un objet.
//1er paramètre: ostream est l'objet cout
//2ème paramètre: carte est une référence constante vers l'objet de symbole Carte que l'on tente d'afficher
ostream& operator<<(ostream &os, const Carte &carte) {
    //La fonction doit récupérer les attributs qui l'intéresse dans l'objet et les envoyer à l'objet os pour ensuite renvoyer une référence 
    //sur cet objet qui permet de faire une chaine
    if(carte.symbole == 4)
    {
        return os << Carte::faces[carte.valeurFace];
    }
    return os << Carte::faces[carte.valeurFace] << "" << Carte::symboles[carte.symbole];
}
//Si on ne fait pas ça, on obtient une référence indéfinie vers « operator<<(std::ostream&, Carte const&)
//
