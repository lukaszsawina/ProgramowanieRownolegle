# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# Dodatkowe biblioteki (matematyczna)
LIBS = -lm

OPT = -g -DDBUG

program: program.o
	$(LOADER) $(OPT) program.o -o  program  $(LIBS)
 
program.o: program.c
	$(CCOMP) -c $(OPT) program.c