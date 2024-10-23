// args.c
#include "headers/args.h"

Args args = {false, false, false, false,
             false}; ///< Global variable to hold command line argument flags.

/// @brief Enables verbose mode.
/// @return true if verbose mode was set successfully, false otherwise.
bool set_verbose() {
  args.verbose = true; ///< Set verbose mode to true.
  return args.verbose; ///< Return the current state of verbose mode.
}

/// @brief Enables force mode.
/// @return true if force mode was set successfully, false otherwise.
bool set_force() {
  args.force = true; ///< Set force mode to true.
  return args.force; ///< Return the current state of force mode.
}

/// @brief Enables debug mode.
/// @return true if debug mode was set successfully, false otherwise.
bool set_debug() {
  args.debug = true; ///< Set debug mode to true.
  return args.debug; ///< Return the current state of debug mode.
}

/// @brief Enables logging.
/// @return true if logging was set successfully, false otherwise.
bool set_log() {
  args.log = true; ///< Set logging mode to true.
  return args.log; ///< Return the current state of logging.
}

/// @brief Enables quiet mode.
/// @return true if quiet mode was set successfully, false otherwise.
bool set_quiet() {
  args.quiet = true; ///< Set quiet mode to true.
  return args.quiet; ///< Return the current state of quiet mode.
}
