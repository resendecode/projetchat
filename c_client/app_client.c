#include "app_client.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#import <arpa/inet.h>
#include <sys/stat.h>
int CreerSocket(char* addr, int port) {
  // adresse de la socket coté serveur
  static struct sockaddr_in addr_serveur;
  // descripteur de la socket locale
  int sock = socket(AF_INET, SOCK_STREAM, 0); // TCP
  if (sock == -1) {
    perror("erreur socket");
    return -1;
  }
  //on spécifie l'adresse locale comme adresse de la machine dont on souhaite se connecter dessus
  //(on utilise inet_pton plutôt que "gethostbyname" par souci de simplicité)
  if(inet_pton(AF_INET, "127.0.0.1", &addr_serveur.sin_addr) <= 0) {
    perror("Adresse invalide / Adresse non supportée");
    exit(EXIT_FAILURE);
  }
  // création adresse socket destinatrice
  addr_serveur.sin_family = AF_INET;
  addr_serveur.sin_port = htons(port);
  if (connect(sock, (struct sockaddr *)&addr_serveur, sizeof(struct sockaddr_in)) == -1) {
    perror("erreur connexion serveur");
    exit(1);
  }
  return sock;
}
struct compte_t* creer_compte(char* nom, char* mdp){
  struct compte_t* compte = (struct compte_t*) malloc(sizeof(struct compte_t));
  compte->nom = nom;
  compte->mdp = mdp;
  return compte;
}
int main(void){
  struct compte_t* compte = creer_compte("toto", "abc");
  mkfifo("pipes/vers_aff", 0666); // Pipe communication à la fenêtre d'affichage
  mkfifo("pipes/vers_cli", 0666); // Pipe de retour

  //nous lanceons la socket client et le connectons au serveur
  CreerSocket("127.0.0.1", 8080);
  //commande provisoire pour ouvrir fenêtre avec messages
  system("gnome-terminal");
  //tuyau qui doit être lancé pour la comm aficheur client
  deconnecter(compte);
  return 0;
}