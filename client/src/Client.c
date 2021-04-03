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
        const char* socket_creation_error_msg = "Socket Creation Error!";
        write(1, socket_creation_error_msg, strlen(socket_creation_error_msg));
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in server_sin;
    server_sin.sin_port = htons(port);
    server_sin.sin_addr.s_addr = inet_addr("127.0.0.1");;
    server_sin.sin_family = AF_INET;

    if (connect(client_fd,(struct sockaddr*)&server_sin, sizeof(server_sin)) == -1)
    {
        const char* connect_error_msg = "Connect Error!";
        write(1, connect_error_msg, strlen(connect_error_msg));
        exit(EXIT_FAILURE);
    }
    const char* connection_success_msg = "Connected Successfully to Server!\n";
    write(1, connection_success_msg, strlen(connection_success_msg));

    char buf[MAX_BUFFER_SIZE];
    recv(client_fd, buf, MAX_BUFFER_SIZE, 0);
    write(1, buf, strlen(buf));
    // while(read(0, buf, MAX_BUFFER_SIZE) != -1)
    // {
    //     send(client_fd, buf, sizeof(buf), 0);
    // }

    close(client_fd);    
}