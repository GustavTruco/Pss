typedef struct nodo {
  int x;
  struct nodo *izq, *der;
} Nodo;

void podarHojas(Nodo **pa);
