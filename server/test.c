#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "server.h"
#include "server.c"

void launch(struct server *Server)
{
    char buffer[30000];
    char *hello = "Hola";
    int address_length = sizeof(Server->address);
    int new_socket;
    while (1)
    {
        printf("==== WAITING FOR CONNECTION ====\n");
        new_socket = accept(Server->socket, (struct sockaddr *)&Server->address,
        (socklen_t *)&address_length);
        read(new_socket, buffer, 30000);
        printf("%s\n", buffer);
        write(new_socket, hello, strlen(hello));
        close(new_socket);
    }
}

int main()
{
    struct server Server = server_contructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 10, launch);
    Server.launch(&Server);
}