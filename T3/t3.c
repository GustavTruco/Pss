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
        *pult=nodo_actual;
    }

    if (nodo_actual->der!=NULL){
        desbalancear(&(nodo_actual->der),pult);
    }
}

Nodo *desbalanceado(Nodo *a, Nodo **pult){
    if (a==NULL){
        Nodo *a= NULL;
        printf("soy nulo\n");
        return a;
    }
    Nodo *nodo_actual=a;
    Nodo * nuevo=malloc(sizeof(Nodo));
    nuevo->id=nodo_actual->id;
    nuevo->hash=nodo_actual->hash;
    nuevo->der=NULL;
    nuevo->izq=NULL;

    if (nodo_actual->izq==NULL && nodo_actual->der==NULL){
        *pult=nuevo;
        return nuevo;
    }
    if (nodo_actual->izq!=NULL){
        Nodo *nuevo2=desbalanceado((nodo_actual->izq),pult);
        (*pult)->der=nuevo;
        *pult=nuevo;
        if (nodo_actual->der!=NULL){
            nuevo->der=desbalanceado((nodo_actual->der),pult);
        }
        return nuevo2;
    }
    if (nodo_actual->der!=NULL){
        nuevo->der=desbalanceado((nodo_actual->der),pult);
    }
    return nuevo;
}