#include <stdio.h>

#define LENGTH 10


int main() {
  int arr[LENGTH] = {7, 3, 4, 2, 12, 5, 6, 8, 31, 23};

  for(size_t i = 0; i < LENGTH - 1; i++) {
    size_t index = i; // assume the smallest is here
    for(size_t j = i + 1; j < LENGTH; j++) {
      if(arr[j] < arr[index]) {
        index = j; // found a new smallest value
      }
    }
    // compares the indexes, if it not the same swap the values.
    // the arr[i] is already compared with arr[index] up there,
    // which helps us to fetch the smallest value and swap the value with the current index i
    if(index != i) {
      int tmp = arr[i];
      arr[i] = arr[index];
      arr[index] = tmp;
    }
  }

  for(size_t i = 0; i < LENGTH; i++) {
    printf("%d - ", arr[i]);
  }
  return 0;
}
