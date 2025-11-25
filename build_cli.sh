#!/bin/sh
set -e

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
  mkdir build
fi

cd build

# Configure project (only runs if needed)
cmake ..

# Build
cmake --build .

# Run the CLI program (optional)
./cli/tictactoe_cli
