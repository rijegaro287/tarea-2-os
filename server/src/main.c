#include <stdint.h>
#include <stdio.h>

#include "processing.h"
#include "helpers.h"

int main()
{
  double* color_sum;
  get_color_sum("./fondo.jpg", color_sum);

  uint8_t max_index = find_max_index(color_sum, 3);

  printf("Red: %f, Green: %f, Blue: %f\n", color_sum[0], color_sum[1], color_sum[2]);
  printf("Dominant color: %s\n", max_index == 0 ? "Red" : max_index == 1 ? "Green" : "Blue");

  return 0;
}