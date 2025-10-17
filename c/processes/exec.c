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
    execlp("ping", "ping", "-c", "3" ,"google.com", NULL);
  }
  else {
    // Parent process
    wait(NULL);
    printf("Child process executed\n");
    printf("Success!\n");
  }

  return 0;
}
