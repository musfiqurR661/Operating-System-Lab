#!/bin/bash
for i in *.txt
do
    director=$(tail -n 2 "$i"| head -n 1)
    mkdir -p "$director"
    mv "$i" "$director"
done
