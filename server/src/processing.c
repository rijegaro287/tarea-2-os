#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "processing.h"
#include "helpers.h"
#include "constants.h"

void classify_by_color(char* path) {
  double color_sum[3] = { 0, 0, 0 };

  int width, height, channels;
  unsigned char* img = stbi_load(path, &width, &height, &channels, 0);

  if (img == NULL) {
    printf("Error in loading the image\n");
    exit(1);
  }

  if (channels > 3) {
    printf("Image has more than 3 channels\n");
    exit(1);
  }

  uint64_t img_size = width * height * channels;
  for (uint64_t i = 0; i < (img_size - 2); i++) {
    color_sum[0] += ((double)img[i]) / 255;
    color_sum[1] += ((double)img[i + 1]) / 255;
    color_sum[2] += ((double)img[i + 2]) / 255;
  }

  char classified_path[FILES_PATH_LEN];
  uint8_t max_index = find_max_index(color_sum, 3);

  get_classification_path(classified_path, max_index);

  stbi_write_png(classified_path, width, height, channels, img, width * channels);

  stbi_image_free(img);
}

void get_classification_path(char* dest_path, uint8_t rgb_index) {
  uint16_t red_images_count = search_files(RED_IMAGES_PATH, NULL);
  uint16_t green_images_count = search_files(GREEN_IMAGES_PATH, NULL);
  uint16_t blue_images_count = search_files(BLUE_IMAGES_PATH, NULL);

  char output_path[FILES_PATH_LEN];
  char file_name[9];
  uint64_t file_index;

  switch (rgb_index) {
  case 0:
    strcpy(output_path, RED_IMAGES_PATH);
    strcpy(file_name, "red");
    file_index = red_images_count;
    break;

  case 1:
    strcpy(output_path, GREEN_IMAGES_PATH);
    strcpy(file_name, "green");
    file_index = green_images_count;
    break;

  case 2:
    strcpy(output_path, BLUE_IMAGES_PATH);
    strcpy(file_name, "blue");
    file_index = blue_images_count;
    break;

  default:
    break;
  }

  snprintf(dest_path, FILES_PATH_LEN, "%s/%s_%d.png", output_path, file_name, file_index);
}