#!bin/bash/
mkdir output_dir
find "in_dir" -type f -name "*txt" | while  read file; do

    if cat $file | grep -e "rabice" -e "pox" -e "corona"; then

        cp $file output_dir
        # echo "Copy"
    fi
done