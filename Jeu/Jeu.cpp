#include "Jeu.hpp"


Jeu::~Jeu() {

    for (int i = 0; i < NOMBREJOUEUR; i++)
        delete this->joueurs[i];
}

Jeu::Jeu() {

}

void Jeu::Demarrer() {


    /* TEST TEMPORAIRE */
    DB.Ouvrir_DB();
    DB.CreerTableCartes();
    DB.CreerTableGames();
    DB.CreerTableJoueurs();
    DB.CreerTableScore();
    DB.Fermer_DB();
    CreerJoueurs(NOMBREJOUEUR);
    DB.EcrireGames();
    do
    {
        pioche = new Pioche();
        Message.Bienvenue();
        RemplirLesMains();
        CreerTas();
        Tour();
        RemettreZeroRound();
    }
    while(!FinDePartie());

}
void Jeu::RemplirLesMains() {
    for (int i=0; i < NOMBREJOUEUR; i++)
    {
        joueurs[i]->RemplirMain(pioche);
    }
}

string Jeu::GetGagnant() //Méthode permettant de retourner le gagnant de la partie
{
    Joueur *Gagnant = this->joueurs[0];
    for (int i = 1; i < NOMBREJOUEUR; i++)
    {
        if (this->joueurs[i]->GetScore() < (Gagnant->GetScore()))
            Gagnant = this->joueurs[i];
    }
    DB.UpdateTablePlayersForWinner(Gagnant); // Met à jour la table 'Players' pour ajouter une victoire au joueur ayant remporté la partie
    return Gagnant->Getnom();
}

bool Jeu::FinDePartie(){
    for (int i = 0; i < NOMBREJOUEUR; i++)
    {
        if (joueurs[i]->GetScore() >= SCOREPOURPERDRE)
        {
            Message.FinDePartie();
            GetGagnant();
            DB.EcrireScore(joueurs,"Partie");
            return true;
        }
    }
    DB.EcrireScore(joueurs,"Round");
    return false;
}

/* Création de la partie */
void Jeu::CreerTas(){
    tasdecartes = new Tas(*pioche);
    vface = (*tasdecartes).DerniereCarte().GetValeurFace();
    symb = (*tasdecartes).DerniereCarte().GetSymbole();
}

void Jeu::CreerJoueurs(int amount){
    for(int i = 0 ; i < amount ; i++){
        joueurs[i] = new Joueur("Joueur " + to_string(i +1),0); // i+1 car nous somme dans un tableau (qui commence donc à 0, nous ne voulons pas de "Joueur 0"
    }
    DB.EcrireJoueurs(joueurs);
}

void Jeu::JouerUneCarte() {
    //pioche->voirPioche();
    Carte carte;
    int j =0;

    for (j; j < joueurs[JoueurActuel]->MainJoueur.size(); j++) //Taille de la main du joueur : 7 cartes
    {
        carte = joueurs[JoueurActuel]->MainJoueur.at(j);
        if(CarteValide(carte)){  break; }
    }
    if (j == joueurs[JoueurActuel]->MainJoueur.size())
    {
        Message.PiocheUneCarte();
       FairePiocherCarte(1, JoueurActuel);
       carte =  joueurs[JoueurActuel]->MainJoueur.at(j);

       cout << endl;
       AfficherTas();
       Message.AfficherMainsJoueur(joueurs, JoueurActuel);
       cout << endl;
    }
    if(CarteValide(carte)){

        cout << endl;
        Message.CarteChoisie(carte);
        DeposerCarteTas(carte, j);
        DB.EcrireCards(JoueurActuel,carte);
    }
}

void Jeu::DeposerCarteTas(Carte carte, int j){

    Carte tmpcarte = carte;
    this->tasdecartes->TasDeCartes.push_back(tmpcarte);
    if (tmpcarte.GetValeurFace() != JOKER){
        symb = tmpcarte.GetSymbole();
    }

    // CODE DE L'EXAMEN

    if(tmpcarte.GetValeurFace() == JOKER || tmpcarte.GetValeurFace() == DEUX)
    {
        cout << CDEBUG << "Le joueur " << this->JoueurActuel+1 << " une des deux carte et évite donc la règle" << RCOULEUR << endl;
        if(ContreRegleJoker) ContreRegleJoker = false;
        if(ContreRegleDeux) ContreRegleDeux = false;
    }
    else
    {
        cout << ROUGE << "Le joueur " << this->JoueurActuel+1 << " a déposé un  " << tmpcarte.GetValeurFace() << " et prend donc 4 ou 2 cartes " << RCOULEUR << endl;
        cout << CDEBUG << "Valeur de ContreRegleJoker : " << to_string(ContreRegleJoker) << " et valeur de ContreRegleDeux : " << to_string(ContreRegleDeux) << RCOULEUR << endl;
        if(ContreRegleJoker) { FairePiocherCarte(4 ,JoueurActuel); cout << ROUGE << "> il prend 4 cartes" << RCOULEUR << endl; }
        if(ContreRegleDeux) { FairePiocherCarte(2, JoueurActuel); cout << ROUGE << "> il prends 2 cartes" << RCOULEUR << endl; }
    }

    // FIN CODE MODIFIE DANS CETTE METHODE POUR L'EXAMEN

    // CODE PROJET
    vface = tmpcarte.GetValeurFace();
    this->joueurs[JoueurActuel]->MainJoueur.erase(joueurs[JoueurActuel]->MainJoueur.begin() + j);

    Regulateur(tmpcarte.GetValeurFace());
}

void Jeu::ChangerTour()
{
    if (SensHoraire)
    {
        if (JoueurActuel == 3) {JoueurActuel = 0;}
        else {JoueurActuel++;}
    }
    else
    {
        if (JoueurActuel == 0) { JoueurActuel = 3; }
        else {JoueurActuel--;}
    }
}

void Jeu::Tour() {

    JoueurActuel = -1;
    do
    {
        ChangerTour();
        AfficherTas();
        Message.AfficherMainsJoueur(joueurs, JoueurActuel );
        JouerUneCarte();
    }
    while(!FinDeRound());
    Message.FinDeRound();
    for (int i =0; i < NOMBREJOUEUR; i++)
    {
        cout << "- " << joueurs[i]->Getnom() << ": " << joueurs[i]->GetScore() << " points" << endl;
    }

}

void Jeu::AfficherTas() {
    cout << "- Tas : ";
    tasdecartes->AfficherLeTas();
    cout << endl;
}

bool Jeu::FinDeRound(){
    if(joueurs[JoueurActuel]->MainJoueur.empty())
    {
        CalculerScoreDesJoueurs();
        return true;
    }
    return false;
}


/* ====================================================== LES REGLES ====================================================== */

// On vérifie si la carte est valide

bool Jeu::CarteValide(Carte carte)
{
    if (carte.GetValeurFace() == JOKER || carte.GetValeurFace() == HUIT || carte.GetValeurFace() == vface || carte.GetSymbole() == symb)
    {
        return true;
    }
    else return false;
}

void Jeu::Regulateur(int _vface){
    switch(_vface){
        case AS: //REGLE DE L'AS
            ChangerSens();
        Message.CarteEffet(_vface);
        break;
        case DEUX: //REGLE DU 2 :  Faire picoher 2 cartes au joueur suivant
            // MODIFICATION D'EXAMEN
                //Message.CarteEffet(_vface); -> Mis en commentaire
                //DonnerCarte(2); -> Mis en commentaire
            RegleContreDeux();
        break;
        case HUIT: // REGLE DU 8 : Faire changer de couleur
        ChangerCouleur();
        Message.CarteEffet(_vface);
        break;
        case DIX: // REGLE DU 10
        Message.CarteEffet(_vface);
        RegleRejouer();
        break;
        case VALET: // REGLE DU VALET
        Message.CarteEffet(_vface);
        ChangerTour();
        break;
        case JOKER: // Regle du Joker fait piocher 4 cartes au joueur suivant

        // MODIFICATION D'EXAMEN
        //Message.CarteEffet(_vface); -> Mis en commentaire
        //DonnerCarte(4); -> Mis en commentaire
        RegleContreJoker();
        break;

    }
}
void Jeu::DonnerCarte(int NombreDeCarteADonner)
{
    ChangerTour();
    FairePiocherCarte(NombreDeCarteADonner, JoueurActuel);
    RegleRejouer();
}


void Jeu::RegleRejouer(){
    ChangerSens(); // On change le sens de jeu (passage en horaire/anti-horaire)
    ChangerTour(); // Le switch du tour prend l'ancien joueur
    ChangerSens(); //On re-change le sens du jeu par celui d'avant

}

void Jeu::ChangerSens(){
    SensHoraire = !SensHoraire; // C'est un inverseur, Si SansHoraire = True il faudra sa valeur !différente => Devient false. De même inversemment
}


void Jeu::ChangerCouleur(){
    srand(time(0));
    int random;
    random = rand()%4;
    symb = random;
}


/* ====================================================== LA PIOCHE  ======================================================== */

void Jeu::FairePiocherCarte(int nombre, int joueur) // Fait piocher x cartes au joueur suivant (Valable pour le Joker et le 2
{


    for(int i = 0; i < nombre; i++){
        SiPiocheVide();
        this->joueurs[joueur]->MainJoueur.push_back(this->pioche->donnerCarte());
        pioche->supprimerCarte();
    }
}

void Jeu::SiPiocheVide(){

    if(pioche->Vecteurpioche.empty()){
        Message.PiocheVide();
        RemplirPioche();
        //pioche->voirPioche();
    }
}

void Jeu::RemplirPioche(){
    //size()-1 car on doit garder la dernière carte du tas comme carte courante
    for (int i = 0; i < this->tasdecartes->TasDeCartes.size() - 1; ++i){
        this->pioche->Vecteurpioche.push_back(this->tasdecartes->TasDeCartes.at(i));
    }
    this->tasdecartes->TasDeCartes.erase(tasdecartes->TasDeCartes.begin(), tasdecartes->TasDeCartes.end() -1);
}

/* ====================================================== LE SCORE  ======================================================== */
/* calculer et ajouter score methodes **/


void Jeu::CalculerScoreDesJoueurs(){
    for (int i =0; i< NOMBREJOUEUR ; i++){
        joueurs[i]->CalculerScore();
    }
}

void Jeu::RemettreZeroRound() {

    SensHoraire = true;
    JoueurActuel = 0;
    delete tasdecartes;
    delete pioche;
}

void Jeu::RegleContreJoker(){
    ContreRegleJoker = ! ContreRegleJoker;
    cout << CDEBUG << "Valeur de ContreRegleJoker : " << to_string(ContreRegleJoker) << RCOULEUR << endl;
}

void Jeu::RegleContreDeux(){
    ContreRegleDeux = ! ContreRegleDeux;
    cout << CDEBUG << "Valeur de ContreRegleDeux : " << to_string(ContreRegleDeux) << RCOULEUR << endl;
}
