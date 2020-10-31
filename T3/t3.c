#include <stdio.h>
#include <stdlib.h>

#include "t3.h"

void desbalancear(Nodo **pa, Nodo **pult){
    if (*pa==NULL){
        return;
    }

    Nodo *nodo_actual=*pa;
    if (nodo_actual->izq==NULL && nodo_actual->der==NULL){
        *pult=nodo_actual;
        return;
    }
    if (nodo_actual->izq!=NULL){
        desbalancear(&(nodo_actual->izq),pult);
        (*pult)->der=nodo_actual;
        *pa=nodo_actual->izq;
        nodo_actual->izq=NULL;
        *pult=nodo_actual
    }

    if (nodo_actual->der!=NULL){
        desbalancear(&(nodo_actual->der),pult);
    }
}

Nodo *desbalanceado(Nodo *a, Nodo **pult){
    Nodo nxref= { 'x', 0, NULL, NULL };
    Nodo *p= &nxref;
    return p;
}