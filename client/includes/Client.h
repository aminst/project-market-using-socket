#ifndef CLIENT_H
#define CLIENT_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define DEFAULT_SERVER_PORT 5500
#define MAX_BUFFER_SIZE 2048

int get_server_port(int argc, char* argv[]);
void run_client(int port);


#endif