// CLITools.h
#ifndef CLITools
#define CLITools

#include "args.h"
#include "log.h"
#include "markdown.h"
#include "print.h"
#include "systime.h"
#include "version.h"
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

/// @brief Parses command line arguments.
/// @param argc The number of command line arguments.
/// @param argv The command line arguments as an array of strings.
/// @return true if the arguments were parsed successfully, false otherwise.
bool set_args(int argc, char *argv[]);

/// @brief Loads configuration from the specified file.
/// @param CONFIG_FILE The name of the configuration file to load.
void config_from_file(char *CONFIG_FILE);

/// @brief Loads configuration from a TOML file.
/// @param CONFIG_FILE The name of the TOML configuration file to load.
/// @return true if the configuration was loaded successfully, false otherwise.
bool config_from_toml_file(char *CONFIG_FILE);

#endif // !CLITools
