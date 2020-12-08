#include <pthread.h>

#include "t6.h"

// *** Esta implementacion no funciona porque no respeta orden de llegada ***

pthread_mutex_t m= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond= PTHREAD_COND_INITIALIZER;

int visor= 0;
int num=0;

void ocupar() {
  pthread_mutex_lock(&m);
  int mi_num=num;
  while(visor!=mi_num){
    pthread_cond_wait(&cond,&m);
  }
  num++;
}

void desocupar() {
  visor++;
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&m);
}
