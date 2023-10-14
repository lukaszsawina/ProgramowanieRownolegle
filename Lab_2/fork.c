#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include"../pomiar_czasu/pomiar_czasu.h"

int zmienna_globalna=0;

int main(){
  
  int pid, wynik, i;

  inicjuj_czas();
  
  for(i=0;i<1000;i++){
    
    pid = fork(); 			
    
    if(pid==0){ 			
      
      zmienna_globalna++;

      char pid_nr[20];
      sprintf(pid_nr, "%d", getpid());
      char *arguments[] = {"./program", (char *)pid_nr, NULL};
        
      wynik=execv("./program", arguments);
      if(wynik==-1) 
        printf("Proces potomny nie wykonal programu\n"); 

      exit(0);
      
    } else {					
      
      wait(NULL);
      
    }
    
  }

  drukuj_czas();
  
}

  
