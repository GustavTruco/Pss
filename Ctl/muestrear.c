#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SIZELIN 20

int main(int argc, char *argv[]) {
  if (argc!=3) {
    fprintf(stderr, "Uso: %s <archivo> <n>\n", argv[0]);
    exit(1);
  }
  char *arch= argv[1];
  int n= atoi(argv[2]);

  ...

  return 0;
}
