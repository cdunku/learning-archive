#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {

  pid_t pid;
  // If fork() executes successfully, it returns 0 and -1 if it fails.
  // pid has the value of 0
  // pid = fork();

  if(pid == 0) {
    // Child process, no need to fork
    printf("Child process\n");
  }
  else if(pid < 0) {
    // Creating a process has failed
    printf("Creating a child process has failed\n");
  }
  else {
    // Parent process, create a new child process 
    printf("Parent process is here, child process is created\n");
    pid = fork();
  }

  printf("Process(es) created\n");

  return 0;
}
