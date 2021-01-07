#include <string.h>
#include <stdio.h>
#include "p1.h"


//Pasa los test 

void elimRep(char *s) {
  char *string=s;
  char *aux=s;
  int c=0;
  int c2=0;
  if (strlen(s)!=0){
    for (int i=0; i<strlen(s)-1; i++){
      string++;
      aux++;
    }
    aux--;
    c++;  

  while(c2<=strlen(s)){
    for (int i=0; i<strlen(s); i++){
      if (c==strlen(s)){
        string--;
        *string=' ';
        c2++;
      }
      else{
        if (*aux!=*string){
        string--;
        *string=*aux;
        }
        c++;
      }
      aux--;
    }

}
    s=string;
  }

}

