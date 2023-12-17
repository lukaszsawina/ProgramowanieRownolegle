# kompilator c
CCOMP = /usr/bin/mpicc

# konsolidator
LOADER = /usr/bin/mpicc

# program uruchomieniowy MPI
MPI_run = /usr/bin/mpiexec -oversubscribe

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lm
LIB = -lm

all: wlasny run 

run: wlasny
	$(MPI_run) -np 5 ./wlasny

# zaleznosci i komendy
wlasny : wlasny.o
	$(LOADER) $(OPT) wlasny.o -o wlasny $(LIB)

# jak uzyskac plik moj_program.o ?
wlasny.o: wlasny.c 
	$(CCOMP) -c $(OPT) wlasny.c

clean:
	rm -f *.o wlasny
