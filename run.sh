#!/bin/bash

check_and_create_directories() {
    if [ ! -d "build/release" ]; then
        mkdir -p build/release
        echo "build/release directory created."
    else
        echo "build/release directory already exists."
    fi
}

compile_main() {
    check_and_create_directories

    # Check if main.c exists
    if [ -f "main.c" ]; then
        gcc main.c -o build/release/main
        echo "Compilation successful. Executable created in build/release."
    else
        echo "main.c file not found. Please ensure the file exists in the current directory."
    fi
}

compile_main

