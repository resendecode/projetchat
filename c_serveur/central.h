//
// Created by gabi on 11/03/24.
//

#ifndef PROJETCHAT_CENTRAL_H
#define PROJETCHAT_CENTRAL_H
struct compte_t{
    char* nom;
    char* mdp;
};
int communication();
int gestion();
int rmi();

int rediff(); //rediffusion d'un message vers tous les clients

#endif //PROJETCHAT_CENTRAL_H
