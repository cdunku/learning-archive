#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Custom signal handler for SIGTSTP (Ctrl+Z)
void signal_handle(int sig) {
  printf("Cannot send this process to the background.\n");
}

int main(int argc, char **argv) {
  // Define a sigaction struct to set up a custom handler
  struct sigaction sa;

  // Assign the handler function that replaces the default action
  // Normally, SIGTSTP suspends the process and sends it to the background.
  sa.sa_handler = &signal_handle;

  // SA_RESTART tells the kernel to automatically restart interrupted system calls
  // (like scanf or read) after the signal handler runs, instead of failing with EINTR.
  // This prevents scanf() from breaking if the user presses Ctrl+Z.
  sa.sa_flags = SA_RESTART;

  // Apply our custom handler for SIGTSTP (Ctrl+Z)
  // The third argument is typically NULL when we don't care about the old action.
  if (sigaction(SIGTSTP, &sa, NULL) == -1) {
    perror("sigaction");
    return 1;
  }

  int x;
  printf("Please input a number: ");
  scanf("%d", &x);
  printf("%d * 2 = %d\n", x, x * 2);

  return 0;
}

