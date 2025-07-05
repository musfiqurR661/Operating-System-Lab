#!/bin/bash
# This script demonstrates basic shell scripting concepts in bash.
# It includes variable assignment, arithmetic operations, string manipulation,
# conditional statements, loops, and functions.
# echo "Hello, World!"

# # Variable assignment
# name=" Musfiqur Rahman"
# age=24
# echo "My name is $name and I am $age years old."

# # Arithmetic operations
# num1=10
# num2=5
# sum=$((num1 + num2))
# diff=$((num1 - num2))
# prod=$((num1 * num2))
# quot=$((num1 / num2))
# echo "Sum: $sum"
# echo "Difference: $diff"
# echo "Product: $prod"
# echo "Quotient: $quot"

# # String manipulation
# str1="Hello"
# str2="World"
# concat="$str1 $str2"
# echo "Concatenated string: $concat"

##user input
# echo "Enter your name:"
# read user_name
# # read -s user_name
# echo "Hello, $user_name!"

## to see the directory
# d=`pwd`
# e=$(pwd)

# d=`ls`
# echo $d

# echo  $e $d

# # to see the arguments
# echo $#
# echo $1
# echo $* 

# # Conditional statements
# read a
# a="y"
# if [ "$a" = "y" ]; then
#     echo "You entered yes."
# fi

# #arithmatic expression
# a=$(( 5 + 3 ))
# echo $a
# b=$((a*2))
# echo   $a $b

# #conditional statements part two
# read a
# if [ $a -eq 10 ]    #a<=10
# then 
# echo "a is less than or equal to 10"
# elif [ $a -gt 10 ]   #a>10
# then
# echo "a is greater than 10"


# # 1<=a<=10
# read a
# if [ $a -gt 1 -a $a -le 10 ]   # AND OP
# then 
# echo "a is between 1 and 10"
# elif [ $a -lt 1 -o $a -gt 10 ]   # OR OP
# then
# echo "a is less than 1 or greater than 10"
# fi


# a=$(echo "scale=2;23.2*222" | bc)
# echo $a

# # nested if else
#  read a 
# if [ $a -eq 1 ]; then echo "A equal 1"; 
# else if [ $a -eq 2 ]; then echo "A equal 2"; 
# else if [ $a -eq 3 ]; then echo "A equal 3"
# else echo "any other value"
# fi ;fi; fi

# # nested if else using elif
#  read a 
# if [ $a -eq 1 ]; then echo "A equal 1"
# elif [ $a -eq 2 ]; then echo "A equal 2"
# elif [ $a -eq 3 ]; then echo "A equal 3"
# else echo "any other value"
# fi 

# #switch case

read a 
case $a in 
    1) echo "A equal 1";;
    2) echo "A equal 2";;
    3) echo "A equal 3";;
    *) echo "Any other value";; # start represent default
esac