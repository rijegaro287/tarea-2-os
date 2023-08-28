#pragma once

/**
* @brief Calculates the sum of each RGB value in an image.
* @param path Path to the image.
* @param color_sum Pointer to an array of 3 doubles where the sum of each RGB value will be stored.
*/
void get_color_sum(char* path, double* color_sum);