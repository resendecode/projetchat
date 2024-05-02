//
// Created by gabi on 11/03/24.
//

#ifndef PROJETCHAT_CENTRAL_H
#define PROJETCHAT_CENTRAL_H
typedef struct {
    char* nom;
    char* mdp;
} compte_t;
enum requete_enum{connexion,deconnexion,creation,suppression,liste,message};

typedef struct{
    int sock;
    int cg[2];
    int gc[2];
}args_t;
int connectionUdp();
int communication(int cg[2], int gc[2]);
void *gere_client(void *arg);
int gestion(int cg[2], int gc[2]);
int rmi();

int rediff(); //rediffusion d'un message vers tous les clients

#endif //PROJETCHAT_CENTRAL_H
