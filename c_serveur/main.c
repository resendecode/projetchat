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

int main(void){
  int cg[2]; //pipe communication =>gestion
  int gc[2]; //pipe gestion => communication
  if(pipe(cg) == -1) return 1;
  if(pipe(gc)== -1) return 1;

  printf("le make a marché \n");
  pid_t commu_pid, gesti_pid, rmi_pid;
  commu_pid = fork();
  if (commu_pid<0){
    perror("fork");
    abort();
  }
  else if(commu_pid ==0){
    printf("commu! \n");
    communication(cg,gc);
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
      gestion(cg,gc);
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
    //ne pas faire "no hang" dans le waitpid car cela empêche le serveur de marcher correctement
    //solution provisoire pour l'attente de la fin des 3 processus
    wait(NULL);
  wait(NULL);
  wait(NULL);
  return 0;
}