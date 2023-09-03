#pragma once

#include <stdint.h>

#include "constants.h"

struct File {
  char path[TMP_FILES_PATH_LEN];
  uint64_t size;
};

/**
* @brief Finds the index of the maximum element in an array.
* @param array Array of doubles to be searched.
* @param size Size of the array.
* @return Index of the maximum element in the array.
*/
uint8_t find_max_index(double* array, uint8_t size);

void create_directory(const char* path);

uint8_t save_file(char* file_path, const char* binary_data, uint64_t  binary_data_length);

uint64_t search_files(const char* path, struct File* files);
