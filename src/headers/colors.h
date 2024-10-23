#ifndef COLORS_H
#define COLORS_H

// ANSI color codes for terminal output
#define RESET_COLOR "\033[0m"        ///< Resets text color to default.
#define BOLD_TEXT "\033[1m"          ///< Makes text bold.
#define RED_TEXT "\033[31m"          ///< Sets text color to red.
#define GREEN_TEXT "\033[32m"        ///< Sets text color to green.
#define BLUE_TEXT "\033[34m"         ///< Sets text color to blue.
#define YELLOW_TEXT "\033[33m"       ///< Sets text color to yellow.
#define ORANGE_TEXT "\033[38;5;214m" ///< Sets text color to orange.

#define DATE_COLOR ORANGE_TEXT ///< Color for date output.
#define TIME_COLOR GREEN_TEXT  ///< Color for time output.

#endif // !COLORS_H
