#include "Client.h"

int get_server_port(int argc, char* argv[])
{
    if (argc != 2)
        return DEFAULT_SERVER_PORT;
    else
    {
        return strtol(argv[1], NULL, 10);
    }
}

void run_client(int port)
{
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1)
    {
        const char* socket_creation_error_msg = "Socket Creation Error!\n";
        write(1, socket_creation_error_msg, strlen(socket_creation_error_msg));
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in server_sin;
    server_sin.sin_port = htons(port);
    server_sin.sin_addr.s_addr = inet_addr("127.0.0.1");;
    server_sin.sin_family = AF_INET;

    if (connect(client_fd,(struct sockaddr*)&server_sin, sizeof(server_sin)) == -1)
    {
        const char* connect_error_msg = "Connect Error!\n";
        write(1, connect_error_msg, strlen(connect_error_msg));
        exit(EXIT_FAILURE);
    }
    const char* connection_success_msg = "Connected Successfully to Server!\n";
    write(1, connection_success_msg, strlen(connection_success_msg));

    char projects_info[MAX_BUFFER_SIZE];
    recv(client_fd, projects_info, MAX_BUFFER_SIZE, 0);
    write(1, projects_info, strlen(projects_info));

    char project_id_str[5];
    const char* select_project_msg = "Please Enter Your Desired Project ID(EXAMPLE:0):";
    write(1, select_project_msg, strlen(select_project_msg));
    read(0, project_id_str, 5);
    send(client_fd, project_id_str, sizeof(project_id_str), 0);

    const char* wait_for_other_users_msg = "Now Wait For Other Users To Join!\n";
    write(1, wait_for_other_users_msg, strlen(wait_for_other_users_msg));

    char udp_port_id[50];
    recv(client_fd, udp_port_id, 50, 0);

    char* udp_port_str = strtok(udp_port_id, "|");
    char* id_str = strtok(NULL, "|");

    close(client_fd);    
}