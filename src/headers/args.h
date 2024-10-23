#ifndef ARGS_H
#define ARGS_H

#include <stdbool.h>

/// Structure to hold command line argument flags.
typedef struct {
  bool verbose; ///< Indicates if verbose mode is enabled.
  bool log;     ///< Indicates if logging is enabled.
  bool debug;   ///< Indicates if debug mode is enabled.
  bool force;   ///< Indicates if force mode is enabled.
  bool quiet;   ///< Indicates if quiet mode is enabled.
  bool version; ///< Indicates if version information is requested.
  bool help;    ///< Indicates if help information is requested.
} Args;

extern Args args; ///< Global variable to hold command line argument flags.

/// @brief Enables verbose mode.
/// @return true if verbose mode was set successfully, false otherwise.
bool set_verbose();

/// @brief Enables force mode.
/// @return true if force mode was set successfully, false otherwise.
bool set_force();

/// @brief Enables debug mode.
/// @return true if debug mode was set successfully, false otherwise.
bool set_debug();

/// @brief Enables logging.
/// @return true if logging was set successfully, false otherwise.
bool set_log();

/// @brief Enables quiet mode.
/// @return true if quiet mode was set successfully, false otherwise.
bool set_quiet();

#endif // !ARGS_H
