#include <stdio.h>

// Binary Search Program
// Prompts the user to input a value from 1–15 and searches for it in a sorted array using binary search.

int main() {
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  int input = 0;

  printf("Please input a value from 1–15:\t");
  scanf("%d", &input);

  int left = 0;
  int right = (sizeof(arr) / sizeof(int)) - 1;

  // Initial midpoint calculation — will be updated inside the loop
  int mid = (right - left) / 2;

  /*
   * While right is greater than or equal to left, continue searching.
   * This condition ensures that we still have a valid search space.
   *
   * If the value is found, the loop exits early via the first if-statement.
   *
   * NOTE:
   * We must use right >= left (not just right > left), because binary search
   * must still run when left == right (especially for odd-sized arrays).
   * If we only used right > left, some values (especially at odd indexes)
   * could be missed.
   */
  while (right >= left) {
    // Check if the middle element is the input
    if (input == arr[mid]) {
      printf("Value of %d has been found in the array!\n", input);
      break;
    }

    /*
     * If the middle element is smaller than the input, move the left boundary up.
     * Since we already checked the middle element, we can safely set:
     *     left = mid + 1
     * This avoids rechecking the same element and speeds up the search.
     */
    else if (arr[mid] < input) {
      left = mid + 1;
    }

    /*
     * If the middle element is greater than the input, move the right boundary down.
     * Again, since we've already checked the middle element, we can set:
     *     right = mid - 1
     * This prevents unnecessary comparisons.
     */
    else {
      right = mid - 1;
    }

    /*
     * IMPORTANT:
     * Recalculate the middle index after updating the search boundaries.
     *
     * We use:
     *     mid = left + (right - left) / 2
     * instead of:
     *     mid = (left + right) / 2
     * to prevent potential overflow and ensure we calculate the mid index
     * relative to the current search range.
     *
     * Without the 'left +' offset, the search would always treat the
     * array as starting at index 0, even after narrowing the range.
     *
     * For example, if:
     *     left = 2 and right = 14
     * then:
     *     mid = left + (right - left) / 2 = 2 + (12 / 2) = 8
     *     → correct index 8 in the narrowed range
     *
     * But:
     *     mid = (left + right) / 2 = (2 + 14) / 2 = 8
     *     → same value, but the reasoning doesn't scale well in larger arrays
     *       or more complex recursions. 'left +' ensures general correctness.
     */
    mid = left + (right - left) / 2;
  }

  return 0;
}

