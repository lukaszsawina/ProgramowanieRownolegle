# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
# OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
OPT = -O3

POMIAR_CZASU_DIR = ../pomiar_czasu

# pliki naglowkowe
INC = -I$(POMIAR_CZASU_DIR)

# biblioteki
LIB = -L$(POMIAR_CZASU_DIR) -lpomiar_czasu -lm

# zaleznosci i komendy
moj_program: moj_program.o
	$(LOADER) $(OPT) moj_program.o -o moj_program $(LIB)

moj_program.o: moj_program.c $(POMIAR_CZASU_DIR)/pomiar_czasu.h
	$(CCOMP) -c moj_program.c $(INC)

clean:
	rm -f *.o
