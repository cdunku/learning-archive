#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <sys/wait.h>
#include <fcntl.h> 

// **envp is used in main() because it helps declare enviorenment variables for the program.
// For an example, when running a command in the terminal; the $PATH would be a envp.
int main(int argc, char **argv, char **envp) {
  pid_t pid = fork();

  if(pid == 0) {
    // We are able to redirect the STDOUT and STDERR somewhere else (e.g. a file).
    // This can be done by opening a new file, where we set the flags:
    // O_CREAT - Create the file
    // O_WRONLY - Write to the file
    int fd = open("error_log.txt", O_WRONLY | O_CREAT, 0777);
    if(fd == -1) {
      printf("The error_log.txt could not be created.\n");
      return 2;
    }
    // We use dup2, to redirect the output stream to the file.
    // So, in our case, dup2(fd, STDERR_FILENO) replaces the stderr stream 
    // from the terminal prompt onto the file.
    dup2(fd, STDERR_FILENO);

    int err = execlp("ping1", "ping", "-c", "3" ,"google.com", NULL);
    if(err != 0) {
      fprintf(stderr, "Something was wrong with executing ping.\n");
      return 1;
    }

    close(fd);
  }
  else {
    // Parent process
    int pstatus;
    // Inserting an int instead of NULL retrieves the code returned from wait().
    // which can tell us what might have happened if an error occurred.
    wait(&pstatus);
    // WIFEXITED checks whether if the process terminated properly.
    if(WIFEXITED(pstatus)) {
      // Retrieves the status code
      int pstatus_code = WEXITSTATUS(pstatus);
      if(pstatus_code == 0) {
        printf("Sucess!\n");
      }
      else {
        printf("Failure\n");
      }
    }
    printf("Child process executed\n");
  }

  return 0;
}
