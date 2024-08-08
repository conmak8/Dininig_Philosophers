#!/bin/bash

# Compilation script for Dining Philosophers problem
gcc main.c routines.c threads.c utils.c -lpthread -o philo

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Executable created: dining_philosophers"
else
    echo "Compilation failed. Please check the source code for errors."
fi
