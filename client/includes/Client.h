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

#include "Utils.h"

#define DEFAULT_SERVER_PORT 5500
#define MAX_BUFFER_SIZE 2048
#define LINE_BREAKER "***************************************\n"

int get_server_port(int argc, char* argv[]);
void run_client(int port);
int connect_to_server(int port);
void send_selected_project_number_to_server(int client_fd);

int init_udp(char* udp_port_str, struct sockaddr_in udp_sin);
void run_project_market(int my_id, int udp_fd, struct sockaddr_in udp_sin);

void write_port_id_msg(char* port, char* id);

#endif