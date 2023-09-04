#pragma once

#include <stdint.h>

#include "config.h"

struct File {
  char path[FILES_PATH_LEN];
  uint64_t size;
};

/**
* @brief Finds the index of the maximum element in an array.
* @param array Array of doubles to be searched.
* @param size Size of the array.
* @return Index of the maximum element in the array.
*/
uint8_t find_max_index(double* array, uint8_t size);

/**
 * @brief Compares the size of two files.
 * @param a Pointer to the first file.
 * @param b Pointer to the second file.
 * @return 1 if the first file is bigger than the second, -1 if the second file is bigger than the first, 0 if they are equal.
 */
int compare_file_size(const void* a, const void* b);

/**
 * @brief Creates a directory.
 * @param path Path of the directory to be created.
 */
void create_directory(const char* path);

/**
 * @brief Deletes a file.
 * @param path Path of the file to be deleted.
 */
void delete_file(const char* path);

/**
 * @brief Saves a file in png format using its binary data.
 * @param file_path Path of the file to be saved.
 * @param binary_data Binary data of the file to be saved.
 * @param binary_data_length Length of the binary data.
 * @return 1 if the file was saved successfully, 0 otherwise.
 */
uint8_t save_file(char* file_path, const char* binary_data, uint64_t  binary_data_length);

/**
 * @brief Searches for files in a directory and saves their path and size into an array. If the array is NULL, it will only return the number of files found.
 * @param path Path of the directory to be searched.
 * @param files Pointer to the array in which the files will be saved.
 * @return Number of files found
*/
uint16_t search_files(const char* path, struct File* files);
