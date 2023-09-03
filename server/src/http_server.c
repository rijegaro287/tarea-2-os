#include <stdio.h>
#include <ulfius.h>

#include "http_server.h"
#include "helpers.h"
#include "constants.h"

static uint64_t uploaded_files_count;
static struct _u_instance server_instance;

int start_server(int port) {
  uploaded_files_count = search_files(TMP_FILES_PATH, NULL);

  if (ulfius_init_instance(&server_instance, port, NULL, NULL) != U_OK) {
    fprintf(stderr, "Error ulfius_init_instance, abort\n");
    return(1);
  }

  u_map_put(server_instance.default_headers, "Access-Control-Allow-Origin", "*");

  ulfius_add_endpoint_by_val(&server_instance, "GET", "/test", NULL, 0, &callback_test, NULL);
  ulfius_add_endpoint_by_val(&server_instance, "POST", "/upload", NULL, 0, &callback_upload_file, NULL);

  // Start the framework
  if (ulfius_start_framework(&server_instance) == U_OK) {
    printf("Started server on: http://localhost:%d\n", server_instance.port);

    // Wait for the user to press <enter> on the console to quit the application
    getchar();
  }
  else {
    fprintf(stderr, "Error starting framework\n");
  }

  ulfius_stop_framework(&server_instance);
  ulfius_clean_instance(&server_instance);

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

  char file_path[FILES_PATH_LEN];
  snprintf(file_path, FILES_PATH_LEN, "%s/uploaded_image_%d.png", TMP_FILES_PATH, uploaded_files_count);

  if (save_file(file_path, binary_image, binary_image_length) == 0) {
    ulfius_set_string_body_response(response, 200, "File uploaded successfully!");
    uploaded_files_count++;
  }
  else {
    ulfius_set_string_body_response(response, 500, "An error occurred while uploading the file!");
  }

  return U_CALLBACK_CONTINUE;
}

int get_server_status() {
  return server_instance.status;
}