#!/bin/bash

# for i in OS CN HCI DBMS DSA
# do
#     echo $i
# done

# #to see current directory and files

# for i in `ls`
# do
#     echo $i
# done

# for i in `cat m1.txt`
# do
#     echo $i
# done

# # take input from user

# read -p "Enter to print 1 to n:" n
# for ((i=1;i<=n;i++))
# do
#     echo $i
# done

# # to check whether the number is positive, negative or zero
read -p "Enter a number: " a

if ((a > 0)); then
    echo "The number is positive."
elif ((a < 0)); then
    echo "The number is negative."
elif ((a == 0)); then
    echo "The number is Zero."
fi

