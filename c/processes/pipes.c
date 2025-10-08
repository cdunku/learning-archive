#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char **argv) {
  // fd[0] - read
  // fd[1] - write
  // We have an array of 2 as file descriptors due to pipe having 2 ends.
  // Since a pipe only has 2 ends, it takes an array of 2 indexes as an argument.
  int fd[2];
  if(pipe(fd) == -1) {
    printf("Error while connecting with a pipe");
  }
  int id = fork();
  if(id < 0) {
    printf("Fork could not be created\n");
  }


  // Checks whether if we have a child process.
  if(id == 0) {
    // Here we write the file descriptor
    // Even though we do not use read in this case, it is good practice to disable reading in this case.
    close(fd[0]);
    int x;
    printf("Please input a value: ");
    scanf("%d", &x);
    // Here we write the value of x into the pipe.
    write(fd[1], &x, sizeof(int));
    // Finish writing x to fd[1].
    close(fd[1]);
  }
  else {
    // Same logic as in close(fd[0]), but this time we are reading
    close(fd[1]);
    int y;
    // Here we read from the pipe and store it in y.
    read(fd[0], &y, sizeof(int));
    printf("The value inputted is: %d\n", y);
    close(fd[0]);
  }

  return 0;
}
