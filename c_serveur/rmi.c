#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "./central.h"
//
// Created by gabi on 28/04/24.
//
#define PORT 8888
#define MAX_BUFFER_SIZE 200
int connectionUdp(){
  int sockfd;
  struct sockaddr_in server_addr;
  char buffer[MAX_BUFFER_SIZE] = "Hello from client";

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&server_addr, 0, sizeof(server_addr));

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  sendto(sockfd, (const char *)buffer, strlen(buffer), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));
  printf("Message de test au serveur: %s\n", buffer);

  memset(buffer, 0, sizeof(buffer));
  recvfrom(sockfd, (char *)buffer, MAX_BUFFER_SIZE, MSG_WAITALL, NULL, NULL);
  printf("réponse: %s\n", buffer);

  close(sockfd);
  return 0;
}

int rmi(){
  sleep(1); //pour s'assurer que le reste des parties sont lancées
  connectionUdp();
  return 0;
}