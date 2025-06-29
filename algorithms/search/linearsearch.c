#include <stdio.h>

int main() {

  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  int input = 0;

  printf("Please input a value from 1-15:\t");
  scanf("%d", &input);
  for(size_t i = 0; i < (sizeof(arr)/sizeof(int)); i++) {
    if(input == arr[i]) {
      printf("Value of %d is found in the array!\n", input);
      break;
    }
  }

  return 0;
}
