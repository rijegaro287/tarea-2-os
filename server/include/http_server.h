#pragma once

/**
 * @brief Starts the server on the specified port and sets the endpoints.
 * @param port The port on which the server will be deployed.
 * @return 0 if the server was started successfully, 1 otherwise.
*/
int start_server(int port);

/**
 * @brief Stops the server and cleans memory.
*/
void cleanup_server();

/**
 * @brief Callback function for the test endpoint.
 * @param request Request object provided by the server.
 * @param response Response object provided by the server.
 * @param user_data User data provided by the th server.
 * @return U_CALLBACK_CONTINUE
*/
int callback_test(const struct _u_request* request, struct _u_response* response, void* user_data);

/**
 * @brief Callback function for the upload endpoint.
 * @param request Request object provided by the server.
 * @param response Response object provided by the server.
 * @param user_data User data provided by the th server.
 * @return U_CALLBACK_CONTINUE
*/
int callback_upload_file(const struct _u_request* request, struct _u_response* response, void* user_data);

/**
 * @brief Returns the server status.
 * @return U_STATUS_RUNNING if the server is running, U_STATUS_STOPPED otherwise.
*/
int get_server_status();