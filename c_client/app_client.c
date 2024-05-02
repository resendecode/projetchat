#include "app_client.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#define MAX_BUFFER_SIZE 200
int deconnecter(compte_t* compte){
  printf("la session s'est terminé! \n");
  return 0;
}
//fonction créatrice de socket locale
int creerSocket() {
  // descripteur de la socket locale
  int sock = socket(AF_INET, SOCK_STREAM, 0); // TCP
  if (sock == -1) {
    perror("erreur socket");
    return -1;
  }
  return sock;
}
int connection(int sock){
  // adresse de la socket coté serveur
  static struct sockaddr_in addr_serveur;
  char buffer[MAX_BUFFER_SIZE] = {0};
  char message[MAX_BUFFER_SIZE] = {0};
  //on spécifie l'adresse locale comme adresse de la machine dont on souhaite se connecter dessus
  //(on utilise inet_pton plutôt que "gethostbyname" par souci de simplicité)
  if(inet_pton(AF_INET, "127.0.0.1", &addr_serveur.sin_addr) <= 0) {
    perror("Adresse invalide / Adresse non supportée");
    exit(EXIT_FAILURE);
  }
  // création adresse socket destinatrice
  addr_serveur.sin_family = AF_INET;
  addr_serveur.sin_port = htons(7777);

  if (connect(sock, (struct sockaddr *)&addr_serveur, sizeof(struct sockaddr_in)) == -1) {
    perror("erreur connexion serveur");
    exit(1);
  }
  do {
    printf("que voulez vous faire?\n"
           "s: se connecter\n"
           "e: envoyer un message\n"
           "a: afficher la liste d'utilisateurs\n"
           "c: créér un nouveau compte\n"
           "d: se déconnecter\n"
           "q: quitter l'application \n-");
    fgets(message, MAX_BUFFER_SIZE, stdin);
    //enlève le final du string saisi
    // Remove newline character from fgets
    message[strcspn(message, "\n")] = '\0';
    // Send message to server
    send(sock, message, strlen(message), 0);
    printf("Message sent to server: %s\n", message);
    memset(buffer,0, MAX_BUFFER_SIZE );
    int nbytes = read(sock, buffer, MAX_BUFFER_SIZE);
    buffer[nbytes] = '\0';
    printf("message reçu: %s and length: %d", buffer, MAX_BUFFER_SIZE);
  }while(strcmp(message,"q") !=0);
  return 0;
}
compte_t* creer_compte(char* nom, char* mdp){
  compte_t* compte = (compte_t*) malloc(sizeof(compte_t));
  strcpy(compte->nom, nom);
  strcpy(compte->mdp, mdp);
  return compte;
}
int effacer_compte(compte_t* compte){
  free(compte);
  return 0;
}
int main(void){
  compte_t* compte = creer_compte("toto", "abc");
  mkfifo("pipes/vers_aff", 0666); // Pipe communication à la fenêtre d'affichage
  mkfifo("pipes/vers_cli", 0666); // Pipe de retour

  //nous lanceons la socket client au départ
  int sock = creerSocket();
  //commande provisoire pour ouvrir fenêtre avec messages
  //system("gnome-terminal");
  connection(sock);
  //tuyau qui doit être lancé pour la comm aficheur client
  deconnecter(compte);
  effacer_compte(compte);
  return 0;
}