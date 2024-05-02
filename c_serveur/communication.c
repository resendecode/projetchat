#include "central.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#define MAX_BUFFER_SIZE 200
#define PORT 7777
void *gere_client(void* arg){
  args_t args = *((args_t *) arg);
  int new_socket = args.sock;
  char buffer [MAX_BUFFER_SIZE] = {0};
  char pip[MAX_BUFFER_SIZE] = {0};
  do {
    read(new_socket, buffer,MAX_BUFFER_SIZE);
    write(args.cg[1],buffer,MAX_BUFFER_SIZE);
    //traitement de gestion...
    read(args.gc[0],&pip,MAX_BUFFER_SIZE);
    send(new_socket, pip,MAX_BUFFER_SIZE, 0);
    printf("%s\n", buffer);
    memset(buffer, 0, MAX_BUFFER_SIZE);
    memset(pip, 0, MAX_BUFFER_SIZE);
  }while(strcmp(buffer, "q") != 0);
  close(new_socket);
}
int communication(int cg[2], int gc[2]){
  int server_fd, new_socket, opt;
  args_t args;
  pthread_t tid;
  opt = 1;
  struct sockaddr_in address;
  socklen_t addrlen = sizeof(address);
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }
  //permettre la reutilisation de la socket service
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                 &opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);
  if (bind(server_fd, (struct sockaddr*)&address,
           sizeof(address))
      < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
    if (listen(server_fd, 3) < 0) {
      perror("listen");
      exit(EXIT_FAILURE);
    }
    while (1){
      if ((new_socket
               = accept(server_fd, (struct sockaddr*)&address,
                        &addrlen))
          < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
      }
      // Create a new thread to handle the client
      args.sock = new_socket;
      args.cg[0] = cg[0];
      args.cg[1] = cg[1];
      args.gc[0] = gc[0];
      args.gc[1] = gc[1];
      if (pthread_create(&tid, NULL,gere_client, &args) != 0) {
        perror("pthread_create");
        close(new_socket);
      }
      // Detacher le thread
      pthread_detach(tid);
    }
  close(server_fd);
  return 0;
}
