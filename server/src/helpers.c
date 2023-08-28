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