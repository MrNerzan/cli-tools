#ifndef ERROR_H
#define ERROR_H

#include "print.h"
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#define DEFAULT_MAX_ERR_BUFFER_SIZE 200
#define DEFAULT_ERR_MSG_BUFFER_SIZE 512

typedef uint8_t ErrorCode;

/// Enum for error types
typedef enum {
  WARNING, ///< Indicates a warning error
  ERROR,   ///< Indicates a critical error
  // Additional error types can be added here
} ErrorType;

/// Struct representing an error with its details.
typedef struct {
  bool is_set;                           ///< Indicates if an error is set
  ErrorType type;                        ///< Type of the error (WARNING, ERROR)
  ErrorCode code;                        ///< Error code (can be extended)
  char msg[DEFAULT_ERR_MSG_BUFFER_SIZE]; ///< Buffer for error message
} Error;

/// Sets the error details in the provided Error struct.
///
/// @param err Pointer to the Error struct to modify.
/// @param type The type of the error (WARNING or ERROR).
/// @param code The error code associated with the error.
/// @param message The error message to store in the struct.
void set_error(Error *err, ErrorType type, ErrorCode code, const char *message);

/// Clears the error state of the provided Error struct.
///
/// @param err Pointer to the Error struct to clear.
void clear_error(Error *err);

/// Prints the error message contained in the provided Error struct.
///
/// @param err Pointer to the Error struct containing the error details.
void error(const Error *err);

/// A placeholder function that does nothing.
void do_nothing();

#endif // ERROR_H
