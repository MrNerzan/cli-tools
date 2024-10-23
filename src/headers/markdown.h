// markdown.h
#ifndef MARKDOWN_H
#define MARKDOWN_H
#include "colors.h"

#define MD_INLINE_CODE_COLOR GREEN_TEXT ///< Color for inline code in markdown.
#define MD_CODE_BLOCK_COLOR ORANGE_TEXT ///< Color for code blocks in markdown.
#define MD_UNDERLINE_TEXT "\033[4m"     ///< Underlines text.

#define MD_MAX_COLUMNS 10       ///< Maximum number of columns in markdown.
#define MD_MAX_LINE_LENGTH 1024 ///< Maximum length of a line in markdown.
#define MD_MAX_COLUMN_LENGTH                                                   \
  256 ///< Maximum length of a single column in markdown.

// Function declaration
/// @brief Parses a markdown file and displays its contents.
/// @param filename The name of the markdown file to parse.
void parse_markdown(const char *filename);

#endif // MARKDOWN_H
