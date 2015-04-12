#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int main (int argc, char **argv)
{
  pid_t pid;
  int i;

  for(i = 1; i <= 3; i++) { 
    pid = atoi(argv[i]);
    kill(pid, SIGUSR1);
  }

  return 0;
}
