#include "./central.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <wait.h>
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/stat.h>

int traiter(int sock) {
  char reponse[200];
  char message[1];
  // la connexion est établie, on attend les données envoyées par le client
  read(sock, reponse, 200);
  // affichage du message reçu
  printf("%s\n", reponse);
  scanf("%s", message);
  // écrit la demande
  send(sock,message, strlen(message)+1, 0);
  // lit la réponse
  memset(reponse,0,sizeof(reponse)); // Vide la variable reponse
  recv(sock, reponse, 200, 0);
  printf("%s\n", reponse);
  return 1;
}

int main(void){
  //TODO: lancer autres processus, creer segment mémoire partagé, créer file méssages, fermer correctement à la fin

  printf("le make a marché \n");
  pid_t commu_pid, gesti_pid, rmi_pid;
  commu_pid = fork();
  if (commu_pid<0){
    perror("fork");
    abort();
  }
  else if(commu_pid ==0){
    printf("commu! \n");
    communication();
    exit(0);
  }
  else{
    gesti_pid = fork();
    if (gesti_pid<0){
      perror("fork");
      abort();
    }
    else if(gesti_pid ==0){
      printf("gestion! \n");
      gestion();
      exit(0);
    }
    else{
      rmi_pid = fork();
      if (rmi_pid<0){
        perror("fork");
        abort();
      }
      else if(rmi_pid ==0){
        printf("rmi! \n");
        rmi();
        exit(0);
      }
    }
  }
  
  char* adr1;
  int shmid, cle = 5;
    //ne pas oublier ipc_creat
    if ((shmid = shmget(cle, sizeof(int), IPC_CREAT|0600)) == -1) {
      printf("shm2.shmget: %s\n", strerror(errno));
      exit(1);
    }
    if ((adr1 = (char *)shmat(shmid, NULL, 0)) == (char *)-1) {
      printf("shm2.shmat: %s\n", strerror(errno));
      exit(1);
    }
    //suppression segment
    if (shmdt(adr1) == -1) {
      printf("shm2.shmdt: %s\n", strerror(errno));
      exit(1);
    }
    //ne pas faire de shmctl car le segmnt est déjà supprimé dans le fils
    int status_commu, status_gest, status_rmi;
  waitpid(commu_pid,&status_commu, WNOHANG);
  waitpid(gesti_pid,&status_gest, WNOHANG);
  waitpid(rmi_pid,&status_rmi, WNOHANG);
  return 0;
}