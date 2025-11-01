#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>


int main(int argc, char** argv) {

  // NOTE: Be careful when declaring pipes, the order is very important.
  // Since I declared the pipe before the fork(), the new process inherited 
  // the file descriptors. If I had the declerations the other way around,
  // the process would have not been able to use the fd[] array. Thus, the child 
  // process being unable to communicate with the parent process.
  int fd[2];
  if(pipe(fd) == -1) {
    fprintf(stderr, "Error: pipe could not be created successfully\n");
    return 2;
  }

  pid_t pid = fork();

  if(pid == -1) {
    fprintf(stderr, "Error: couldn't be able to fork a process\n");
    return 1;
  }

  if(pid == 0) {
    close(fd[0]);

    int n;
    int arr[10];

    srand(time(NULL));
    // How many numbers will be added into the array
    n = rand() % 10 + 1;

    // Declare the random numbers
    for(size_t i = 0; i < n; i++) {
      arr[i] = rand() % 10;
      printf("The number in the array: %d\n", arr[i]);
    }

    // The main process must know how many numbers will be inputted somehow,
    // we can declare a global variable which isn't frowned upon. So I will first 
    // write the number of numbers inputted through the pipe and send it to the 
    // parent process.
    if(write(fd[1], &n, sizeof(int)) == -1) {
      fprintf(stderr, "Error: couldn't write the array index\n");
      return 3;
    }
    // Next, write through the pipe. Be careful with the size we are writing with.
    // It should be (the size of one index) * (the n numbers we are writing), so 
    // n * sizeof(int);
    if(write(fd[1], arr, n * sizeof(int)) == -1) {
      fprintf(stderr, "Error: couldn't write the whole array\n");
      return 4;
    } 

    close(fd[1]);
  }
  else {
    close(fd[1]);
    
    int n;
    int arr[10];

    // Same applies to the parent process too, just read n first and then the array.
    // Since an array is a one big chunk of memory with each block or index aligned together,
    // it will not be a problem when writing or reading from a pipe, 
    // it will essentially function and work as writing or reading a normal variable.

    if(read(fd[0], &n, sizeof(int)) == -1) {
      fprintf(stderr, "Error: couldn't read the array index\n");
      return 5;
    }

    printf("The array index is: %d\n", n);

    if(read(fd[0], arr, n * sizeof(int)) == -1) {
      fprintf(stderr, "Error: couldn't read the whole array\n");
      return 6;
    }
    close(fd[0]);

    int sum = 0;
    for(size_t i = 0; i < n; i++) {
      printf("Number recieved from the child process: %d\n", arr[i]);
      sum += arr[i];
    }

    printf("Sum of the whole array is: %d\n", sum);
    wait(NULL);
  }

  return 0;
}
