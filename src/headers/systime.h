#ifndef TIME_H
#define TIME_H

#include <sys/time.h>
#include <time.h>

/// Represents a specific date and time.
typedef struct {
  int year;  ///< The year (e.g., 2024).
  int month; ///< The month (1-12).
  int day;   ///< The day of the month (1-31).
  int hr;    ///< The hour of the day (0-23).
  int min;   ///< The minute of the hour (0-59).
  int sec;   ///< The second of the minute (0-59).
  int ms;    ///< The millisecond of the second (0-999).
} DateTime;

/// Retrieves the current date and time.
///
/// @return A DateTime structure containing the current date and time.
DateTime get_rtc();

#endif // !TIME_H
