#include <stdlib.h>
#include <string.h>

#include <libconfig.h>

#include "config.h"

uint16_t SERVER_PORT = 1717;
uint16_t PROCESSING_QUEUE_SIZE = 10;
uint16_t HISTOGRAM_SIZE = 256;

char TMP_FILES_PATH[FILES_PATH_LEN] = "./tmp_files";

char PROCESSED_IMAGES_PATH[FILES_PATH_LEN] = "./processed_images";
char EQUALIZED_IMAGES_PATH[FILES_PATH_LEN] = "./processed_images/equalized";
char RED_IMAGES_PATH[FILES_PATH_LEN] = "./processed_images/red";
char GREEN_IMAGES_PATH[FILES_PATH_LEN] = "./processed_images/green";
char BLUE_IMAGES_PATH[FILES_PATH_LEN] = "./processed_images/blue";

char LOGS_PATH[FILES_PATH_LEN] = "./logs";

uint8_t init_config() {
  config_t cfg;
  config_setting_t* setting;
  const char* str;

  config_init(&cfg);

  if (!config_read_file(&cfg, CONFIG_FILE_PATH)) {
    fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
      config_error_line(&cfg), config_error_text(&cfg));

    config_destroy(&cfg);

    return(EXIT_FAILURE);
  }

  if (config_lookup_string(&cfg, "SERVER_PORT", &str)) {
    SERVER_PORT = atoi(str);
  }

  if (config_lookup_string(&cfg, "PROCESSING_QUEUE_SIZE", &str)) {
    PROCESSING_QUEUE_SIZE = atoi(str);
  }

  if (config_lookup_string(&cfg, "HISTOGRAM_SIZE", &str)) {
    HISTOGRAM_SIZE = atoi(str);
  }

  if (config_lookup_string(&cfg, "TMP_FILES_PATH", &str)) {
    strcpy(TMP_FILES_PATH, str);
  }

  if (config_lookup_string(&cfg, "PROCESSED_IMAGES_PATH", &str)) {
    strcpy(PROCESSED_IMAGES_PATH, str);
  }

  if (config_lookup_string(&cfg, "EQUALIZED_IMAGES_PATH", &str)) {
    strcpy(EQUALIZED_IMAGES_PATH, str);
  }

  if (config_lookup_string(&cfg, "RED_IMAGES_PATH", &str)) {
    strcpy(RED_IMAGES_PATH, str);
  }

  if (config_lookup_string(&cfg, "GREEN_IMAGES_PATH", &str)) {
    strcpy(GREEN_IMAGES_PATH, str);
  }

  if (config_lookup_string(&cfg, "BLUE_IMAGES_PATH", &str)) {
    strcpy(BLUE_IMAGES_PATH, str);
  }

  if (config_lookup_string(&cfg, "LOGS_PATH", &str)) {
    strcpy(LOGS_PATH, str);
  }

  return 0;
}