# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

program: program.o
	$(LOADER) program.o -o  program

program.o: program.c
	$(CCOMP) -c program.c