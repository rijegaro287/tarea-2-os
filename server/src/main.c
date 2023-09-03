#include <ulfius.h>
#include <pthread.h>

#include "http_server.h"
#include "processing.h"
#include "helpers.h"
#include "constants.h"

#define SERVER_PORT 3000

void create_directories() {
  create_directory(TMP_FILES_PATH);
  create_directory(EQUALIZED_IMAGES_PATH);
  create_directory(RED_IMAGES_PATH);
  create_directory(GREEN_IMAGES_PATH);
  create_directory(BLUE_IMAGES_PATH);
}

void* processing_loop(void* vargp) {
  while (get_server_status() == U_STATUS_RUNNING) {
    struct File uploaded_files[PROCESSING_QUEUE_SIZE];
    uint64_t found_files = search_files(TMP_FILES_PATH, uploaded_files);

    sleep(3);
    printf("-------------------------------------------------------------\n");
    for (uint8_t i = 0; i < found_files; i++) {
      struct File current_file = uploaded_files[i];
      printf("Processing file: %s\n", current_file.path);
      printf("File size: %ld\n", current_file.size);
    }
  }

  return NULL;
}

int main()
{
  // double color_sum[3];
  // get_color_sum("./persona1.jpg", color_sum);

  // uint8_t max_index = find_max_index(color_sum, 3);

  // printf("Red: %f, Green: %f, Blue: %f\n", color_sum[0], color_sum[1], color_sum[2]);
  // printf("Dominant color: %s\n", max_index == 0 ? "Red" : max_index == 1 ? "Green" : "Blue");

  create_directories();

  pthread_t thread_id;
  pthread_create(&thread_id, NULL, processing_loop, NULL);

  start_server(SERVER_PORT);

  pthread_join(thread_id, NULL);
  return 0;
}