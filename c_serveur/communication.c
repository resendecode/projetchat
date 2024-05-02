#include "central.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 7777
void *gere_client(void* arg){
  int new_socket = *((int *)arg);
  char buffer [200] = {0};
  char* hello = "Hello from server";
  do {
    read(new_socket, buffer,
                   sizeof(char[200]));
    printf("%s\n", buffer);
    memset(buffer, 0, sizeof(buffer));
    send(new_socket, hello, strlen(hello), 0);

  }while(strcmp(buffer, "q") != 0);
  // closing the connected socket
  close(new_socket);
}
int communication(){
  int server_fd, new_socket, opt;
  pthread_t tid;
  opt = 1;
  struct sockaddr_in address;
  socklen_t addrlen = sizeof(address);
  // Creating socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }
// Set socket options to allow multiple connections
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
      if (pthread_create(&tid, NULL,gere_client, &new_socket) != 0) {
        perror("pthread_create");
        close(new_socket);
      }
      // Detach the thread to avoid memory leaks
      pthread_detach(tid);
    }

  // closing the listening socket
  close(server_fd);
  return 0;
}
