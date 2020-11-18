#include <stdio.h>
#include <stdlib.h>
#include "p3.h"

/* Pasa el test de enunciado*/

void elimRep(char *s) {
  char *w=s;
	char *r=s;
	char *p=s+1;

  while (*w){
    if (*r==*""){
      *w=*r;
      w++;
      r++;
    }
    else if (*r==*p){
      r++;
      p++;
    }
    else{
      *w=*r;
      w++;
      r++;
      p++;
    }
  }
}
