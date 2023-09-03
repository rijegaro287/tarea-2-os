#include <ulfius_server.h>

/**
 * Callback function for the web application on /helloworld url call
 */
int callback_hello_world(const struct _u_request* request, struct _u_response* response, void* user_data) {
  ulfius_set_string_body_response(response, 200, "Server is running!");
  return U_CALLBACK_CONTINUE;
}

void set_endpoints(struct _u_instance* instance) {
  ulfius_add_endpoint_by_val(instance, "GET", "/test", NULL, 0, &callback_hello_world, NULL);
}

int start_server(int port) {
  struct _u_instance instance;

  // Initialize instance with the port number
  if (ulfius_init_instance(&instance, port, NULL, NULL) != U_OK) {
    fprintf(stderr, "Error ulfius_init_instance, abort\n");
    return(1);
  }

  u_map_put(instance.default_headers, "Access-Control-Allow-Origin", "*");

  set_endpoints(&instance);

  // Start the framework
  if (ulfius_start_framework(&instance) == U_OK) {
    printf("Started framework on: http://localhost:%d\n", instance.port);

    // Wait for the user to press <enter> on the console to quit the application
    getchar();
  }
  else {
    fprintf(stderr, "Error starting framework\n");
  }

  stop_server(&instance);
  printf("Server stopped\n");

  return 0;
}

void stop_server(struct _u_instance* instance) {
  ulfius_stop_framework(instance);
  ulfius_clean_instance(instance);
}