// log.c
#include "headers/log.h"

/// Global variable to hold the log filename.
char *LOG_FILENAME = NULL;

/// @brief Sets the log filename.
/// @param filename The desired log filename. If NULL, a default filename will
/// be generated.
/// @return true if the filename was set successfully, false otherwise.
bool set_logfile(const char *filename) {
  if (LOG_FILENAME != NULL) {
    free(LOG_FILENAME);
  }

  if (filename == NULL) {
    DateTime now = get_rtc();
    int len = snprintf(NULL, 0, DEFAULT_LOG_FILENAME_FORMAT, now.year,
                       now.month, now.day) +
              1;
    LOG_FILENAME = (char *)malloc(len);
    if (LOG_FILENAME != NULL) {
      snprintf(LOG_FILENAME, len, DEFAULT_LOG_FILENAME_FORMAT, now.year,
               now.month, now.day);
    } else {
      return false;
    }
  } else {
    LOG_FILENAME = (char *)malloc(strlen(filename) + 1);
    if (LOG_FILENAME != NULL) {
      strcpy(LOG_FILENAME, filename);
    } else {
      return false;
    }
  }
  return true;
}
