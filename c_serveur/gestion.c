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
  memset(&buffer, 0, MAX_BUFFER_SIZE);
  read(cg[0],&buffer, MAX_BUFFER_SIZE);
  write(gc[1],"Gestionnn :p\n", MAX_BUFFER_SIZE);
  printf("%s", buffer);
  return 0;
}