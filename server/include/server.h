#pragma once

#ifndef server_h
#define server_h

#include <sys/socket.h>
#include <netinet/in.h>

struct server
{
    int domain;
    int service;
    int protocol;
    __u_long interface;
    int port;
    int backlog;

    struct sockaddr_in address;

    int socket;

    void (*launch)(struct server* Server);

};

struct server server_contructor(int domain, int service, int protocol,
    __u_long interface, int port, int backlog, void (*launch)(struct server* Server));



#endif /* server_h */


