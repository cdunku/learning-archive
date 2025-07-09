#include <stdio.h>

// NOTE: This implementation uses stack allocation (VLAs). 
// For large arrays, this can lead to stack overflow. 
// A heap-based version using malloc would be more scalable.

void divide_arr(int *arr, size_t l, size_t m, size_t r) {
  size_t size1 = m - l + 1;
  size_t size2 = r - m;
  int arr1[size1]; 
  int arr2[size2];

  // Copy left half into arr1
  for (size_t i = 0; i < size1; i++) {
    arr1[i] = arr[l + i];
  }

  // Copy right half into arr2
  for (size_t i = 0; i < size2; i++) {
    arr2[i] = arr[m + 1 + i]; 
  }

  // Merge arr1 and arr2 back into arr[l..r]
  size_t i = 0, j = 0, k = l;

  for (; k <= r; k++) {
    // Take from arr1 if:
    // - It's not exhausted (i < size1), AND
    // - arr2 is exhausted OR current arr1 element <= arr2 element
    if ((i < size1) && 
        (j >= size2 || arr1[i] <= arr2[j])) {
      arr[k] = arr1[i];
      i++;
    } else {
      arr[k] = arr2[j];
      j++;
    }
  }
}

void merge_sort(int *arr, size_t l, size_t r) {
  if (r > l) {
    size_t m = l + (r - l) / 2;

    // Recursively sort the left half
    merge_sort(arr, l, m);

    // Recursively sort the right half
    merge_sort(arr, m + 1, r);

    // Merge the two sorted halves
    divide_arr(arr, l, m, r);
  }
}

int main() {
  int arr[] = { 7, 3, 5, 1, 2, 43, 21, 53, 12, 32, 9, 0, 10 };
  size_t arr_len = sizeof(arr) / sizeof(arr[0]);

  merge_sort(arr, 0, arr_len - 1);

  // Print the sorted array
  for (size_t i = 0; i < arr_len; i++) {
    printf("%d - ", arr[i]);
  }
  return 0;
}

