#include <stdio.h>



int main() {

  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  int input = 0;

  printf("Please input a value from 1-15:\t");
  scanf("%d", &input);

  int left = 0;
  int right = (sizeof(arr) / sizeof(int)) - 1;
  int mid = (right - left) / 2;

  // while right is still greater and equal to than left continue searching, it will still stop searching through the array when the value is found in the first if statement
  // the array cannot find odd indexes if it were right > left, since when finding the odd indexes it means that right = left, but when searching for some even numbers 
  // right > left or left < right and this fetches the middle element, hence finding the desired value.
  while(right >= left) {
    if(input == arr[mid]) {
      printf("Value of %d has been found in the array!\n", input);
      break;
    }
    // If the mid is smaller than input, move the left border up
    // since we already check for mid elemenet we can decrement by one avoiding more comparisons.
    else if(arr[mid] < input) {
      left = mid + 1;
    }
    // if the mid is greater than input, move the right border down.
    // since we already check for mid element we can decrement it by one avoiding more comparisons
    else {
      right = mid - 1;
    }
    // we add left to the mid element because it fetches the mid index of the current array.
    // if we did not have left + ... then it would always search the lower half of the array, and sometimes incorrectly.
    // if left = 2 and right = 14, then: 2 + (14 + 2) / 2 = (current mid value is 10) but if we did not add the left index (acts as offset):
    // then: mid = (14 + 2) / 2 = 8; this does not consider from the actual length of the array we are searching through, but the full array we initially are looking through
    // this creates problems while searching the higher parts of the array
    mid = left + (right - left) / 2;
  }

  return 0;
}
