#!/bin/bash

# Check if the file argument is provided
if [ $# -ne 1 ]; then
    echo "Usage: $0 <package_list_file>"
    exit 1
fi

# Check if the file exists
if [ ! -f "$1" ]; then
    echo "File $1 not found!"
    exit 1
fi

# Read each line from the file and install packages
while IFS= read -r package; do
    sudo apt install -y "$package"
done < "$1"
