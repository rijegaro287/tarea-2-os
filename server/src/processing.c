#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "processing.h"
#include "helpers.h"
#include "config.h"

void histogramEqualization(char* path)
{
  int width, height, channels;
  unsigned char* img = stbi_load(path, &width, &height, &channels, 0);

  if (img == NULL) {
    printf("Error in loading the image\n");
    exit(1);
  }

  // Calculate histograms for each color channel
  unsigned int red_hist[HISTOGRAM_SIZE] = { 0 };
  unsigned int green_hist[HISTOGRAM_SIZE] = { 0 };
  unsigned int blue_hist[HISTOGRAM_SIZE] = { 0 };

  for (int i = 0; i < width * height * channels; i += channels) {
    red_hist[img[i]]++;
    if (channels >= 2) {
      green_hist[img[i + 1]]++;
    }
    if (channels >= 3) {
      blue_hist[img[i + 2]]++;
    }
  }

  // Calculate cumulative distribution functions (CDF) for each channel
  unsigned int red_cdf[HISTOGRAM_SIZE] = { 0 };
  unsigned int green_cdf[HISTOGRAM_SIZE] = { 0 };
  unsigned int blue_cdf[HISTOGRAM_SIZE] = { 0 };

  red_cdf[0] = red_hist[0];
  green_cdf[0] = green_hist[0];
  blue_cdf[0] = blue_hist[0];

  for (int i = 1; i < HISTOGRAM_SIZE; i++) {
    red_cdf[i] = red_cdf[i - 1] + red_hist[i];
    green_cdf[i] = green_cdf[i - 1] + green_hist[i];
    blue_cdf[i] = blue_cdf[i - 1] + blue_hist[i];
  }

  // Perform histogram equalization for each channel
  for (int i = 0; i < width * height * channels; i += channels) {
    img[i] = (unsigned char)((red_cdf[img[i]] * 255) / (width * height));
    if (channels >= 2) {
      img[i + 1] = (unsigned char)((green_cdf[img[i + 1]] * 255) / (width * height));
    }
    if (channels >= 3) {
      img[i + 2] = (unsigned char)((blue_cdf[img[i + 2]] * 255) / (width * height));
    }
  }

  uint16_t eq_images_count = search_files(EQUALIZED_IMAGES_PATH, NULL);
  char output_path[FILES_PATH_LEN];

  snprintf(output_path, FILES_PATH_LEN, "%s/%s_%d.png", EQUALIZED_IMAGES_PATH, "foto_eq", eq_images_count);

  stbi_write_jpg(output_path, width, height, channels, img, 100);

  stbi_image_free(img);
}

void classify_by_color(char* path)
{
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

void get_classification_path(char* dest_path, uint8_t rgb_index)
{
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