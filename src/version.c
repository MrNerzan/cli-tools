// version.c
#include "headers/version.h"

const SoftwareVersion software_version = {.major = SOFTWARE_VERSION_MAJOR,
                                          .minor = SOFTWARE_VERSION_MINOR,
                                          .patch = SOFTWARE_VERSION_PATCH,
                                          .build = SOFTWARE_VERSION_BUILD};
void print_version() {
  print_v("Version: %d.%d.%d.%d\n", software_version.major,
          software_version.minor, software_version.patch,
          software_version.build);
}
