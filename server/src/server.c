#include "server.h" 
#include <stdio.h>
#include <stdlib.h>

struct server server_contructor(int domain, int service, int protocol,
    __u_long interface, int port, int backlog, void (*launch)(struct server* Server))
{
    struct server Server;

    Server.domain = domain;
    Server.service = service;
    Server.protocol = protocol;
    Server.interface = interface;
    Server.port = port;
    Server.backlog = backlog;

    Server.address.sin_family = domain;
    Server.address.sin_port = htons(port);
    Server.address.sin_addr.s_addr = htonl(interface);

    Server.socket = socket(domain, service, protocol);
    if (Server.socket == 0) {
        perror("Failed to connect socket...\n");
        exit(1);
    }

    if ((bind(Server.socket, (struct sockaddr*)&Server.address,
        sizeof(Server.address))) < 0) {
        perror("Failed to bind socket...\n");
        exit(1);
    }

    if ((listen(Server.socket, Server.backlog)) < 0) {
        perror("Failed to start listening...\n");
        exit(1);
    }

    Server.launch = launch;

    return Server;
};