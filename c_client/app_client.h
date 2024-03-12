#ifndef PROJETCHAT_APP_CLIENT_H
#define PROJETCHAT_APP_CLIENT_H
//ici se trouvent les fonctions d'utilisation
//(les signatures de ces fonctions ne sont pas définitives)
int connecter (char* pseudo, char* mdp);
int deconnecter();
void afficher_liste_utilisateurs();
int creer_compte();
int supprimer_compte();
void quitter_client();
#endif //PROJETCHAT_APP_CLIENT_H
