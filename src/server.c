#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

struct Server server_constructor(int domain, int service, int protocol,
                                 u_long interface, int port, int backlog,
                                 void (*launch)(struct Server *server)) {
  struct Server server;

  server.domain = domain;
  server.service = service;
  server.protocol = protocol;
  server.interface = interface;
  server.port = port;
  server.backlog = backlog;

  server.address.sin_family = domain;
  server.address.sin_addr.s_addr = htonl(server.interface);
  server.address.sin_port = htons(port);

  server.socket = socket(domain, service, protocol);
  server.launch = launch;

  if (server.socket == 0) {
    perror("Socket creation failed.");
    exit(EXIT_FAILURE);
  }

  if (bind(server.socket, (struct sockaddr *)&server.address,
           sizeof(server.address))) {
    perror("Binding failed.");
    exit(EXIT_FAILURE);
  }

  if (listen(server.socket, server.backlog) < 0) {
    perror("Listening failed");
    exit(EXIT_FAILURE);
  }

  printf("Server running on port %d\n", server.port);

  return server;
}
