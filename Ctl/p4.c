#define SIZELIN 20

int main(int argc, char *argv[]) {
  if (argc!=3) {
    fprintf(stderr, "Uso: %s <archivo>\n", argv[0]);
    exit(1);
  }
  FILE *in= fopen(argv[1], "r");
  if (in==NULL) {
    perror(argv[1]);
    exit(2);
  }
  int sep= atoi(argv[2]);
  char buf[SIZELIN+1];
  buf[SIZELIN]= 0;
  int i= 0;
  for (;;) {
    fseek(io, i*SIZELIN, SEEK_SET);
    int rc= fread(buf, SIZELIN, 1, io);
    if (rc==0)
      break;
    printf("%s", buf);
    i *= sep;
  }
  return 0;
}
