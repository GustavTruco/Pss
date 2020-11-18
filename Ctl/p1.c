#include <stdio.h>
#include <stdlib.h>

#include "p1.h"

/*Pasa los test de enunciado */


void descomprimir(uint a[], uint x, int nbits) {
  int offset=0;
  int i=0;
  while (offset<32){
  unsigned int mask= (1ULL<<nbits)-1;
  a[i]=x&mask;
  printf("%u",a[i]);
  x=x>>nbits;
  offset=offset+nbits;
  i++;
  }
}
