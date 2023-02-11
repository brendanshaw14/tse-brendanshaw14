#Testing file for the indexer and index modules for the CS50 TSE. 
##Author: Brendan Shaw, February 2023

#clean and make
make clean
make

#no arguments
./indexer

#one argument 
./indexer onearg

#more arguments
./indexer onearg twoarg threearg

#invalid pageDir
./indexer ../data/fakepath ../data/indexFileMakeTest

#invalid indexFile
./indexer ../data/letters fakepath

#invalid indexFile - read only directory
make clean
make 
chmod 555 ../data
./indexer ../data/letters ../data/indexFileMakeTest
chmod 775 ../data

#invalid indexFile - read only file REMOVED THIS TEST BECUASE MY PROGRAM MAKES THE FILE
#chmod 444 ../data/indexFileMakeTest
#./indexer ../data/letters ../data/indexFileMakeTest
#chmod 666 ../data/indexFileMakeTest

##letters
make clean
make
./indexer ../data/letters ../data/indexFileMakeTest
./indextest ../data/indexFileMakeTest ../data/indexFileMakeTestOut
#Compare letters: output below
~/cs50-dev/shared/tse/indexcmp ../data/indexFileMakeTest ../data/indexFileMakeTestOut
make clean
make

#toscrape
./indexer ../data/toscrape ../data/indexFileMakeTest
./indextest ../data/indexFileMakeTest ../data/indexFileMakeTestOut
#Compare letters: output below
~/cs50-dev/shared/tse/indexcmp ../data/indexFileMakeTest ../data/indexFileMakeTestOut
make clean
make

#valgrinds
make clean
make
#indexer
make valgrind
#indextest
make testvalgrind
