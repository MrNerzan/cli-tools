#ifndef LOG_H
#define LOG_H

#include "systime.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_LOG_FILENAME_FORMAT "log_%d%d%d.log"

/// Global variable to hold the log filename.
extern char *LOG_FILENAME;

/// @brief Sets the log filename.
/// @param filename The desired log filename. If NULL, a default filename will
/// be generated.
/// @return true if the filename was set successfully, false otherwise.
bool set_logfile(const char *filename);

#endif // !LOG_H
