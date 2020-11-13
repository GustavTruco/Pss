#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "p1.h"

#define CANARY 0x385ac48f

int main() {
  uint a[10];
  a[0]= a[9] = CANARY;
  descomprimir(&a[1], 0xf3155, 4); // x en hexadecimal
  int aref[ ] = { CANARY, 5, 5, 1, 3, 15, 0, 0, 0, CANARY };
  for (int i= 0; i<10; i++) {
    if (a[i]!=aref[i]) {
      fprintf(stderr, "a[%d] es incorrectamente %d.  Debio ser %d.\n",
              i, a[i], aref[i]);
      exit(1);
    }
  }
  uint b[13];
  b[0]= b[12] = CANARY;
  descomprimir(&b[1], 01573401, 3); // x en octal
  int bref[ ] = { CANARY, 1, 0, 4, 3, 7, 5, 1, 0, 0, 0, 0, CANARY };
  for (int i= 0; i<10; i++) {
    if (b[i]!=bref[i]) {
      fprintf(stderr, "b[%d] es incorrectamente %d.  Debio ser %d.\n",
              i, b[i], bref[i]);
      exit(1);
    }
  }
  printf("Felicitaciones: paso los 2 tests del enunciado\n");
  return 0;
}
