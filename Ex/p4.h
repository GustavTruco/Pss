typedef struct nodo {
  int k, v;
  struct nodo *izq, *der;
} Nodo;
int buscarLlavePar(Nodo *a, int valor, int *pk, int p);
int buscarLlaveSec(Nodo *a, int valor, int *pk);
