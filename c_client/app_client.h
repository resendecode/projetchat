#ifndef PROJETCHAT_APP_CLIENT_H
#define PROJETCHAT_APP_CLIENT_H
//ici se trouvent les fonctions d'utilisation
//(les signatures de ces fonctions ne sont pas définitives)
struct compte_t{
    char* nom;
    char* mdp;
};
int connecter (struct compte_t* compte);
int deconnecter();
void afficher_liste_utilisateurs();
struct compte_t *creer_compte(char* nom, char* mdp);
int supprimer_compte(struct compte_t* compte);
void quitter_client();
#endif //PROJETCHAT_APP_CLIENT_H
