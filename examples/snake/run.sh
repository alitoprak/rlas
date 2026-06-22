#!/bin/bash

# store caller directory
CALLER_DIR="$PWD"

# change directory to script
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# run rlas relative to script directory
../../build/rlas

# change directory back to caller
cd "$CALLER_DIR"