#include "kernel/types.h"
#include "user/user.h"

// Crea 3 procesos hijos que consumen CPU y escriben su letra
int
main(int argc, char *argv[])
{
  int n = 3;

  for (int i = 0; i < n; i++) {
    int pid = fork();
    if (pid < 0) {
      printf("fork failed\n");
      exit(1);
    }
    if (pid == 0) {
      char c = 'A' + i;
      for (int k = 0; k < 20; k++) {
        for (volatile long j = 0; j < 20000000; j++)
          ;
        write(1, &c, 1);
      }
      exit(0);
    }
  }

  for (int i = 0; i < n; i++)
    wait(0);
  printf("\n");
  exit(0);
}
