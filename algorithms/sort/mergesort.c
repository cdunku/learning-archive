#include <stdio.h>

int main() {

  int arr[] = { 7, 3, 5, 1, 2, 43, 21, 53, 12, 32, 9, 0, 10 };

  for(size_t i = 0; i < (sizeof(arr) / sizeof(int)); i++) {
    printf("%d - ", arr[i]);
  }
  return 1;
}
