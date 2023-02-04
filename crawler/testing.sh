#!/bin/bash

##Testing file for crawler.c (and pagedir.c)
##Author: Brendan Shaw
##CS50-23W


#zero arguments
echo "Zero Arguments Test: "
./crawler

#one argument: seedURL
echo "One Argument Test"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html

#two arguments: seedURL and pageDir
echo "Two Valid Arguments Test"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters


#two arguments part II: input temp and windchill 
echo "Two Valid Arguments Test Again"
./chill -10 130 

#invalid arguments- not numbers
echo "One Invalid Argument"
./chill 15j 12

#invalid arguments II- not numbers
echo -e "\n Two Invalid Arguments Test"
./chill ajf lll

#invalid arguments III- not numbers
echo -e "\n One Invalid Argument Test"
./chill f

#invalid arguments V- inputs out of range 
echo -e "\n Invalid Temp test"
./chill 140

#invalid arguments VI- inputs out of range 
echo -e "\n Invalid wind test" 
./chill 100 -10

#valid arguments - temp edge case
echo "temp edge case" 
./chill -98 10

#valid arguments- wind velocity edge case
echo "Wind velocity edge case"
./chill -10 0.6

#valid arguments - temp edge case- one arg
echo "temp edge case" 
./chill -98 

#invalid arguments - first invalid temp 
echo "first invalid temp case" 
./chill -99 

#invalid arguments - first invalid wind 
echo "first invalid wind speed"
./chill 15 231









