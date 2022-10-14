#pragma once
#include <iostream>
#include "Definitions.h"

using namespace std;

class Carte
{
    public:
        Carte(); //Constructeur par défaut
        ~Carte();
        Carte(int valeurFace, int symbole); //Constructeur acceptant une valeur de la face et un type de symbole
        int GetValeurFace();
        int GetSymbole();
        static string symboles[4];
        static string faces[14];
        static string GetSymbolAtIndex(int Index);


    private:
        int symbole;
        int valeurFace;
        friend ostream& operator<<(ostream&, const Carte&);
};