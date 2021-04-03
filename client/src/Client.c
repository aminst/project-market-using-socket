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

void write_port_id_msg(char* port_str, char* id_str)
{
    char temp[200] = {0};
    strcat(temp, "Got Port: ");
    strcat(temp, port_str);
    strcat(temp, " From Server!\n");
    strcat(temp, "Got Id: ");
    strcat(temp, id_str);
    strcat(temp, " From Server!\n");
    write(1, temp, strlen(temp));
}

int connect_to_server(int port)
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

    if (connect(client_fd, (struct sockaddr*)&server_sin, sizeof(server_sin)) == -1)
    {
        const char* connect_error_msg = "Connect Error!\n";
        write(1, connect_error_msg, strlen(connect_error_msg));
        exit(EXIT_FAILURE);
    }
    const char* connection_success_msg = "Connected Successfully to Server!\n";
    write(1, connection_success_msg, strlen(connection_success_msg));

    return client_fd;
}

void send_selected_project_number_to_server(int client_fd)
{
    char project_id_str[5];
    const char* select_project_msg = "Please Enter Your Desired Project ID(EXAMPLE:0):";
    write(1, select_project_msg, strlen(select_project_msg));
    read(0, project_id_str, 5);
    send(client_fd, project_id_str, sizeof(project_id_str), 0);    
}

int init_udp(char* udp_port_str)
{
    int udp_socket_fd;
    if ((udp_socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        const char* udp_socket_create_error_msg = "UDP Socket Creation Error!\n";
        write(1, udp_socket_create_error_msg, strlen(udp_socket_create_error_msg));
        exit(EXIT_FAILURE);
    }

    int broadcast = 1;
    if (setsockopt(udp_socket_fd, SOL_SOCKET, SO_BROADCAST, (char *)&broadcast, sizeof(broadcast)) == -1)
    {
        const char* udp_socket_set_option_error = "UDP Socket Set Option Error!\n";
        write(1, udp_socket_set_option_error, strlen(udp_socket_set_option_error));
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(udp_socket_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) == -1)
    {
        const char* udp_socket_set_option_error = "UDP Socket Set Option Error!\n";
        write(1, udp_socket_set_option_error, strlen(udp_socket_set_option_error));
        exit(EXIT_FAILURE);        
    }

    struct sockaddr_in udp_sin;
    udp_sin.sin_family = AF_INET;
    udp_sin.sin_port = htons(atoi(udp_port_str));
    udp_sin.sin_addr.s_addr = inet_addr("255.255.255.255");

    if (bind(udp_socket_fd, (struct sockaddr *)&udp_sin, sizeof(udp_sin)) == -1)
    {
        const char* udp_bind_error_msg = "UDP Bind Error!\n";
        write(1, udp_bind_error_msg, strlen(udp_bind_error_msg));
        exit(EXIT_FAILURE);
    }

    const char* udp_success_msg = "Successfuly Initialized UDP Socket\n";
    write(1, udp_success_msg, strlen(udp_success_msg));

    return udp_socket_fd;
}

void run_client(int port)
{
    int client_fd = connect_to_server(port);

    char projects_info[MAX_BUFFER_SIZE];
    recv(client_fd, projects_info, MAX_BUFFER_SIZE, 0);
    write(1, projects_info, strlen(projects_info));

    send_selected_project_number_to_server(client_fd);

    const char* wait_for_other_users_msg = "Now Wait For Other Users To Join!\n";
    write(1, wait_for_other_users_msg, strlen(wait_for_other_users_msg));

    char udp_port_id[50];
    recv(client_fd, udp_port_id, 50, 0);

    char* udp_port_str = strtok(udp_port_id, "|");
    char* id_str = strtok(NULL, "|");

    write_port_id_msg(udp_port_str, id_str);

    int udp_socket_fd = init_udp(udp_port_str);


    close(client_fd);
    close(udp_socket_fd);
}