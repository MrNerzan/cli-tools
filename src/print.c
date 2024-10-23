// print.c
#include "headers/print.h"

void print_v(const char *format, ...) {
  va_list slargs_v;
  va_start(slargs_v, format);

  DateTime now = get_rtc();

  char date[30] = "";
  char time[30] = "";

  if (args.debug) {
    if (debug.date)
      snprintf(date, sizeof(date), "[%04d-%02d-%02d]", now.year, now.month,
               now.day);
    if (debug.time)
      snprintf(time, sizeof(time), "[%02d:%02d:%02d:%03d]", now.hr, now.min,
               now.sec, now.ms);
  }

  int lstr_l = strlen(date) + strlen(time) + strlen(format) + 4;
  char *lformat_v = malloc(lstr_l);

  if (lformat_v == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    va_end(slargs_v);
    return;
  }

  snprintf(lformat_v, lstr_l, "%s %s \t%s\n", date, time, format);

  if (args.log) {
    FILE *log_file = fopen(LOG_FILENAME, "a");
    if (log_file == NULL) {
      fprintf(stderr, "Failed to open file\n");
      free(lformat_v);
      va_end(slargs_v);
      return;
    }

    struct stat file_stat;
    int write_bom = 0;

    if (stat(LOG_FILENAME, &file_stat) == 0 && file_stat.st_size == 0) {
      write_bom = 1;
    }

    if (write_bom) {
      fprintf(log_file, "\xEF\xBB\xBF");
    }

    va_list scargs_v;
    va_copy(scargs_v, slargs_v);
    vfprintf(log_file, lformat_v, scargs_v);
    va_end(scargs_v);

    fclose(log_file);
    free(lformat_v);
  }

  if (!args.quiet) {
    va_list scargs_v;
    va_copy(scargs_v, slargs_v);
    int cstr_l = strlen(DATE_COLOR) + strlen(date) + strlen(TIME_COLOR) +
                 strlen(time) + strlen(RESET_COLOR) + strlen(format) + 4;
    char *cformat_v = malloc(cstr_l);
    snprintf(cformat_v, cstr_l,
             DATE_COLOR "%s" TIME_COLOR "%s" RESET_COLOR "\t%s\n", date, time,
             format);
    vprintf(cformat_v, scargs_v);
    va_end(scargs_v);
    free(cformat_v);
  }
  va_end(slargs_v);
}
