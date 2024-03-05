#!/bin/bash

# Check if a tag name was provided as the first argument
if [ $# -eq 0 ]; then
    echo "Usage: $0 <tagname>"
    exit 1
fi

# The tag to remove
tag_name=$1

# Delete the tag locally
git tag -d "$tag_name"

# Check if the local tag removal was successful
if [ $? -eq 0 ]; then
    echo "Successfully deleted local tag '$tag_name'."

    # Optionally, delete the tag from the remote repository
    read -p "Do you want to delete the tag '$tag_name' from the remote repository? (y/N) " answer
    case ${answer:0:1} in
        y|Y )
            git push --delete origin "$tag_name"
            if [ $? -eq 0 ]; then
                echo "Successfully deleted
