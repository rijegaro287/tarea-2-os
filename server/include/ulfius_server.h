#pragma once

#include <stdio.h>
#include <ulfius.h>

int callback_hello_world(const struct _u_request* request, struct _u_response* response, void* user_data);

void set_endpoints(struct _u_instance* instance);

int start_server(int port);

void stop_server(struct _u_instance* instance);