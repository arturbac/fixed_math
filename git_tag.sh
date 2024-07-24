#!/bin/bash

# Path to the file containing the version string
FILE_PATH="fixed_lib/include/fixedmath/types.h"

# Extract the version string from the file
VERSION_STRING=$(grep 'FIXEDMATH_VERSION_STRING' $FILE_PATH | cut -d '"' -f2)

# Check if the version string was found
if [ -z "$VERSION_STRING" ]; then
    echo "Version string not found in $FILE_PATH"
    exit 1
fi

# Prefix the version string with 'v'
TAG_NAME="v$VERSION_STRING"

# Create a Git tag with the prefixed version string
git tag -a "$TAG_NAME" -m "Release $TAG_NAME"

echo "Git tag $TAG_NAME created successfully."

# Optional: Push the tag to the remote repository
# git push origin "$TAG_NAME"
