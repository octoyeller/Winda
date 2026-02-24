#!/bin/bash

# Script to recursively bundle all transitive shared library dependencies
# Usage: ./bundle_libs.sh <binary_path> <target_dir>
# Example: ./bundle_libs.sh app/winda app/

# Check arguments
if [ $# -ne 2 ]; then
  echo "Usage: $0 <binary_path> <target_dir>"
  exit 1
fi

binary="$1"
target_dir="$2"

# Create a temp file to track seen libraries
seen=$(mktemp)
echo "" > "$seen"

# Queue for processing (start with the binary)
to_process="$binary"

while [ -n "$to_process" ]; do
  # Get the next item to process
  current=$(echo "$to_process" | head -n1)
  to_process=$(echo "$to_process" | tail -n +2)

  # Get dependencies of the current item
  libs=$(ldd "$current" 2>/dev/null | awk '{print $3}' | sort -u)

  for lib in $libs; do
    if ! grep -q "^$lib$" "$seen"; then
      echo "$lib" >> "$seen"
      # Copy with parent dirs, dereferencing symlinks
      cp --parents -L "$lib" "$target_dir"
      # Add to queue for recursion
      to_process="$to_process $lib"
    fi
  done
done

# Cleanup
rm -f "$seen"

echo "Bundling complete. All transitive dependencies copied to $target_dir."
