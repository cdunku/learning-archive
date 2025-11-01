#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int x = 0;

void handle_sigusr1(int sig) {
  if(x == 0) {
    printf("\nMultiplication is repetitive addition\n");
  }
}

int main(int argc, char** argv) {

  pid_t pid = fork();

  if(pid == -1) {
    fprintf(stderr, "Error: failed to fork a process\n");
    return 1;
  }


  // Child sends SIGUSR1 to parent after a delay.
  // Parent handles the signal, printing a message without interrupting scanf().
  if(pid == 0) {
    sleep(3);
    // The child process communicates with the parent process,
    // where it calls kill and assigns a signal that will happen in the 
    // parent process. Esentially, we are communicating between the 
    // child process and the parent process.
    // kill(Proccess ID, Signal)
    // SIGUSR1 is a custom and user-defineable signal
    kill(getppid(), SIGUSR1);
  }
  else {
    // Handle the SIGUSR1 signal in the parent process.
    // Assign the necessary flags, handler and 
    // link the (sa) struct to the SIGUSR1 signal. 
    struct sigaction sa;
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = &handle_sigusr1;
    sigaction(SIGUSR1, &sa, NULL);

    printf("Input a number please: ");
    scanf("%d", &x);
    printf("3 * %d = %d\n", x, 3 * x);

    wait(NULL);
  }

  return 0; 
}
