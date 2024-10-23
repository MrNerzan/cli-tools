// error.c
#include "headers/error.h"

void set_error(Error *err, ErrorType type, ErrorCode code,
               const char *message) {
  err->is_set = true; ///< Mark the error as set
  err->type = type;   ///< Set the error type
  err->code = code;   ///< Set the error code
  snprintf(err->msg, sizeof(err->msg), "%s",
           message); ///< Set the error message
}

void clear_error(Error *err) {
  err->is_set = false; ///< Reset the error flag
  err->code = 0;       ///< Clear the error code
  err->msg[0] = '\0';  ///< Clear the error message
}

void error(const Error *err) {
  if (err == NULL) {
    print_v("[ERROR]\tUnknown error occurred.");
    return;
  }

  // Constructing the full error message
  char full_err_msg[DEFAULT_ERR_MSG_BUFFER_SIZE];
  const char *type_str = (err->type == WARNING) ? "WARNING" : "ERROR";

  snprintf(full_err_msg, sizeof(full_err_msg), "[%s] Code: %u\t%s", type_str,
           err->code, err->msg[0] ? err->msg : "No additional details");

  print_v("%s", full_err_msg);
}

/// A placeholder function that does nothing.
void do_nothing() {
  // this function should do something
}
