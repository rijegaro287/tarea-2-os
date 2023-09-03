#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

#include "helpers.h"

uint8_t find_max_index(double* array, uint8_t size) {
  uint8_t max_index = 0;
  double max_element = 0;

  for (uint8_t current_index = 0; current_index < size; current_index++) {
    const double current_element = array[current_index];

    if (current_element > max_element) {
      max_element = current_element;
      max_index = current_index;
    }
  }

  return max_index;
}

void create_directories(const char* path) {
  DIR* dir = opendir(path);

  if (dir) {
    closedir(dir);
    return;
  }

  if (mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0) {
    printf("Directory '%s' created successfully.\n", path);
    return;
  }

  printf("Error creating directory '%s'.\n", path);
  return;
}

uint8_t save_file(char* file_path, const char* binary_data, uint64_t  binary_data_length) {
  FILE* file = fopen(file_path, "wb");

  if (!file) {
    fprintf(stderr, "Failed to open file for writing: %s\n", file_path);
    return 1;
  }

  fwrite(binary_data, 1, binary_data_length, file);

  fclose(file);
  return 0;
}