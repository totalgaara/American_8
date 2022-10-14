#include "Joueur.hpp"
#include "Carte.hpp"
#include "Pioche.hpp"
#include "Tas.hpp"
#include <array>
class Messages {

public:

    void Bienvenue();
    void AfficherMainsJoueur(Joueur *joueurs[], int JoueurActuel);
    void CarteEffet(int value);
    void CarteChoisie(Carte carte);
    void AfficherCarteCourante(Carte carte);
    void PiocheVide();
    void PiocheUneCarte();
    void FinDePartie();
    void FinDeRound();
};

