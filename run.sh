#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: ./run.sh <cpp_file>"
    exit 1
fi

FILE=$1
BASE="${FILE%.*}"

echo "Compiling $FILE..."
g++ -Wall -Wextra -O2 -std=c++17 -D_GLIBCXX_DEBUG "$FILE" -o "$BASE"

if [ $? -eq 0 ]; then
    echo "Running $BASE..."
    ./"$BASE"
else
    echo "Compilation failed."
fi
