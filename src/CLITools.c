// CLITools.c
#include "headers/CLITools.h"

/// @brief Displays the help information by parsing the HELP.md file.
void get_help() { parse_markdown("HELP.md"); }

/// @brief Sets command line arguments based on user input.
/// @param argc The number of command line arguments.
/// @param argv The command line arguments as an array of strings.
/// @return true if the arguments were set successfully, false otherwise.
bool set_args(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
      get_help();
      return true;
    } else if (strcmp(argv[i], "--version") == 0 ||
               strcmp(argv[i], "-v") == 0) {
      print_version();
      return true;
    }
  }

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--verbose") == 0 || strcmp(argv[i], "-vv") == 0) {
      if (!set_verbose())
        return false;
    } else if (strcmp(argv[i], "--log") == 0 || strcmp(argv[i], "-l") == 0) {
      if (i + 1 < argc && argv[i + 1][0] != '-') {
        set_logfile(argv[++i]);
      } else {
        set_logfile(NULL);
      }
      if (!set_log())
        return false;
    } else if (strcmp(argv[i], "--force") == 0 || strcmp(argv[i], "-f") == 0) {
      if (!set_force())
        return false;
    } else if (strcmp(argv[i], "--quiet") == 0 || strcmp(argv[i], "-q") == 0) {
      if (!set_quiet())
        return false;
    } else if (strcmp(argv[i], "--debug") == 0 || strcmp(argv[i], "-d") == 0) {
      if (!set_debug())
        return false;
    } else {
      print_v("Unknown argument: %s\n", argv[i]);
      return false;
    }
  }
  return true;
}
