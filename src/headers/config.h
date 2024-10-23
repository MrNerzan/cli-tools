#ifndef CONFIG_H
#define CONFIG_H

#include "args.h"
#include "toml.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CONFIG_FILENAME "config.toml"

/// Structure to hold debug flags for configuration.
///
/// This structure contains flags to indicate whether to include
/// the date and time in debug output.
typedef struct {
  bool date; ///< Indicates if the date should be included in debug output.
  bool time; ///< Indicates if the time should be included in debug output.
} DebugFlags;

/// Loads configuration from a specified file.
///
/// @param CONFIG_FILE The path to the configuration file.
void config_from_file(char *CONFIG_FILE);

/// Loads configuration from a TOML file.
///
/// @param CONFIG_FILE The path to the TOML configuration file.
/// @return true if the configuration was loaded successfully, false otherwise.
bool config_from_toml_file(char *CONFIG_FILE);

/// Global variable to hold debug flags for configuration.
extern DebugFlags debug;

#endif // CONFIG_H
