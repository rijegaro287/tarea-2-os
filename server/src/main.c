#include "http_server.h"
#include "helpers.h"

#define SERVER_PORT 3000

int main()
{
  // double color_sum[3];
  // get_color_sum("./persona1.jpg", color_sum);

  // uint8_t max_index = find_max_index(color_sum, 3);

  // printf("Red: %f, Green: %f, Blue: %f\n", color_sum[0], color_sum[1], color_sum[2]);
  // printf("Dominant color: %s\n", max_index == 0 ? "Red" : max_index == 1 ? "Green" : "Blue");
  create_directories("tmp_files");
  create_directories("processed_files");

  start_server(SERVER_PORT);

  return 0;
}