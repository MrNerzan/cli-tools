// config.c
#include "headers/config.h"
#include "headers/error.h"

/// Global variable to hold debug flags for configuration.
DebugFlags debug = {false, true};

/// Loads configuration from a specified file.
///
/// If CONFIG_FILE is NULL, it defaults to DEFAULT_CONFIG_FILENAME.
///
/// @param CONFIG_FILE The path to the configuration file.
void config_from_file(char *CONFIG_FILE) {
  if (CONFIG_FILE == NULL) {
    CONFIG_FILE = DEFAULT_CONFIG_FILENAME;
  }
  config_from_toml_file(CONFIG_FILE);
}

/// Loads configuration from a TOML file.
///
/// This function attempts to open and parse a TOML configuration file.
///
/// @param CONFIG_FILE The path to the TOML configuration file.
/// @return true if the configuration was loaded successfully, false otherwise.
bool config_from_toml_file(char *CONFIG_FILE) {
  if (CONFIG_FILE == NULL) {
    return false;
  }

  FILE *cf;
  char errbuf[DEFAULT_MAX_ERR_BUFFER_SIZE];
  Error err;

  cf = fopen(CONFIG_FILE, "r");
  if (!cf) {
    set_error(&err, ERROR, errno, "Cannot open config.toml - ");
    error(&err);
  }

  toml_table_t *conf = toml_parse_file(cf, errbuf, sizeof(errbuf));
  fclose(cf);

  if (!conf) {
    set_error(&err, ERROR, 0, "Cannot parse - ");
    error(&err);
    return false;
  }

  toml_table_t *tbl_debug = toml_table_in(conf, "debug");
  if (!tbl_debug) {
    do_nothing();
  } else {
    toml_datum_t debug_enabled = toml_bool_in(tbl_debug, "enabled");
    if (!debug_enabled.ok) {
      do_nothing();
    } else {
      set_debug();
    }

    toml_datum_t date = toml_bool_in(tbl_debug, "date");
    if (date.ok) {
      debug.date = true;
    }

    toml_datum_t time = toml_bool_in(tbl_debug, "time");
    if (time.ok) {
      debug.time = true;
    }
  }

  toml_free(conf);
  return true;
}
