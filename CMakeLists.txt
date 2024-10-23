cmake_minimum_required(VERSION 3.10)
project(cook C)
set(CMAKE_C_STANDARD 11)

include_directories(src/headers)
add_executable(cli_tools
        src/args.c
        src/CLITools.c
        src/config.c
        src/error.c
        src/log.c
        src/main.c
        src/markdown.c
        src/print.c
        src/systime.c
        src/toml.c
        src/version.c)
