#include <stdlib.h>
#include<stdio.h>
#include "p2.h"

void mediaLista(Nodo **ph) {
  Nodo* actual=*ph;
  if (actual==NULL || actual->prox==NULL){
      *ph=NULL;
      return;
  }
  Nodo* proximo=actual->prox;
  **ph=*(proximo);
  mediaLista(&(proximo));
  return;
}
