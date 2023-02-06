#!/bin/bash

##Testing file for crawler.c (and pagedir.c)
##Author: Brendan Shaw
##CS50-23W

make clean

make

echo -e "\n Zero Arguments Test: "
./crawler

echo -e "\n One Argument Test"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html

echo -e "\n Two Arguments Test"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters

echo -e "\n Two Invalid Arguments Test"
./crawler abc def

echo -e "\n Incorrect number of args test"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters abc def

echo -e "\n Three Arguments- invalid URL Test"
./crawler http://cs50ts.cs.dartmouth.edu/tse/letters/index.html ../data/letters 2

echo -e "\n Three Arguments- invalid pageDir Test"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html invalid 2

echo -e "\n Three Arguments- invalid maxDepth edge case Test"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 11

echo -e "\n Three Arguments- invalid maxDepth case Test"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 22

echo -e "\n Valid args: letters 0" 
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 0
make clean
make

echo -e "\n Valid args: letters 1" 
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 1
make clean
make

echo -e "\n Valid args: letters 2" 
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 2
make clean
make

echo -e "\n Valid args: letters 10" 
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../data/letters 10
make clean
make 

echo -e "\n Valid args: letters 10 WITH VALGRIND" 
make valgrind


echo -e "\n Valid args: toScrape 0" 
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ../data/toscrape 0
make clean
make 

echo -e "\n Valid args: toScrape 1" 
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ../data/toscrape 1
make clean
make 

echo -e "\n Valid args: wikipedia 0" 
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../data/wikipedia 0
make clean
make 

echo -e "\n Valid args: wikipedia 1" 
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../data/wikipedia 1
make clean
make 

