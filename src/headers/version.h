// version.h
#ifndef VERSION_H
#define VERSION_H

#include "print.h"
#include <stdint.h>

#define SOFTWARE_VERSION_MAJOR 0
#define SOFTWARE_VERSION_MINOR 1
#define SOFTWARE_VERSION_PATCH 0
#define SOFTWARE_VERSION_BUILD 0

typedef struct {
  uint8_t major;
  uint8_t minor;
  uint8_t patch;
  uint8_t build;
} SoftwareVersion;

void print_version();

#endif // VERSION_H
