#include <stdio.h>

#define LENGTH 10


int main() {
  int arr[LENGTH] = {7, 3, 4, 2, 12, 5, 6, 8, 31, 23};
  bool noswap = 1;

  for(size_t i = 0; i < LENGTH - 1; i++) { 
  // LENGTH - i - 1 avoids unnessecary comparisons.
  // if i = 4 then: LENGTH - 4 - 1 (the value of i means that the i number of elements have been sorted)
  // if it were LENGTH - 1 then it would compare the sorted values (which is inefficient)
    for(size_t j = 0; j < LENGTH - i - 1; j++) { 
      if(arr[j] > arr[j + 1]) {
        int temp = arr[j + 1];
        arr[j + 1] = arr[j];
        arr[j] = temp;
        noswap = 0;
      }
    }
    if(noswap) break;
  }
  for(size_t i = 0; i < LENGTH; i++) {
    printf("%d - ", arr[i]);
  }
  return 0;
}
