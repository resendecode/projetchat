#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <wait.h>
#include <signal.h>
#include <unistd.h>
//TODO: finir les imports
int main(void){
  //TODO: lancer autres processus, creer segment mémoire partagé, créer file méssages, fermer correctement à la fin
  //creation despace mémoire
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
    if (shmdt(adr1) == -1) {
      printf("shm2.shmdt: %s\n", strerror(errno));
      exit(1);
    }
    //ne pas faire de shmctl car le segmnt est déjà supprimé dans le fils


  return 0;
}