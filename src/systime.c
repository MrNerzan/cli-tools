// systime.c
#include "headers/systime.h"

/// Retrieves the current date and time.
///
/// @return A DateTime structure containing the current date and time.
DateTime get_rtc() {
  struct timeval tv;
  gettimeofday(&tv, NULL);

  struct tm *local_time = localtime(&tv.tv_sec);

  DateTime now;
  now.year = local_time->tm_year + 1900; // years since 1900
  now.month = local_time->tm_mon + 1;    // months since January
  now.day = local_time->tm_mday;
  now.hr = local_time->tm_hour;
  now.min = local_time->tm_min;
  now.sec = local_time->tm_sec;
  now.ms = tv.tv_usec / 1000; // microseconds to milliseconds

  return now;
}
