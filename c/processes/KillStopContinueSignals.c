#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
  pid_t pid = fork();

  if(pid == -1) {
    fprintf(stderr, "Process failed to be forked\n");
    return 1;
  }

  // In this program, the child process will execute an infinite loop printing a message.
  // The parent process, on the other hand, will determine how long the child process will 
  // execute the loop and for how long.
  if(pid == 0) {
    while(1) {
      printf("Oh no! You are in an infinite loop.\n");
      usleep(50000);
    }
  }
  else {
    // We first stop the child process from further execution with the SIGSTOP signal, 
    // so we can determine how long we should loop the message. 
    kill(pid, SIGSTOP);

    size_t seconds;
    do {
      printf("How many seconds should you be in the loop?\n");
      scanf("%d", &seconds);

      // After receiving the number of seconds (which must be greater than 0,
      // we continue the execution of the child process with the signal SIGCONT.
      // Later on, sleep(seconds) (sleep() effects the main process and sleeps, 
      // while the child process continues to execute) is executed in order to loop through the message 
      // a specific number of seconds. Finally, we stop the child process again and 
      // execute this loop until we enter a number less than 1.
      if(seconds > 0) {
        kill(pid, SIGCONT);
        sleep(seconds);
        kill(pid, SIGSTOP);
      }
    }while(seconds > 0);

    // When we exit the loop in the main process. Finally, we kill or terminate the 
    // child process with the SIGKILL signal and wait for the child process to terminate 
    // first, then terminate the main process.

    kill(pid, SIGKILL);
    wait(NULL);
  }
  return 0;
}
