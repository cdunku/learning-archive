#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char **argv) {
  int arr[5];
  size_t arr_len = sizeof(arr) / sizeof(arr[0]);
  int fd = open("sum", O_RDONLY);


  for(size_t i = 0; i < 5; i++) {
    if(read(fd, &arr[i], sizeof(int)) == -1) {
      printf("Could not read from the file\n");
      return 1;
    }
    printf("Recieved the number %d\n", arr[i]);
  }

  int sum;
  for(size_t i = 0; i < 5; i++) {
    sum += arr[i];
  }

  // Since we are going to write to fifo1.c again with the same var,
  // we must close fd first, then open it again with a new file descriptor.
  close(fd);

  printf("The sum in fifo2.c: %d\n", sum);

  // We create a new FIFO file because FIFO files are one-way pipes,
  // when we write to sum again we will not get the intended behaviour.
  // In order to write the data back to the other process we must create a new file.

  if(mkfifo("sum_back", 0777) == -1) {
    if(errno != EEXIST) {
      printf("Something went wrong creating the FIFO file\n");
      return 1;
    }
  }

  fd = open("sum_back", O_WRONLY);
  write(fd, &sum, sizeof(int));

  close(fd);
  return 0;
}
