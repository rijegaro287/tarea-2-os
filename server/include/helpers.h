#pragma once

#include <stdint.h>

/**
* @brief Finds the index of the maximum element in an array.
* @param array Array of doubles to be searched.
* @param size Size of the array.
* @return Index of the maximum element in the array.
*/
uint8_t find_max_index(double* array, uint8_t size);

void create_directories(const char* path);

uint8_t save_file(char* file_path, const char* binary_data, uint64_t  binary_data_length);
