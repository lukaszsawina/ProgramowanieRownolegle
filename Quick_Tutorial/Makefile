#zmienne
CCOMP = gcc

LOADER = gcc

OPT = -g -DDEBUG

HelloWorld: HelloWorld.o Calculator.o
	$(LOADER) $(OPT) HelloWorld.o Calculator.o -o HelloWorld

HelloWorld.o: HelloWorld.c
	$(CCOMP) -c $(OPT) HelloWorld.c

Calculator.o: Calculator.c
	$(CCOMP) -c $(OPT) Calculator.c

Clean:
	rm -f *.o