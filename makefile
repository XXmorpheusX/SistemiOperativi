CC = gcc
#CC = g++
FLAGS = -Wall -g
#includedir = ./source
#INCLUDEDIR = -I. -I$(includedir)
#LIB = -lm

.PHONY: clean distclean

target: visitaRicorsivaDirectory compile distclean install

visitaRicorsivaDirectory:
		$(CC) $(FLAGS) -c visitaRicorsivaDirectory.c

compile:
		$(CC) $(FLAGS) -o myExe visitaRicorsivaDirectory.o

clean:
		rm -rf *~
		rm -rf *bak*
		rm -rf core

distclean: clean
		#rm -rf myExe
		rm -rf *.o

install:
		mkdir bin
		cp ./myExe ./bin/
		rm ./myExe