#include "headers/CLITools.h"

int main(int argc, char *argv[]) {
  set_args(argc, argv);            // TODO: add --config arg
  config_from_file("config.toml"); // TODO: add handling if no config file
  print_v("this is %s", "some text");
  return 0;
}
