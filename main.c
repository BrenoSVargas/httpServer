#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_request(int client_socket) {
  char buffer[BUFFER_SIZE] = {0};
  if (read(client_socket, buffer, BUFFER_SIZE - 1) < 0) {
    perror("Failed while reading the buffer.");
    exit(EXIT_FAILURE);
  }

  printf("Received request: \n%s\n", buffer);

  const char *response =
      "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><h1>Hello, HTTP "
      "Server!</h1></body></html>";
  write(client_socket, response, strlen(response));
  close(client_socket);
}

int main() {
  int server_fd;
  int client_socket;

  struct sockaddr_in address;

  int addr_length = sizeof(address);

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("Socket creation failed.");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))) {
    perror("Binding failed.");
    exit(EXIT_FAILURE);
  }

  if (listen(server_fd, 3) < 0) {
    perror("Listening failed");
    exit(EXIT_FAILURE);
  }

  printf("Server running on port %d\n", PORT);

  while (1) {
    if ((client_socket = accept(server_fd, (struct sockaddr *)&address,
                                (socklen_t *)&addr_length)) < 0) {
      perror("Listening failed");
      exit(EXIT_FAILURE);
    }

    handle_request(client_socket);
  }

  return 0;
}
