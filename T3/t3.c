#include <stdio.h>
#include <stdlib.h>

#include "t3.h"

void desbalancear(Nodo **pa, Nodo **pult){
    Nodo *nodo_actual=*pa;
    Nodo *nodo_pas= *pult;
    if (nodo_actual->der==NULL && nodo_actual->izq==NULL){
        nodo_actual->der=nodo_pas;
        return;
    }
    else if (nodo_actual->der==NULL && nodo_pas!=NULL){
        nodo_pas->izq=nodo_actual->izq;
        nodo_actual->izq=NULL;
        desbalancear(& nodo_actual->izq,& nodo_actual);
    }
   
    if (nodo_actual->izq!=NULL){desbalancear(& nodo_actual->izq,& nodo_actual);}
    if (nodo_actual->der!=NULL){desbalancear(& nodo_actual->der,NULL);}
    
    Nodo *paux= nodo_actual->izq;

    while(paux->der!=NULL){
        paux=paux->der;
    }
    paux->der=nodo_actual;
    nodo_actual->izq=NULL;
}

Nodo *desbalanceado(Nodo *a, Nodo **pult){
    Nodo nxref= { 'x', 0, NULL, NULL };
    Nodo *p= &nxref;
    return p;
}