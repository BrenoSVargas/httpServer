#include "src/server.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define BACKLOG 5

void handle_request(struct Server *server) {
  while (1) {
    int new_socket;
    int address_length = sizeof(server->address);

    if ((new_socket =
             accept(server->socket, (struct sockaddr *)&server->address,
                    (socklen_t *)&address_length)) < 0) {
      perror("Listening failed");
      exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE] = {0};

      if (read(new_socket, buffer, BUFFER_SIZE - 1) < 0) {
      perror("Failed while reading the buffer.");
      exit(EXIT_FAILURE);
    }

    printf("Received request: \n%s\n", buffer);

    const char *response = "HTTP/1.1 200 OK\nContent-Type: "
                           "text/html\n\n<html><body><h1>Hello, HTTP "
                           "Server!</h1></body></html>";
    write(new_socket, response, strlen(response));
    close(new_socket);
  }
}

int main() {
  struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY,
                                            PORT, BACKLOG, handle_request);

  handle_request(&server);
  return 0;
}
