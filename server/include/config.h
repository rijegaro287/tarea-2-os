#pragma once

#include <stdint.h>

#define CONFIG_FILE_PATH "./config.conf"
#define FILES_PATH_LEN 256

extern uint16_t SERVER_PORT;
extern uint16_t PROCESSING_QUEUE_SIZE;
extern uint16_t HISTOGRAM_SIZE;

extern char TMP_FILES_PATH[FILES_PATH_LEN];

extern char PROCESSED_IMAGES_PATH[FILES_PATH_LEN];
extern char EQUALIZED_IMAGES_PATH[FILES_PATH_LEN];
extern char RED_IMAGES_PATH[FILES_PATH_LEN];
extern char GREEN_IMAGES_PATH[FILES_PATH_LEN];
extern char BLUE_IMAGES_PATH[FILES_PATH_LEN];

extern char LOGS_PATH[FILES_PATH_LEN];

/**
 * @brief Initializes the configuration of the server.
 * @return 0 if the configuration was initialized successfully, 1 otherwise.
*/
uint8_t init_config();