#pragma once

int start_server(int port);

int callback_test(const struct _u_request* request, struct _u_response* response, void* user_data);

int callback_upload_file(const struct _u_request* request, struct _u_response* response, void* user_data);

int get_server_status();
