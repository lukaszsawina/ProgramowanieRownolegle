# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# Dodatkowe biblioteki (matematyczna)
LIBS = -lm -pthread

OPT = -g -DDBUG

program123: program.o
	$(LOADER) $(OPT) program.o -o  program123 $(LIBS)
 
program.o: program.c
	$(CCOMP) -c $(OPT) program.c