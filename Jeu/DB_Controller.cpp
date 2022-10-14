#include "DB_Controller.hpp"

static int callbackScores(void *data, int argc, char **argv, char **azColName){
    int i;
    if(data) // ajout d'une condition pour éviter le "(null): " au début de chaque réponse/callback
        fprintf(stderr, "%s: ", (const char*)data);

    int loop = 0;
    for (i = 0; i < argc; i++) {
        // Cette boucle permet d'organiser la syntaxe console au fil des callback qui sont reçus pour la Requête SQL 1
        if (loop == 4) loop = 1;
        else loop++;

        switch (loop) {
            case 1: printf("%s (", argv[i] ? argv[i] : "NULL"); break;
            case 2: printf("Partie %s) - ", argv[i] ? argv[i] : "NULL"); break;
            case 3: printf("Joueur %s, ", argv[i] ? argv[i] : "NULL"); break;
            case 4: printf("%s points", argv[i] ? argv[i] : "NULL"); break;
            default: break;
        }

    }

    printf("\n");
    return 0;
}


/* Affichage console pour la Requête 2 (nombre de victoires pour chaque joueur) */
static int CallBackVictoire(void *data, int argc, char **argv, char **azColName) {
    int i;
    if (data) // ajout d'une condition pour éviter le "(null): " au début de chaque réponse
        fprintf(stderr, "%s: ", (const char *) data);

    int loop = 0;

    for (i = 0; i < argc; i++) {
        // Cette boucle permet d'organiser la syntaxe console au fil des callback qui sont reçus pour la Requête SQL 2
        if (loop == 2) loop = 1;
        else loop++;

        switch (loop) {
            case 1: printf("%s : ", argv[i] ? argv[i] : "NULL"); break;
            case 2: printf("%s victoire(s)", argv[i] ? argv[i] : "NULL"); break;
            default: break;
        }
    }

    printf("\n");
    return 0;
}

static int callbackCartesJouees(void *data, int argc, char **argv, char **azColName) {
    int i;
    if (data) // ajout d'une condition pour éviter le "(null): " au début de chaque réponse
        fprintf(stderr, "%s: ", (const char *) data);

    int loop = 0;
    string cardvalue = "";

    for (i = 0; i < argc; i++) {
        // Cette boucle permet d'organiser la syntaxe console au fil des callback qui sont reçus pour la Requête SQL 3
        if (loop == 3) loop = 1;
        else loop++;

        switch (loop) {
            case 1: printf("La carte : %s ", argv[i] ? argv[i] : "NULL"); break;
            case 2: printf("a été jouée un total de %s fois ", argv[i] ? argv[i] : "NULL"); break;
            case 3: printf("et son taux de jeu est de %s pourcent", argv[i] ? argv[i] : "NULL"); break;
            default: break;
        }
    }
    printf("\n");
    return 0;
}


/* CODE AJOUTE A L'EXAMEN */
static int CallBackMoyenneRound(void *data, int argc, char **argv, char **azColName) {
    if (data) fprintf(stderr, "%s: ", (const char *) data);
    printf("Il y a %s rounds en moyenne par partie: ", argv[2] ? argv[2] : "NULL");
    printf("\n");
    return 0;
}

static int CallBackBestWinner(void *data, int argc, char **argv, char **azColName) {
    if (data) fprintf(stderr, "%s: ", (const char *) data);

     int i;
     int loop = 0;

    for (i = 0; i < argc; i++) {
        // Cette boucle permet d'organiser la syntaxe console au fil des callback qui sont reçus pour la Requête SQL 2
        if (loop == 2) loop = 1;
        else loop++;

        switch (loop) {
            case 1: printf("Le plus grand gagnant est le joueur %s ", argv[i] ? argv[i] : "NULL"); break;
            case 2: printf("avec %s parties gagnées", argv[i] ? argv[i] : "NULL"); break;
            default: break;
        }
    }
    printf("\n");
    return 0;

}


static int callbackMostSymbol(void *data, int argc, char **argv, char **azColName) {
    int i;
    if (data) // ajout d'une condition pour éviter le "(null): " au début de chaque réponse
        fprintf(stderr, "%s: ", (const char *) data);

    int loop = 0;
    string cardvalue = "";

    for (i = 0; i < argc; i++) {
        // Cette boucle permet d'organiser la syntaxe console au fil des callback qui sont reçus pour la Requête SQL 3
        if (loop == 2) loop = 1;
        else loop++;

        switch (loop) {
            case 1: printf("Le taux de  %s ", argv[i] ? argv[i] : "NULL"); break;
            case 2: printf("est de  %s pourcent", argv[i] ? argv[i] : "NULL"); break;
            default: break;
        }
    }
    printf("\n");
    return 0;
}



/* Comme pour de la programmation Web, on spécifie une ouverture et fermeture de base
 * de données */

int DB_Controller::Ouvrir_DB() {
    return (sqlite3_open("database.db", &_DATABASE));
}

void DB_Controller::Fermer_DB() {
    sqlite3_close(_DATABASE); //Equivalant à mysql_close
}

void DB_Controller::CreerTableGames() {
    //Constant car ces lignes n'obtiennent pas de valeur extérieure et restent statiques
    const char *SQL_Query = "CREATE TABLE IF NOT EXISTS Games (Game_ID INTEGER NOT NULL, DateTime TEXT NOT NULL, PRIMARY KEY(Game_ID AUTOINCREMENT));";
    int result = sqlite3_exec(_DATABASE, SQL_Query, NULL, 0, &_MessageErreur);
    if (result) { // On recoit un "code erreur" 0 = OK | 1 = Erreur
        cout << ROUGE << "Erreur lors de la creation de la table 'Games' : " << _MessageErreur << RCOULEUR << endl;
        sqlite3_free(_MessageErreur);
    } else {
        cout << VERT << "La table [Games] a été crée avec succès." << RCOULEUR << endl;
    }
}

void DB_Controller::CreerTableCartes() {
    //Constant car ces lignes n'obtiennent pas de valeur extérieure et restent statiques
    const char *SQL_Query = "CREATE TABLE IF NOT EXISTS Cards ( Cards_ID INTEGER UNIQUE, Game_ID INTEGER, Players_ID INTEGER, Valeur TEXT, PRIMARY KEY(Cards_ID AUTOINCREMENT), FOREIGN KEY(Game_ID) REFERENCES Games(Game_ID), FOREIGN KEY (Players_ID) REFERENCES Players(Players_ID));";
    int result = sqlite3_exec(_DATABASE, SQL_Query, NULL, 0, &_MessageErreur);
    if (result) { // On recoit un "code erreur" 0 = OK | 1 = Erreur
        cout << ROUGE << "Erreur lors de la creation de la table 'Cards' : " << _MessageErreur << RCOULEUR << endl;
        sqlite3_free(_MessageErreur);
    } else {
        cout << VERT << "La table [Cards] a été crée avec succès." << RCOULEUR << endl;
    }
}

void DB_Controller::CreerTableJoueurs() {
    // Constant car ces lignes n'obtiennent pas de valeur extérieure et restent statiques
    const char *SQL_Query = "CREATE TABLE IF NOT EXISTS Players ( Players_ID INTEGER UNIQUE, NamePlayer TEXT, Wins INTEGER DEFAULT 0, PRIMARY KEY(Players_ID AUTOINCREMENT) );";
    int result = sqlite3_exec(_DATABASE, SQL_Query, NULL, 0, &_MessageErreur);
    if (result) { // On recoit un "code erreur" 0 = OK | 1 = Erreur
        cout << ROUGE << "Erreur lors de la creation de la table 'Players' : " << _MessageErreur << RCOULEUR << endl;
        sqlite3_free(_MessageErreur);
    } else {
        cout << VERT << "La table [Players] a été crée avec succès." << RCOULEUR << endl;
    }
}


void DB_Controller::CreerTableScore() {
    //Constant car ces lignes n'obtiennent pas de valeur extérieure et restent statiques
    const char *SQL_Query = "CREATE TABLE IF NOT EXISTS Score ( Score_ID INTEGER UNIQUE, Game_ID INTEGER, Type TEXT, Players_ID INTEGER, Score INTEGER, FOREIGN KEY(Game_ID) REFERENCES Games(Game_ID), PRIMARY KEY(Score_ID AUTOINCREMENT), FOREIGN KEY(Players_ID) REFERENCES Players (Players_ID));";
    int result = sqlite3_exec(_DATABASE, SQL_Query, NULL, 0, &_MessageErreur);
    if (result) { // On recoit un "code erreur" 0 = OK | 1 = Erreur
        cout << ROUGE << "Erreur lors de la creation de la table 'Score' : " << _MessageErreur << RCOULEUR << endl;
        sqlite3_free(_MessageErreur);
    } else {
        cout << VERT << "La table [Score] a été crée avec succès." << RCOULEUR << endl;
    }
}

void DB_Controller::EcrireGames() {
    int OpenDB = Ouvrir_DB();
    if (OpenDB) {
        cout << ROUGE << "Erreur lors de l'ouverture de la base de données' : " << OpenDB << RCOULEUR << endl;

    }

    char RequeteSQL[256];
    sprintf(RequeteSQL, "INSERT INTO Games(DATETIME) VALUES (datetime('now', 'localtime'))");
    OpenDB = sqlite3_exec(_DATABASE, RequeteSQL, NULL, 0, &_MessageErreur);
    if (OpenDB) {
        cout << ROUGE << "Erreur lors de l'insertion des données : " << OpenDB << RCOULEUR << endl;
        sqlite3_free(_MessageErreur);
    }
    Fermer_DB();

}

void DB_Controller::EcrireCards(int JoueurActuel, Carte carte) {
    string _symbole;
    string _face;

    /* Les caractères spéciaux (symboles) ne sont pas correctement transcrit dans la base de donnée
     * il faut donc "transformer" les valeurs avant ajout*/

    switch (carte.GetSymbole()) {
        case 0: _symbole = " de Pique"; break;
        case 1: _symbole = " de Coeur"; break;
        case 2: _symbole = " de Trèfle"; break;
        case 3: _symbole = " de Carreau"; break;

    }

    switch(carte.GetValeurFace()){
        case AS: _face = "As"; break;
        case DAME: _face = "Dame"; break;
        case ROI: _face = "Roi"; break;
        case VALET: _face = "Valet"; break;
        case JOKER: _face = "Joker"; break;
        default: _face = to_string(carte.GetValeurFace()); break;
    }
    //string _Carte = to_string(carte.GetValeurFace()) + _symbole;
    string global = _face + _symbole;

    int OpenDB = Ouvrir_DB();
    if (OpenDB) {
        cout << ROUGE << "Erreur lors de l'ouverture de la base de données' : " << OpenDB << RCOULEUR << endl;

    }
    char RequeteSQL[256];


    sprintf(RequeteSQL,
            "INSERT INTO Cards(Game_ID, Players_ID, Valeur) VALUES ((SELECT MAX(Game_ID) FROM Games), (SELECT Players_ID FROM Players WHERE NamePlayer = 'Joueur %d') ,'%s') ",
            (JoueurActuel+1),global.c_str());
    OpenDB = sqlite3_exec(_DATABASE, RequeteSQL, NULL, 0, &_MessageErreur);
    if (OpenDB) {
        cout << ROUGE << "Erreur lors de l'insertion des données : " << OpenDB << RCOULEUR << endl;
        sqlite3_free(_MessageErreur);

    }
    Fermer_DB();

}

void DB_Controller::EcrireJoueurs(Joueur *joueurs[NOMBREJOUEUR]) {
    int OpenDB = Ouvrir_DB();
    if (OpenDB) {
        cout << ROUGE << "Erreur lors de l'ouverture de la base de données' : " << OpenDB << RCOULEUR << endl;

    }
    for (int i = 0; i < NOMBREJOUEUR; i++) {
        char RequeteSQL[256];
        sprintf(RequeteSQL, "INSERT INTO Players (NamePlayer) SELECT ('%s')"
                            "WHERE NOT EXISTS (SELECT 1 FROM Players WHERE NamePlayer='%s');",
                joueurs[i]->Getnom().c_str(),
                joueurs[i]->Getnom().c_str());
        OpenDB = sqlite3_exec(_DATABASE, RequeteSQL, NULL, 0, &_MessageErreur);


        if (OpenDB) {
            cout << ROUGE << "Erreur lors de l'insertion des données : " << OpenDB << RCOULEUR << endl;
            sqlite3_free(_MessageErreur);
        }
    }
    Fermer_DB();

}

void DB_Controller::EcrireScore(Joueur *joueurs[NOMBREJOUEUR], string type) {
    int OpenDB = Ouvrir_DB();
    if (OpenDB) {
        cout << ROUGE << "Erreur lors de l'ouverture de la base de données' : " << OpenDB << RCOULEUR << endl;

    }

    for (int i = 0; i < NOMBREJOUEUR; i++) {
        char RequeteSQL[256];
        sprintf(RequeteSQL,
                "INSERT INTO Score (Game_ID, Type, Players_ID, Score) VALUES ((SELECT MAX(Game_ID) FROM Games),'%s',(SELECT Players_ID FROM Players WHERE NamePlayer = '%s'), '%d')",
                type.c_str(), joueurs[i]->Getnom().c_str(), joueurs[i]->GetScore());
        OpenDB = sqlite3_exec(_DATABASE, RequeteSQL, NULL, 0, &_MessageErreur);


        if (OpenDB) {
            cout << ROUGE << "Erreur lors de l'insertion des données : " << OpenDB << RCOULEUR << endl;
            sqlite3_free(_MessageErreur);
        }
    }
    Fermer_DB();
}

void DB_Controller::UpdateTablePlayersForWinner(Joueur * Gagnant) // Met à jour la table 'Players' pour incrémenter le nombre de victoires du gagnant
    {
        int OpenDB = Ouvrir_DB(); // Ouverture de la DB et réception d'un code
        if (OpenDB)
            cerr << "Erreur durant l'ouverture de la DB, code : " << OpenDB << endl;
        char SQLRequest[256];

        sprintf(SQLRequest,
                "UPDATE Players SET Wins = Wins+1 WHERE NamePlayer = '%s';",
                Gagnant->Getnom().c_str());

        OpenDB = sqlite3_exec(_DATABASE, SQLRequest, NULL, 0, &_MessageErreur); // Envoi de la requête, réception d'un code réponse
        if (OpenDB) {
            cout << "Erreur lors de l'insertion dans la table 'Games' : " << _MessageErreur << endl;
            sqlite3_free(_MessageErreur);
        }
        Fermer_DB();
    }



void DB_Controller::SelectScore(){
    int OpenDB = Ouvrir_DB();
    if (OpenDB) {
        cout << ROUGE << "Erreur lors de l'ouverture de la base de données' : " << OpenDB << RCOULEUR << endl;
    }
    string RequeteSQL;

    RequeteSQL = "SELECT Games.DateTime, Score.Game_ID, Score.Players_ID, Score.score  FROM Score INNER JOIN Games ON Score.Game_ID = Games.Game_ID WHERE Score.Type='Partie' ORDER By DateTime ASC, Score ASC";
    OpenDB = sqlite3_exec(_DATABASE, RequeteSQL.c_str(), callbackScores, 0, &_MessageErreur);

    if (OpenDB) {
        cout << ROUGE << "Erreur lors de la lecture des données : " << OpenDB << RCOULEUR << endl;
        sqlite3_free(_MessageErreur);
    }
    Fermer_DB();
}


void DB_Controller::SelectVictoire(){
    int OpenDB = Ouvrir_DB();
    if (OpenDB) {
        cout << ROUGE << "Erreur lors de l'ouverture de la base de données' : " << OpenDB << RCOULEUR << endl;
    }
    string RequeteSQL;

    RequeteSQL = "SELECT NamePlayer, Wins FROM Players";
    OpenDB = sqlite3_exec(_DATABASE, RequeteSQL.c_str(), CallBackVictoire, 0, &_MessageErreur);

    if (OpenDB) {
        cout << ROUGE << "Erreur lors de la lecture des données : " << OpenDB << RCOULEUR << endl;
        sqlite3_free(_MessageErreur);
    }

    Fermer_DB();
}

void DB_Controller::SelectCartesJouees() {
    int OpenDB = Ouvrir_DB();
    if (OpenDB) {
        cout << ROUGE << "Erreur lors de l'ouverture de la base de données' : " << OpenDB << RCOULEUR << endl;
    }
    string RequeteSQL;

    RequeteSQL =
            "SELECT Valeur, COUNT(Valeur) AS NbreFoisCarteJouee, (COUNT(Valeur)/MAX(Games.Game_ID))AS Taux FROM Cards, Games Group BY Valeur ORDER BY Valeur ASC";
    OpenDB = sqlite3_exec(_DATABASE, RequeteSQL.c_str(), callbackCartesJouees, 0, &_MessageErreur);

    if (OpenDB) {
        cout << ROUGE << "Erreur lors de la lecture des données : " << OpenDB << RCOULEUR << endl;
        sqlite3_free(_MessageErreur);
    }
    Fermer_DB();
}


/** CODE AJOUTE POUR L'EXAMEN */
/** Obtenir la moyenne de round **/

void DB_Controller::SelectGetRounds() {
    int OpenDB = Ouvrir_DB();
    if (OpenDB) {
        cout << ROUGE << "Erreur lors de l'ouverture de la base de données' : " << OpenDB << RCOULEUR << endl;
    }
    string RequeteSQL;

    RequeteSQL =
            "SELECT COUNT(Type)/4 as nombreRound, COUNT(DISTINCT Game_ID)as nombrePartie, ROUND((COUNT(Type)/4)/(COUNT(DISTINCT Game_ID))) as moyenne FROM score ";
    OpenDB = sqlite3_exec(_DATABASE, RequeteSQL.c_str(), CallBackMoyenneRound, 0, &_MessageErreur);

    if (OpenDB) {
        cout << ROUGE << "Erreur lors de la lecture des données : " << OpenDB << RCOULEUR << endl;
        sqlite3_free(_MessageErreur);
    }
    Fermer_DB();
}

/* Obtenir le plus grand gagnant */


void DB_Controller::SelectGetBestWinner() {
    int OpenDB = Ouvrir_DB();
    if (OpenDB) {
        cout << ROUGE << "Erreur lors de l'ouverture de la base de données' : " << OpenDB << RCOULEUR << endl;
    }
    string RequeteSQL;

    RequeteSQL =
            "SELECT Players_ID, Wins as Victoires from Players  GROUP BY Wins ORDER BY Victoires DESC LIMIT 1";
    OpenDB = sqlite3_exec(_DATABASE, RequeteSQL.c_str(), CallBackBestWinner, 0, &_MessageErreur);

    if (OpenDB) {
        cout << ROUGE << "Erreur lors de la lecture des données : " << OpenDB << RCOULEUR << endl;
        sqlite3_free(_MessageErreur);
    }
    Fermer_DB();
}

/* Taux de couleur (symbole) la plus jouée
 *
 * Comme dans notre base de donnée nous stockons la carte en un string (nous avions eu des problèmes
 * avec les caractères spéciaux, je tronque la string pour n'avoir que le symbole et non la face
 * mais malheureusement cela ne donnera jamais le résultat attendu
 *
 *
 * */

void DB_Controller::SelectMostPlayedSymbol() {
    int OpenDB = Ouvrir_DB();
    if (OpenDB) {
        cout << ROUGE << "Erreur lors de l'ouverture de la base de données' : " << OpenDB << RCOULEUR << endl;
    }
    string RequeteSQL;

    RequeteSQL =
            "SELECT SUBSTR(Valeur, 4) as ValeurSoustraite, (COUNT(Valeur)/MAX(Games.Game_ID))AS Taux FROM Cards, Games Group BY Valeur ORDER BY Valeur ASC";
    OpenDB = sqlite3_exec(_DATABASE, RequeteSQL.c_str(), callbackMostSymbol, 0, &_MessageErreur);

    if (OpenDB) {
        cout << ROUGE << "Erreur lors de la lecture des données : " << OpenDB << RCOULEUR << endl;
        sqlite3_free(_MessageErreur);
    }
    Fermer_DB();
}


