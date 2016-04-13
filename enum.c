#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// This is to prevent compile error "invalid in C99"
// We are just defining our own max macro.
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif


// Algorithm 1: Enumeration. Loop over each pair of indices i, j and compute the sum.
// Keep the best sum you have found so far.
//
// Loop over
//
// Arrays
int test1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};         // Should equal 45
int test2[] = {-1, 1, 1, 1, -1};           // Should equal 3
int test3[] = {-1, 2, 2, 2, -1};                       // Should equal 6
int test4[] = {-1, 2, -1};                       // Should equal 2
int test5[] = {10, -2, -1};                       // Should equal 10
int test6[] = {1, 2};                       // Should equal 3


int arrayEnum1(int array[], int size) {
  int maxSoFar = 0;
  int subLen = 0;                     // Starts at 1 because 1 is the smallest subarray we can have.
  int subSum = 0;
  int subStart = 0;
  int i = 0;

  // Loop over all possible sub array sizes.
  for(subLen = 0; subLen < size; subLen++) {

    // Loop over each possible position the sub array can occupy.
    for(subStart = 0; subStart < (size-subLen); subStart++) {

      // Sum the sub array.
      for(i = subStart; i <= (subStart+subLen); i++) {
        subSum += array[i];
      }

      // Check to see if sub array sum is larger than current largest.
      if(maxSoFar < subSum) {
        maxSoFar = subSum;
      }

      subSum = 0;       // Reset our temporary sum container.
    }

  }
  return maxSoFar;
}

// Algorithm 2: Better Enumeration. Notice that in the previous algorithm the same sum is computed
// Write a new version of the first algorithm that takes advantage of this
// observation.
// Example of comparison:
/*
  [10, -2, -1]
    X
    X   X
    X   X   X
        X   X
            X
*/
int arrayEnum2(int array[], int size) {
  int maxSoFar = 0;
  int subLen = 0;
  int subSum = 0;
  int i = 0;

  // Loop over all possible sub array sizes.
  for(subLen = 0; subLen < size; subLen++) {
    subSum = 0;       // Reset our temporary sum container.

    // Loop over each possible position the sub array can occupy.
    for(i = subLen; i < size; i++) {

      // Sum the sub array.
      subSum += array[i];

      // Check to see if sub array sum is larger than current largest.
      if(maxSoFar < subSum) {
        maxSoFar = subSum;
      }

    }

  }
  return maxSoFar;
}

/*
Algorithm 3: Divide and Conquer. If we split the array into two halves, we know that the maximum
subarray will either be:
 - Contained entirely in the first half,
 - Contained entirely in the second half or
 - Made of a suffix of the first half of the subarray and a prefix of the second half
 https://www.youtube.com/watch?v=ohHWQf1HDfU

*/
int divideConquer(int array[], int len) {
  int sumLeft = INT_MIN;
  int sumRight = INT_MIN;
  int maxSoFar = 0;
  int middle = 0;
  int sum = 0;
  int i = 0;

  if(len == 1) {       // Length is 1 so just return the first element.
    return array[0];
  }

  // Split array in half.
  middle = len/2;

  int leftMax = divideConquer(array, middle);
  int rightMax = divideConquer(array+middle, len-middle);

  // Search right half.
  for(i = middle; i < len; i++) {
    sum += array[i];
    sumRight = max(sum, sumRight);
  }

  sum = 0;

  // Search left half.
  for(i = (middle-1); i >= 0; i--) {
    sum += array[i];
    sumLeft = max(sum, sumLeft);
  }

  int singleSubArray = max(leftMax, rightMax);
  return max(singleSubArray, sumLeft+sumRight);
}


// Algorithm 4: Linear-time. Use the following ideas to develop a nonrecursive linear time algorithm. Start
// at the left end of the array and progress towards the right, keeping track of the maximum subarray sum
// seen so far. Knowing a maximum subarray of A[1 . . j], extend the answer to find a maximum subarray
// ending at index j+1 by using the following observation:
//  a maximum subarray of A[1 . . j+1] is either a maximum subarray of A[1 . . j]
//  or a subarray A[i . . j+1], for some 1 ≤ i ≤ j+1. Determine a maximum
// subarray of the form A[i . . j+1] in constant time based on knowing a maximum subarray ending at
// index j.
// https://en.wikipedia.org/wiki/Maximum_subarray_problem
int linearTime(int array[], int size) {
  int maxEnding = 0;
  int maxSoFar = 0;
  int i = 0;

  for(i = 0; i < size; i++) {
    maxEnding = max(0, maxEnding+array[i]);        // Get current max ending point
    maxSoFar = max(maxSoFar, maxEnding);
  }

  return maxSoFar;

}


int main() {
  printf("--- Algorithm 1 --- \n");
  printf("%d \n", arrayEnum1(test1, sizeof(test1)/sizeof(test1[0])));
  printf("%d \n", arrayEnum1(test2, sizeof(test2)/sizeof(test2[0])));
  printf("%d \n", arrayEnum1(test3, sizeof(test3)/sizeof(test3[0])));
  printf("%d \n", arrayEnum1(test4, sizeof(test4)/sizeof(test4[0])));
  printf("%d \n", arrayEnum1(test5, sizeof(test5)/sizeof(test5[0])));
  printf("%d \n", arrayEnum1(test6, sizeof(test6)/sizeof(test6[0])));

  printf("--- Algorithm 2 --- \n");
  printf("%d \n", arrayEnum2(test1, sizeof(test1)/sizeof(test1[0])));
  printf("%d \n", arrayEnum2(test2, sizeof(test2)/sizeof(test2[0])));
  printf("%d \n", arrayEnum2(test3, sizeof(test3)/sizeof(test3[0])));
  printf("%d \n", arrayEnum2(test4, sizeof(test4)/sizeof(test4[0])));
  printf("%d \n", arrayEnum2(test5, sizeof(test5)/sizeof(test5[0])));
  printf("%d \n", arrayEnum2(test6, sizeof(test6)/sizeof(test6[0])));

  //
  printf("--- Algorithm 3 --- \n");
  printf("%d \n", divideConquer(test1, sizeof(test1)/sizeof(test1[0])));
  printf("%d \n", divideConquer(test2, sizeof(test2)/sizeof(test2[0])));
  printf("%d \n", divideConquer(test3, sizeof(test3)/sizeof(test3[0])));
  printf("%d \n", divideConquer(test4, sizeof(test4)/sizeof(test4[0])));
  printf("%d \n", divideConquer(test5, sizeof(test5)/sizeof(test5[0])));
  printf("%d \n", divideConquer(test6, sizeof(test6)/sizeof(test6[0])));

  printf("--- Algorithm 4 --- \n");
  printf("%d \n", linearTime(test1, sizeof(test1)/sizeof(test1[0])));
  printf("%d \n", linearTime(test2, sizeof(test2)/sizeof(test2[0])));
  printf("%d \n", linearTime(test3, sizeof(test3)/sizeof(test3[0])));
  printf("%d \n", linearTime(test4, sizeof(test4)/sizeof(test4[0])));
  printf("%d \n", linearTime(test5, sizeof(test5)/sizeof(test5[0])));
  printf("%d \n", linearTime(test6, sizeof(test6)/sizeof(test6[0])));
}
