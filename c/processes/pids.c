#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int agrc, char **argv) {
  pid_t pid = fork();

  printf("Child ID (%d), Parent ID (%d)\n", getpid(), getppid());

  pid_t res = wait(NULL);

  // If we wait the parent process, the wait returns -1.
  // Meaning only that specfic child process is running and has no children of its own.
  if(res == -1) {
    printf("No child processes found\n");
  }
  // Otherwise the parent process is running, res returns the ID child process when it finishes
  else {
    printf("ID (%d) finished execution\n", res);
  }

  return 0;
}
