#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void sigHandler(int signo);

void doprocessing();

int main ()
{
  printf("main: start\n"); 
 
  int pid, wpid, status;
  int i;
  for(i = 1; i <= 3; i++) {
    pid = fork();
    if(pid < 0) {
      perror("fork");
      exit(1);
    } else if(pid == 0) {
      doprocessing();
      exit(0);
    } else {
      printf("current pid = %d\n", getpid());
      //wpid = wait(&status);
      //printf("pid = %d, status = %d\n", wpid, status);
    }
  }
  printf("main: end\n");
  return 0;
}

void doprocessing() {
  //printf("childProcess pid = %d: start\n", getpid());
  signal(SIGUSR1, sigHandler);
  for(;;) {}
  //printf("childProcess pid = %d: end\n", getpid());
}

void sigHandler(int signo) {
  if(signo == SIGUSR1) {
    printf("Handle SIGUSR1 signal\n"); 
  }
}
