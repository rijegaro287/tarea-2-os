#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "processing.h"

void get_color_sum(char* path, double* color_sum) {
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

  stbi_image_free(img);
}