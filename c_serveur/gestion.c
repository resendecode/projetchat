#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "./central.h"
//
// Created by gabi on 28/04/24.
//
//TODO: donner definition
#define MAX_BUFFER_SIZE 200
int gestion(int cg[2], int gc[2]){
  char buffer[MAX_BUFFER_SIZE];
  while (1){
    memset(&buffer, 0, MAX_BUFFER_SIZE);
    read(cg[0],&buffer, MAX_BUFFER_SIZE);
    switch (buffer[0]) {
      case 's':
        memset(&buffer,0,MAX_BUFFER_SIZE);
        strcpy(buffer,"veuillez saisir votre nom et mot de passe\n");
        write(gc[1], buffer, MAX_BUFFER_SIZE);

        memset(&buffer,0,MAX_BUFFER_SIZE);
        read(cg[0],&buffer, MAX_BUFFER_SIZE);
        printf("ids: %s\n", buffer);
        memset(&buffer, 0, MAX_BUFFER_SIZE);
        strcpy(buffer, "compte créé! \n");
        write(gc[1], buffer, MAX_BUFFER_SIZE);
        break;
      default:
        memset(&buffer,0,MAX_BUFFER_SIZE);
        strcpy(buffer, "ou non!");
        write(gc[1], buffer, MAX_BUFFER_SIZE);
        break;
    }
    printf("%s", buffer);
  }
  return 0;
}