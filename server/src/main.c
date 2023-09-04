#include <ulfius.h>
#include <pthread.h>

#include "http_server.h"
#include "processing.h"
#include "helpers.h"
#include "config.h"

void create_directories() {
  create_directory(TMP_FILES_PATH);
  create_directory(PROCESSED_IMAGES_PATH);
  create_directory(EQUALIZED_IMAGES_PATH);
  create_directory(RED_IMAGES_PATH);
  create_directory(GREEN_IMAGES_PATH);
  create_directory(BLUE_IMAGES_PATH);
  create_directory(LOGS_PATH);
}

void* processing_loop(void* vargp) {
  sleep(3);
  while (get_server_status() == U_STATUS_RUNNING) {
    struct File uploaded_files[PROCESSING_QUEUE_SIZE];
    uint64_t uploaded_files_count = search_files(TMP_FILES_PATH, uploaded_files);

    qsort(uploaded_files, uploaded_files_count, sizeof(struct File), compare_file_size);

    for (uint8_t i = 0; i < uploaded_files_count; i++) {
      struct File current_file = uploaded_files[i];
      printf("Processing file: %s\n", current_file.path);
      printf("File size: %ld\n", current_file.size);

      histogramEqualization(current_file.path);
      classify_by_color(current_file.path);

      delete_file(current_file.path);
      printf("------------------------------\n");

      sleep(1);
    }
  }

  return NULL;
}

int main()
{
  init_config();

  sleep(1);

  create_directories();

  pthread_t thread_id;
  pthread_create(&thread_id, NULL, processing_loop, NULL);

  start_server(SERVER_PORT);

  pthread_join(thread_id, NULL);
  return 0;
}