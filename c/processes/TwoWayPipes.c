#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <sys/wait.h>


int main(int argc, char **argv) {
  // The reason why I have created 2 pipes is due to a pipe only working
  // as a uni-directional communication pipe. So one file descriptor is 
  // used to read by one process and the other one is used by a 
  // different process for writing. In order to exchange data between
  // both processes (so reading and writing), we need 2 pipes.
  int pipe1[2]; // Parent process (read) -> Child process (Write)
  int pipe2[2]; // Child process (read) -> Parent process (Write)

  if(pipe(pipe1) == -1) { return 1; }
  if(pipe(pipe2) == -1) { return 2; }

  int pid = fork();
  
  if(pid == 0) {
    // Child process

    // We must close the end we WILL NOT use. So in our case; Parent read and Parent write.
    close(pipe1[0]);
    close(pipe2[1]);

    int y;
    if(read(pipe2[0], &y, sizeof(y)) == -1) { return 4; }
    printf("Number recieved by child process: %d\n", y);
    y *= y;
    printf("Number sent to main process: %d\n", y);
    if(write(pipe1[1], &y, sizeof(y)) == -1) { return 5; }

    // When we finish with using the pipes for the child process, we close them too.
    close(pipe1[1]);
    close(pipe2[0]);
  } else {
    // Parent process
    // Same logic applies here, but we close the read and write file descriptors for the child process.
    close(pipe1[1]);
    close(pipe2[0]);
    
    srand(time(NULL));
    int x = rand() % 10;

    printf("Number sent to child process: %d\n", x);
    if(write(pipe2[1], &x, sizeof(x)) == -1) { return 3; }
    if(read(pipe1[0], &x, sizeof(x)) == -1) { return 4; }
    printf("Number processed by child process: %d\n", x);
    // We must wait for the child process to finish in order to close the pipes.
    wait(NULL);

    // Finally, we close the read and write file descriptors for the parent process.
    close(pipe1[0]);
    close(pipe2[1]);
  }

  return 0;
}
