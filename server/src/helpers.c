#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
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

int compare_file_size(const void* a, const void* b) {
  struct File* file_a = (struct File*)a;
  struct File* file_b = (struct File*)b;

  if (file_a->size < file_b->size) {
    return -1;
  }
  else if (file_a->size > file_b->size) {
    return 1;
  }
  else {
    return 0;
  }
}

void create_directory(const char* path) {
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

void delete_file(const char* path) {
  if (remove(path) == 0) {
    // printf("File '%s' deleted successfully.\n", path);
    return;
  }

  printf("Error deleting file '%s'.\n", path);
  return;
}

uint8_t save_file(char* file_path, const char* binary_data, uint64_t  binary_data_length) {
  FILE* file = fopen(file_path, "wb");

  if (file) {
    fwrite(binary_data, 1, binary_data_length, file);

    fclose(file);
    return 0;
  }

  fprintf(stderr, "Failed to open file for writing: %s\n", file_path);
  return 1;
}

uint16_t search_files(const char* path, struct File* files) {
  DIR* dir = opendir(path);

  if (!dir) {
    printf("Error opening directory '%s'.\n", path);
    return 0;
  }

  struct dirent* entry;
  struct stat file_stat;

  uint16_t file_index = 0;
  while ((entry = readdir(dir)) != NULL && file_index < PROCESSING_QUEUE_SIZE) {
    if (entry->d_type == DT_REG) {
      char file_path[FILES_PATH_LEN];
      snprintf(file_path, FILES_PATH_LEN, "%s/%s", path, entry->d_name);

      if ((files != NULL) && stat(file_path, &file_stat) == 0) {
        strcpy(files[file_index].path, file_path);
        files[file_index].size = file_stat.st_size;
      }

      file_index++;
    }
  }

  closedir(dir);

  return file_index;
}