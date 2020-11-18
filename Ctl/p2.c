#include <stdlib.h>

#include "p2.h"

/*Pasa los test de enunciado*/

void podarHojas(Nodo **pa) {
  if (*pa==NULL){
        return;
    }

  Nodo *nodo_actual=*pa;
  if (nodo_actual->izq==NULL && nodo_actual->der==NULL){
      *pa=NULL;
      free(nodo_actual);
      return;
  }
  podarHojas(&(nodo_actual->izq));
  podarHojas(&(nodo_actual->der));
}
