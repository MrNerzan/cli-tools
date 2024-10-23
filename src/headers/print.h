#ifndef PRINT_H
#define PRINT_H

#include "args.h"
#include "colors.h"
#include "config.h"
#include "log.h"
#include "systime.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void print_v(const char *format, ...);

#endif // PRINT_H
