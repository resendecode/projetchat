#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "./central.h"
//
// Created by gabi on 28/04/24.
//
#define PORT 8888
#define MAX_BUFFER_SIZE 200
int serveurUdp(){
  int sockfd;
  struct sockaddr_in server_addr, client_addr;
  char buffer[MAX_BUFFER_SIZE];

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&server_addr, 0, sizeof(server_addr));
  memset(&client_addr, 0, sizeof(client_addr));

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Bind failed");
    exit(EXIT_FAILURE);
  }


  while (1) {
    socklen_t len = sizeof(client_addr);

    int bytes_received = recvfrom(sockfd, (char *)buffer, MAX_BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&client_addr, &len);
    buffer[bytes_received] = '\0';
    printf("Message du client: %s\n", buffer);

    sendto(sockfd, "Reçu", strlen("Reçu"), 0, (const struct sockaddr *)&client_addr, len);
  }

  close(sockfd);
  return 0;
}
int gestion(int cg[2], int gc[2]){
  int sock_service, sock;
  char buffer[MAX_BUFFER_SIZE];
  while (1){
    memset(&buffer, 0, MAX_BUFFER_SIZE);
    read(cg[0],&buffer, MAX_BUFFER_SIZE);
    if(strlen(buffer)!=1){
        memset(&buffer,0,MAX_BUFFER_SIZE);
        strcpy(buffer,"Format invalide!\n");
        write(gc[1], buffer, MAX_BUFFER_SIZE);
    }
    else{
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
    }

    printf("%s", buffer);
  }
  return 0;
}