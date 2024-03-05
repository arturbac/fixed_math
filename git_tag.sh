#!/bin/bash

# Path to the top level CMakeLists.txt file
CMAKE_FILE="CMakeLists.txt"

# Extract the version number
#VERSION=$(grep "VERSION" $CMAKE_FILE | head -n 1 | awk '{print $2}')
#VERSION=$(grep "VERSION" $CMAKE_FILE | head -n 1 | sed -E 's/.*VERSION ([0-9]+.[0-9]+.[0-9]+).*/\1/')
#VERSION=$(grep "^project(" $CMAKE_FILE | sed -n 's/.*VERSION \([0-9]*\.[0-9]*\.[0-9]*\).*/\1/p')
VERSION=$(tail -n +2 $CMAKE_FILE | grep "VERSION" | head -n 1 | awk '{print $2}')

# Check if VERSION is empty
if [ -z "$VERSION" ]; then
  echo "Version not found in $CMAKE_FILE"
  exit 1
fi

# Prefix the version with a 'v'
TAG="v$VERSION"

# Add a git tag
git tag -a $TAG -m "Release $TAG"

# Optional: Push the tag to remote repository
# git push origin $TAG

echo "Tag $TAG created and ready to be pushed."
