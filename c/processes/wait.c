#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char** argv) {
  pid_t pid = fork();
  int n;

  n = (pid == 0) ? 1 : 6;

  // Since both the processes can work simultaenously by themselves and can interfere,
  // (the numbers can be printed out in any order) we will check whether if the pid is a child process.
  // If it is not, we will halt the main process and execute the child process first.
  if(pid > 0) { wait(NULL); }

  for(int i = n; i < n + 5; i++) {
    printf("%d - ", i);
    fflush(stdout);
  }
  return 0;
}
