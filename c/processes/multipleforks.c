#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char **argv) {
  pid_t pid1 = fork();
  pid_t pid2 = fork();

  // Process Z - Parent process (parent)
  // Process X - Child process (child of Z)
  // Process Y - Grandchild process (child of X)
  // And one more hypothethical process
  //
  // Since we called fork() twice, 
  // the child process (pid1) has a child (pid2) of its own and the parent has a new child.
  // When fork() is called n number of times, we have 2^n processes.
  // Meaning in order to access pid2 we need to check whether if pid1 exists.
  // If pid1 is released, pid2 becomes a zombie process and the memory cannot be freed.

  if(pid1 == 0) {
    if(pid2 == 0) {
      printf("Process Y\n");
    }
    else {
      printf("Process X\n");
    }
  }
  else {
    printf("Process Z\n");
  }
  
  // wait(NULL) blocks until a child process finishes. It returns:
  //   - The PID of the terminated child, if successful
  //   - -1 if there are no child processes or an error occurred
  //
  // errno is a global variable set when wait() returns -1. The specific error
  // we care about here is ECHILD, which means "no more child processes exist".
  //
  // The loop ensures we wait for **all children** to finish.
  // Using ECHILD is good practice to distinguish between "no children left" 
  // and other possible errors.
  // The loop can work with without the errno checking, but it acts like a safety net.
  // The && ensures that the loop stopped due to there being no more children and not something else.
  while(wait(NULL) != -1 && errno != ECHILD) {
    printf("Waited for child\n");
  }
  return 0;
}
