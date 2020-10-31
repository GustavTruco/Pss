#include <stdio.h>
#include <stdlib.h>

#include "t3.h"

void desbalancear(Nodo **pa, Nodo **pult){
    Nodo *nodo_actual=*pa;
    if (a->izq==NULL and a->der==NULL){
        *pult=a;
        return;
    }
    if (a->izq!=NULL){
        desbalancear(&(a->izq),pult);

        Nodo *aux=a->izq;
        while (aux->der!=NULL){
            *aux=aux->der;
        }
        a->izq=NULL;
        aux->der=a;
    }

    if (a->der!=NULL){
        desbalancear(&(a->der),pult);
    }
}

Nodo *desbalanceado(Nodo *a, Nodo **pult){
    Nodo nxref= { 'x', 0, NULL, NULL };
    Nodo *p= &nxref;
    return p;
}