all: texref

texref: texref.c chardata.h Makefile
	gcc -o $@ -Wall -pedantic -Wl,-lreadline -Wno-format $<
