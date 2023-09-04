#pragma once

/**
 * @brief Applies histogram equalization to the image at the specified path and saves it to the corresponding folder.
 * @param path The path to the image.
*/
void histogramEqualization(char* path);

/**
 * @brief Gets the dominant color of the image at the specified path and saves it to the corresponding folder.
 * @param path The path to the image.
*/
void classify_by_color(char* path);

/**
 * @brief Gets the corresponding path in which a file will be saved depending on its dominant color.
 * @param dest_path The destination path.
 * @param rgb_index The index of the dominant color.
*/
void get_classification_path(char* dest_path, uint8_t rgb_index);
