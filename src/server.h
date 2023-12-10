#ifndef server_h
#define server_h

#include <netinet/in.h>
#include <sys/types.h>

struct Server {
  int domain;
  int service;
  int protocol;
  u_long interface;
  int port;
  int backlog;

  int socket;
  struct sockaddr_in address;

  void (*launch)(struct Server *server);
};

struct Server server_constructor(int domain, int service, int protocol,
                                 u_long interface, int port, int backlog,
                                 void (*launch)(struct Server *server));

#endif // !server_h
