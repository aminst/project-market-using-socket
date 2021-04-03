#ifndef SERVER_H
#define SERVER_H

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Utils.h"
#include "Project.h"

#define DEFAULT_SERVER_PORT 5500
#define MAX_CONNECTIONS 50
#define MAX_BUFFER_SIZE 2048
#define LINE_BREAKER "***************************************\n"

int get_random_port();
void send_udp_port_to_group(int project_id, Project* projects);

int get_server_port(int argc, char* argv[]);
void run_server_on_port(int port);
int run_tcp_socket(int port);

void write_server_startup_msg(int port);
void send_available_projects_info(int fd, Project* projects);

#endif
