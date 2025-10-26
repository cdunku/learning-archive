#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>


// **envp is used in main() because it helps declare enviorenment variables for the program.
// For an example, when running a command in the terminal; the $PATH would be a envp.
int main(int argc, char **argv, char **envp) {
  pid_t pid = fork();

  if(pid == 0) {
    // Child process
    // exec*() functions overwrite the entire process (including the memory) with the command executed.
    // execlp() = execute-list-path
    //
    // The list identifier includes the list of arguments used for executing the command.
    // The path identifier searches throught the $PATH, 
    // but most of the time defaults to /bin/* for searching the command, if execl() is used,
    // then we must include the full path for the specific command we are using.
    // 
    // execlp(file, arg0, arg1, ..., NULL)
    //
    // Other exec* variants include (v) - vector, e - environment
    // Where v - needs an array of list of arguments 
    // and e - needs an array of environment variables 
    // So something like:
    // char *arr[] = { "ping", "-c", "3", "google.com", NULL };
    // char *env[] = { "TEST=enviorenment variable", NULL };
    // execvpe("ping", arr, env);
    // Also exec() also works with one specific command,
    // adding a pipe "|" like in a bash script will not work.
    int err = execlp("ping", "ping", "-c", "3" ,"google.com", NULL);
    if(err != 0) {
      printf("Something was wrong with executing ping.\n");
      return 1;
    }
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
