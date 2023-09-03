#include <stdio.h>
#include <ulfius.h>

#include "http_server.h"

int start_server(int port) {
  struct _u_instance instance;

  if (ulfius_init_instance(&instance, port, NULL, NULL) != U_OK) {
    fprintf(stderr, "Error ulfius_init_instance, abort\n");
    return(1);
  }

  u_map_put(instance.default_headers, "Access-Control-Allow-Origin", "*");

  ulfius_add_endpoint_by_val(&instance, "GET", "/test", NULL, 0, &callback_test, NULL);
  ulfius_add_endpoint_by_val(&instance, "POST", "/upload", NULL, 0, &callback_upload_file, NULL);

  // Start the framework
  if (ulfius_start_framework(&instance) == U_OK) {
    printf("Started server on: http://localhost:%d\n", instance.port);

    // Wait for the user to press <enter> on the console to quit the application
    getchar();
  }
  else {
    fprintf(stderr, "Error starting framework\n");
  }

  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);

  printf("Server stopped\n");

  return 0;
}

int callback_test(const struct _u_request* request, struct _u_response* response, void* user_data) {
  ulfius_set_string_body_response(response, 200, "Server is running!");
  return U_CALLBACK_CONTINUE;
}

int callback_upload_file(const struct _u_request* request, struct _u_response* response, void* user_data) {
  const char* binary_image = (char*)request->binary_body;
  const size_t binary_image_length = request->binary_body_length;

  const char* file_path = "uploaded_image.png";

  FILE* file = fopen(file_path, "wb");
  if (!file) {
    fprintf(stderr, "Failed to open file for writing: %s\n", file_path);

    ulfius_set_string_body_response(response, 500, "An error occurred while uploading the file!");
  }
  else {
    // Write the data to the file
    fwrite(binary_image, 1, binary_image_length, file);

    // Close the file
    fclose(file);

    // Set the response
    ulfius_set_string_body_response(response, 200, "File uploaded successfully!");
  }

  return U_CALLBACK_CONTINUE;
}