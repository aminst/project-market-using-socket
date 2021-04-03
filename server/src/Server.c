#include "Server.h"

int get_server_port(int argc, char* argv[])
{
    if (argc != 2)
        return DEFAULT_SERVER_PORT;
    else
    {
        return strtol(argv[1], NULL, 10);
    }
}

void write_server_startup_msg(int port)
{
    const char* server_run_msg = "Server Is Running On Port ";
    write(1, server_run_msg, strlen(server_run_msg));
    char port_str[10];
    snprintf(port_str, sizeof(port_str), "%d", port);
    write(1, port_str, strlen(port_str));
    const char* waiting_for_users_connect_msg = "\nWating For Users to connect\n";
    write(1, waiting_for_users_connect_msg, strlen(waiting_for_users_connect_msg));    
}

void run_server_on_port(int port)
{
    struct sockaddr_in server_sin;

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        const char* socket_creation_error_msg = "Socket Creation Error!";
        write(1, socket_creation_error_msg, strlen(socket_creation_error_msg));
        exit(EXIT_FAILURE);
    }

    server_sin.sin_port = htons(port);
    server_sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_sin.sin_family = AF_INET;

    const int true_flag = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &true_flag, sizeof(int)) < 0)
    {
        const char* set_sock_option_error_msg = "Set Option Error!";
        write(1, set_sock_option_error_msg, strlen(set_sock_option_error_msg));
        exit(EXIT_FAILURE);
    }

    if (bind(server_fd, (struct sockaddr*)& server_sin, sizeof(server_sin)) == -1)
    {
        const char* bind_error_msg = "Bind Error!";
        write(1, bind_error_msg, strlen(bind_error_msg));
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_CONNECTIONS) == -1)
    {
        const char* listen_error_msg = "Listen Error!";
        write(1, listen_error_msg, strlen(listen_error_msg));
        exit(EXIT_FAILURE);
    }

    write_server_startup_msg(port);

    struct sockaddr_in client_sin;
    int client_in_len;
    int new_server_fd = accept(server_fd, (struct sockaddr*)& client_sin, (socklen_t*)&client_in_len);
    if (new_server_fd == -1)
    {
        const char* accept_error_msg = "Accept Error!";
        write(1, accept_error_msg, strlen(accept_error_msg));
        exit(EXIT_FAILURE);
    }
    char buf[MAX_BUFFER_SIZE];
    while (1)
    {
        if ((client_in_len = recv(new_server_fd, buf, sizeof(buf), 0)))
            write(1, buf, strlen(buf));
    }
    close(server_fd);
    close(new_server_fd);
}
