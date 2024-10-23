#!/bin/bash

# Output executable name
OUTPUT="cli_tools"
BUILD_DIR="build"

# Compiler and default flags
CC=gcc
CFLAGS="-Wall"  # Enable all warnings by default

# Source files (get all .c files from the src/ directory)
SRC="src/*.c"

# Header files location
INCLUDES="-I."  # Include the directory containing your header files

# Temporary files (you can add other file extensions if needed)
TEMP_FILES="*.o"

# Determine build type (debug or release)
BUILD_TYPE=$1

if [ "$BUILD_TYPE" == "debug" ]; then
    echo "Building in debug mode..."
    CFLAGS="$CFLAGS -g"  # Add debugging symbols
elif [ "$BUILD_TYPE" == "release" ]; then
    echo "Building in release mode..."
    CFLAGS="$CFLAGS -O2"  # Optimize for release
else
    echo "Usage: $0 {debug|release}"
    exit 1
fi

# Ensure the build directory exists
mkdir -p $BUILD_DIR

# Clean function (does not remove the output executable)
clean() {
    echo "Cleaning up..."
    rm -f $BUILD_DIR/$TEMP_FILES
    if [ -d "$BUILD_DIR/$OUTPUT.dSYM" ]; then
        rm -rf "$BUILD_DIR/$OUTPUT.dSYM"
        echo "$BUILD_DIR/$OUTPUT.dSYM directory removed."
    fi
    echo "Environment cleaned."
}

# Build the program inside the build directory
echo "Building $OUTPUT in $BUILD_DIR with flags: $CFLAGS"
$CC $CFLAGS $INCLUDES $SRC -o $BUILD_DIR/$OUTPUT

# Check if the build was successful
if [ $? -eq 0 ]; then
    echo "Build successful: ./$BUILD_DIR/$OUTPUT"

    # Copy help file
    cp HELP.md ./$BUILD_DIR/HELP.md

    # Execute the generate_docs.sh script
    if [ -f "generate_docs.sh" ]; then
        echo "Executing generate_docs.sh..."
        ./generate_docs.sh
        if [ $? -eq 0 ]; then
            echo "Documentation generation successful."
        else
            echo "Documentation generation failed."
        fi
    else
        echo "generate_docs.sh not found, skipping documentation generation."
    fi

    clean
else
    echo "Build failed."
    exit 1
fi
