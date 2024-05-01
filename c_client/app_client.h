#ifndef PROJETCHAT_APP_CLIENT_H
#define PROJETCHAT_APP_CLIENT_H
//ici se trouvent les fonctions d'utilisation
//(les signatures de ces fonctions ne sont pas définitives)
typedef struct{
    char nom[90];
    char mdp[90];
} compte_t;
int connecter (compte_t* compte);
int deconnecter(compte_t* compte);
void afficher_liste_utilisateurs();
compte_t *creer_compte(char* nom, char* mdp);
int supprimer_compte(compte_t* compte);
void quitter_client();
#endif //PROJETCHAT_APP_CLIENT_H
