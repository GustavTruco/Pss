#include "p3.h"

void elimRep(char *s) {
  char *w=s;
	char *r=s;
	char *p=s+1;

  while (*w){
    if (*r==*p){
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
