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
  // If pid1 is released, pid2 becomes a zombie process and cannot the memory cannot be freed.

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
    
  // Process ID returns if the child is terminated successfully.
  // -1 returned means no child processes left.
  // errno is a global variable that tells us why an error occurred. 
  // When wait(NULL) returns -1, errno is set describing the error.
  // If errno == ECHILD (error code for: no existing child processes) the loop terminates.
  while(wait(NULL) != -1 || errno != ECHILD) {
    printf("Waited for child\n");
  }
  return 0;
}
