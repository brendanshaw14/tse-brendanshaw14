# Testing File for the Querier Component of the Tiny Search Engine
#   Author: Brendan Shaw
#   CS50- Winter 2023


make clean
make


## Arguments Tests: 

#no args
./querier

#one arg
./querier ../data/letters

#three args
./querier ../data/letters ../data/indexFileMakeTest thirdArg

#invalid pagedir (no .crawler)
    mkdir ../data/fakePageDir

./querier ../data/fakePageDir ../data/indexFileMakeTest

#invalid pagedir file (no pageDir/1) file
    touch ../data/fakePageDir/2
    touch ../data/fakePageDir/.crawler

./querier ../data/fakePageDir ../data/indexFileMakeTest

    rm -r -f ../data/fakePageDir

#invalid indexFile 
./querier ../data/letters ../data/fakeIndexFile

#test all types of syntactically invalid commands
    {
        echo and
        echo or
        echo and earth
        echo or earth
        echo planet earth or
        echo planet earth and
        echo planet earth and or science
        echo planet earth and and science
        echo planet earth or and science
        echo "Warning!"
        echo "(The Lunar Chronicles #4.5)"
        echo ^D
    } | ./querier ../data/letters ../data/indexFileMakeTest


#a few tests to show basic funcitonality of intersect and merge in letters : tse is 1 1, so should print score of one in doc 1
echo tse | ./querier ../data/letters ../data/indexFileMakeTest



#testing home: index is home 1 2 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 
#result should be docs 1 with score 2 and docs 2-9 with score 1
echo home | ./querier ../data/letters ../data/indexFileMakeTest




#testing computational or first: indexes are: computational 9 1 and first 3 1 8 1 
#result should be 3, 8, 9, with score 1. 
echo computational or first | ./querier ../data/letters ../data/indexFileMakeTest




#testing tse and home: indexes are tse 1 1 and home 1 2 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 
#result should be just doc 1 with score 1
echo tse and home | ./querier ../data/letters ../data/indexFileMakeTest




#testing home and tse (reversing the order): indexes are tse 1 1 and home 1 2 2 1 3 1 4 1 5 1 6 1 7 1 8 1 9 1 
#result should still be doc 1 with score 1
echo tse and home | ./querier ../data/letters ../data/indexFileMakeTest




#testing home and tse and playground
#result should be 1 with score 1 
echo home and tse and playground | ./querier ../data/letters ../data/indexFileMakeTest



#testing home or tse or playground
#result should be 1 with score 4, the rest of home with score 1 
echo home or tse or playground | ./querier ../data/letters ../data/indexFileMakeTest









#Now for some fuzz testing (toscrape1) 
make fuzz 



#Fuzz with valgrind: I have no leaks (also toscrape 1)
make fuzzgrind
