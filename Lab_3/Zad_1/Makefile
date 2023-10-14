# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

pthreads_detach_kill: pthreads_detach_kill.o
	$(LOADER) pthreads_detach_kill.o -o  pthreads_detach_kill

pthreads_detach_kill.o: pthreads_detach_kill.c
	$(CCOMP) -c pthreads_detach_kill.c