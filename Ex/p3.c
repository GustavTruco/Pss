#include <pthread.h>

#include "p3.h"

// Agregue las lineas que faltan para que este codigo sea correcto y eficiente

//PASA los TEST

pthread_mutex_t m= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond= PTHREAD_COND_INITIALIZER;


int ocup= 0, cat_ult=1, pend[2]= {0, 0};

void ocupar(int cat) {
  pthread_mutex_lock(&m);
  pend[cat]++;
  while ( ocup || (cat==cat_ult && pend[!cat]!=0) )
    pthread_cond_wait(&cond,&m);        // note que !0 es 1 y !1 es 0
  pend[cat]--;
  ocup= 1;
  cat_ult= cat;
  pthread_mutex_unlock(&m);
}

void desocupar() {
  pthread_mutex_lock(&m);
  ocup= 0;
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&m);
}


