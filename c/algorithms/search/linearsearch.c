#include <stdio.h>

int main() {
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  int input = 0;

  printf("Please input a value from 1–15:\t");
  scanf("%d", &input);

  /*
   * Use a simple linear search to iterate through the array.
   * We compare each element of the array with the input value.
   * As soon as we find a match, we print a message and break out of the loop.
   *
   * Note:
   * - This is not the most efficient search method (especially for large arrays),
   *   but it's straightforward and always works, regardless of array order.
   * - We use 'size_t' for the index to match the type returned by sizeof.
   */
  for (size_t i = 0; i < (sizeof(arr) / sizeof(int)); i++) {
    if (input == arr[i]) {
      printf("Value of %d is found in the array!\n", input);
      break;
    }
  }

  return 0;
}

