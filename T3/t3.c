#include <stdio.h>
#include <stdlib.h>

#include "t3.h"

void desbalancear(Nodo **pa, Nodo **pult){
    if (*pa==NULL){
        return;
    }

    Nodo *nodo_actual=*pa;
     printf("Nodo Id= %d", nodo_actual->id);
    if (nodo_actual->izq==NULL && nodo_actual->der==NULL){
        *pult=nodo_actual;
        return;
    }
    if (nodo_actual->izq!=NULL){
        desbalancear(&(nodo_actual->izq),pult);
    
        Nodo *aux=nodo_actual->izq;
        while (aux->der!=NULL){
            aux=aux->der;
        }
        *pa=&&(nodo_actual->izq);
        nodo_actual->izq=NULL;
        aux->der=nodo_actual;
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