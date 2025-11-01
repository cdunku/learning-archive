#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {

  int fd[2];
  if(pipe(fd) == -1) {
    fprintf(stderr, "Error: pipe couldn't be created\n");
    return 1;
  }

  pid_t pid = fork();
  if(pid == -1) {
    fprintf(stderr, "Error: the processes couldn't be forked\n");
    return 2;
  }

  if(pid == 0) {
    close(fd[0]);

    char arr[200];

    printf("Plus input some text: ");
    fgets(arr, 200, stdin);
    // We are doing this because with fgets() typically
    // the last character inputted is '\n' due to pressing enter.
    // To prevent this, we put the so that the last character is '\0'.
    // strlen(arr) = '\0' in all cases, but strlen(arr) - 1 = '\n'.
    // We replace the '\n' with '\0'.
    arr[strlen(arr) - 1] = '\0';

    // This line is important because of the array size.
    // If we send "hello" through stdin that is 5 bytes,
    // but since we have the invisible '\0' character, we must 
    // have some kind of end to the "hello" string. Additionally,
    // this string is seen as 'h','e','l','l','o','\0' in memory,
    // so that is 6 bytes.
    int n = strlen(arr) + 1;
    if(write(fd[1], &n, sizeof(n)) == -1) {
      fprintf(stderr, "Error: couldn't write string size\n");
      return 3;
    }
    if(write(fd[1], arr, n * sizeof(char)) == -1) {
      fprintf(stderr, "Error: couldn't write string to main process\n");
      return 4;
    }
    close(fd[1]);
  }
  else {
    close(fd[1]);

    char arr[200];
    int n;

    if(read(fd[0], &n, sizeof(n)) == -1) {
      fprintf(stderr, "Error: couldn't read string size\n");
      return 5;
    }
    if(read(fd[0], arr, n * sizeof(char)) == -1) {
      fprintf(stderr, "Error: couldn't read string\n");
      return 6;
    }

    printf("%s\n", arr);
    close(fd[0]);
    wait(NULL);
  }


  return 0;
}
