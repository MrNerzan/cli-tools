// markdown.c
#include "headers/markdown.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_inline_code_segment(const char *text, int start, int end);
static int split_row(const char *line,
                     char columns[MD_MAX_COLUMNS][MD_MAX_COLUMN_LENGTH]);

/// @brief Prints a heading based on its level.
/// @param line The heading text to print.
/// @param heading_level The level of the heading (1-3).
void print_heading(const char *line, int heading_level) {
  switch (heading_level) {
  case 1:
    printf(BOLD_TEXT "%s" RESET_COLOR "\n", line);
    break;
  case 2:
    printf(RED_TEXT BOLD_TEXT "%s" RESET_COLOR "\n", line);
    break;
  case 3:
  default:
    printf("%s\n", line);
    break;
  }
}

/// @brief Checks if a line is an unordered list.
/// @param line The line to check.
/// @return 1 if the line is an unordered list, 0 otherwise.
int is_unordered_list(const char *line) {
  return (line[0] == '-' || line[0] == '*') && isspace(line[1]);
}

/// @brief Checks if a line is an ordered list.
/// @param line The line to check.
/// @return 1 if the line is an ordered list, 0 otherwise.
int is_ordered_list(const char *line) {
  int i = 0;
  while (isdigit(line[i])) {
    i++;
  }
  return line[i] == '.' && isspace(line[i + 1]);
}

/// @brief Prints a segment of inline code.
/// @param text The text containing the code.
/// @param start The start index of the code segment.
/// @param end The end index of the code segment.
static void print_inline_code_segment(const char *text, int start, int end) {
  printf(MD_CODE_BLOCK_COLOR);
  for (int i = start; i < end; i++) {
    printf("%c", text[i]);
  }
  printf(RESET_COLOR);
}

/// @brief Prints inline code from a line.
/// @param line The line containing inline code.
void print_inline_code(const char *line) {
  int i = 0;
  int in_code = 0;
  while (line[i] != '\0') {
    if (line[i] == '`') {
      if (in_code) {
        printf(RESET_COLOR);
        in_code = 0;
      } else {
        printf(MD_INLINE_CODE_COLOR);
        in_code = 1;
      }
      i++;
    } else {
      printf("%c", line[i]);
      i++;
    }
  }
  if (in_code) {
    printf(RESET_COLOR);
  }
}

/// @brief Prints a list item.
/// @param line The line containing the list item.
/// @param is_ordered Indicates if the list is ordered (1) or unordered (0).
void print_list(const char *line, int is_ordered) {
  printf("  • ");
  print_inline_code(line);
}

/// @brief Prints a markdown link.
/// @param line The line containing the link.
void print_link(const char *line) {
  int i = 0;
  while (line[i] != '\0') {
    if (line[i] == '[') {
      int start = i + 1;
      char *closing_bracket = strchr(line + start, ']');
      if (closing_bracket != NULL) {
        if (closing_bracket[1] == '(') {
          int end_text = closing_bracket - line;
          int start_url = end_text + 2;
          char *closing_paren = strchr(line + start_url, ')');
          if (closing_paren != NULL) {
            char text[MD_MAX_COLUMN_LENGTH], url[MD_MAX_COLUMN_LENGTH];
            strncpy(text, line + start, end_text - start);
            text[end_text - start] = '\0';
            strncpy(url, line + start_url, closing_paren - (line + start_url));
            url[closing_paren - (line + start_url)] = '\0';
            printf(MD_UNDERLINE_TEXT "%s" RESET_COLOR " (%s)", text, url);
            i = closing_paren - line + 1;
            continue;
          }
        }
      }
    }
    printf("%c", line[i]);
    i++;
  }
}

/// @brief Splits a markdown row into columns.
/// @param line The line to split.
/// @param columns An array to hold the split columns.
/// @return The number of columns split.
static int split_row(const char *line,
                     char columns[MD_MAX_COLUMNS][MD_MAX_COLUMN_LENGTH]) {
  int col_count = 0;
  int i = 0, col_start = 0, col_len = 0;

  while (line[i] != '\0') {
    if (line[i] == '|') {
      if (col_len > 0) {
        while (isspace(line[col_start])) {
          col_start++;
        }
        while (col_len > 0 && isspace(line[col_start + col_len - 1])) {
          col_len--;
        }
        strncpy(columns[col_count], line + col_start, col_len);
        columns[col_count][col_len] = '\0';
        col_count++;
      }
      col_start = i + 1;
      col_len = 0;
    } else {
      col_len++;
    }
    i++;
  }
  return col_count;
}

/// @brief Prints the header of a markdown table.
/// @param line The line containing the header.
void print_table_header(const char *line) {
  const char *p = line;
  int is_first_pipe = 1;
  while (*p) {
    if (*p == '|') {
      if (is_first_pipe) {
        printf(" ");
      } else {
        printf("\t");
      }
    } else {
      printf(BOLD_TEXT "%c" RESET_COLOR, *p);
    }
    p++;
  }
}

/// @brief Prints a row of a markdown table.
/// @param line The line containing the row.
void print_table_row(const char *line) {
  const char *p = line;
  int is_dash_column = 1;

  while (*p) {
    if (*p == '|') {
      if (!is_dash_column) {
        printf("\t  ");
      }
      p++;
      is_dash_column = 1;
    } else if (*p == '`') {
      const char *start_code = p;
      p++;
      while (*p != '\0' && *p != '`') {
        p++;
      }
      if (*p == '`') {
        p++;
        char inline_code[MD_MAX_COLUMN_LENGTH];
        strncpy(inline_code, start_code, p - start_code);
        inline_code[p - start_code] = '\0';
        print_inline_code(inline_code);
        is_dash_column = 0;
      } else {
        printf("%s", start_code);
        is_dash_column = 0;
      }
    } else {
      if (*p != '-' && !isspace(*p)) {
        is_dash_column = 0;
      }
      if (!is_dash_column) {
        printf("%c", *p);
      }
      p++;
    }
  }
  printf("\n");
}

/// @brief Parses and prints rows of a markdown table from a file.
/// @param file The file pointer to read the table rows from.
void parse_table_rows(FILE *file) {
  char line[MD_MAX_LINE_LENGTH];
  while (fgets(line, sizeof(line), file) != NULL && strchr(line, '|')) {
    printf("  ");
    print_table_row(line);
  }
}

/// @brief Parses a markdown file and displays its contents.
/// @param filename The name of the markdown file to parse.
void parse_markdown(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file");
    return;
  }

  char line[MD_MAX_LINE_LENGTH];
  int inside_unordered_list = 0;
  int inside_ordered_list = 0;
  int inside_code_block = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    if (strncmp(line, "```", 3) == 0) {
      if (inside_code_block) {
        printf(RESET_COLOR "\n");
        inside_code_block = 0;
      } else {
        printf(MD_CODE_BLOCK_COLOR "\n");
        inside_code_block = 1;
      }
      continue;
    }

    if (inside_code_block) {
      printf("%s", line);
      continue;
    }

    if (line[0] == '#') {
      if (inside_unordered_list) {
        inside_unordered_list = 0;
      }
      if (inside_ordered_list) {
        inside_ordered_list = 0;
      }
      int heading_level = 0;
      int i = 0;
      while (line[i] == '#') {
        heading_level++;
        i++;
      }
      print_heading(line + heading_level, heading_level);
    } else if (is_unordered_list(line)) {
      if (!inside_unordered_list) {
        inside_unordered_list = 1;
      }
      print_list(line + 2, 0);
    } else if (is_ordered_list(line)) {
      if (!inside_ordered_list) {
        inside_ordered_list = 1;
      }
      int i = 0;
      while (isdigit(line[i])) {
        i++;
      }
      print_list(line + i + 2, 1);
    } else if (strchr(line, '|')) {
      print_table_header(line);
      parse_table_rows(file);
    } else {
      if (inside_unordered_list) {
        inside_unordered_list = 0;
      }
      if (inside_ordered_list) {
        inside_ordered_list = 0;
      }
      if (strstr(line, "`") != NULL) {
        print_inline_code(line);
      } else if (strstr(line, "[") != NULL && strstr(line, "](") != NULL) {
        print_link(line);
      } else {
        printf("%s", line);
      }
    }
  }

  fclose(file);
}
