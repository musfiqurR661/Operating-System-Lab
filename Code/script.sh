#!/bin/bash

# # Use find with -print0 and read with -d '' to support spaces in filenames
# find . -type f -name "*.txt" -print0 | while IFS= read -r -d '' i
# do
#     country=$(head -n 2 "$i" | tail -n 1)
#     echo $country
#     role=$(head -n 4 "$i" | tail -n 1)
#     folder="$country/$role"

#     mkdir -p "$folder"

#     name=$(basename "$i")
#     mv "$i" "$folder/$name"
# done

# # Delete empty folders
# find . -type d -empty -delete


#!/bin/bash

# Find all .txt files recursively
find . -type f -name "*.txt" | while read i; do
    # Extract player name, country, role using head & tail
    player_name=$(head -n 1 "$i")
    country=$(head -n 2 "$i" | tail -n 1)
    role=$(head -n 4 "$i" | tail -n 1)

    # Build target directory and file path
    target_dir="$country/$role"
    target_path="$target_dir/$player_name.txt"

    # Make sure the directory exists
    mkdir -p "$target_dir"

    # Only move if it's NOT already in the correct location
    if [[ "$(realpath "$i")" != "$(realpath "$target_path")" ]]; then
        mv "$i" "$target_path"
    fi
done

# Remove empty directories (bottom-up)
find . -type d -empty -delete
