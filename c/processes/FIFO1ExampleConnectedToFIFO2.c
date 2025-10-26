#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

// NOTE: FILES fifo1.c AND fifo2.c ARE INTERLINKED!

int main(int argc, char **argv) {
  // When the FIFO file is created for the first time, 
  // it does not give an error.
  // But when we run the program the next time it will return -1,
  // if the FIFO file exists.
  // To combat the error, mkfifo returns the EEXIST flag which means
  // the FIFO file exists. If the error is not because of it existing,
  // then it prints out a message.
  //
  // 0777 all permissions have the right to access the file.
  if(mkfifo("sum", 0777) == -1) {
    if(errno != EEXIST) {
      printf("Something went wrong creating the FIFO file\n");
      return 1;
    }
  }

  int arr[5];
  srand(time(NULL));
  size_t arr_len = sizeof(arr) / sizeof(arr[0]);
  for(size_t i = 0; i < 5; i++) {
    arr[i] = rand() % 100;
    printf("Number in the array: %d\n", arr[i]);
  }

  // If both ends are not "open", the program will stop here.
  // We must do something on the other end as well for the program 
  // to continue execution.
  int fd = open("sum", O_WRONLY);
  if(fd == -1) {
    printf("File descriptor invalid\n");
    return 2;
  }

  // Since we are gonna write all the elements at once,
  // we do not need a for loop (it can make the program slower).
  // But we need to write the amount of bytes we will write to.
  // So in our case: for(size_t i = 0; i < arr_len; i++) 
  // is the same as sizeof(int) * arr_len.
  if(write(fd, &arr, sizeof(int) * 5) == -1) {
    printf("Failed to write to FIFO file\n");
    return 3;
  }
  close(fd);

  fd = open("sum_back", O_RDONLY);
  int sum;
  read(fd, &sum, sizeof(int));
  printf("The sum in fifo1.c: %d\n", sum);

  close(fd);
  return 0;
}
