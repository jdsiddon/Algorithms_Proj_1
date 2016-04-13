#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

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


int main(int argc, char *argv[]) {
  char inputBuffer[1000];
  int numberArray[1000];
  int pos = 0;
  int i = 0;

  // Make sure they provided an algorithm and file to test.
  if(argc < 3) {
    printf("Usage: ./enum [alg[X]] [filename]\n");
    return 0;
  }

  // Make sure they provided a valid algorithm.
  if (!(strcmp(argv[1], "alg1") == 0 || strcmp(argv[1], "alg2") == 0 || strcmp(argv[1], "alg3") == 0 || strcmp(argv[1], "alg4") == 0)) {
    printf("Valid algorithms: alg1, alg2, alg3, alg4 \n");
    return 0;
  }

  // Make sure input file is readable.
  FILE *input;
  input = fopen(argv[2], "r");
  if (input == NULL) {
    printf("ERROR: File not readable.");
    return 0;

  } else {
    // Open output file to write results to.
    FILE *output;
    output = fopen("MSS_Results.txt", "w");        // Open totally new output file.

    while(fgets(inputBuffer, 1000, input)) {       // Get array line.
      // Write array to output file.
      fputs(inputBuffer, output); // Write array to file.

      char *number = strtok (inputBuffer, " ,][");

      // Convert input array line to an array of numbers.
      while (number != NULL)
      {
        numberArray[pos] = atoi(number);
        number = strtok (NULL, " ,][");
        pos++;
      }

      bzero((char *) &inputBuffer, sizeof(inputBuffer));      // Clear out input buffer.

      if(strcmp(argv[1], "alg1") == 0) {        // Executing Algorithm 1: Enumeration
        printf("--- Algorithm 1 --- \n");
        printf("%d \n", arrayEnum1(numberArray, pos-1));
      } else if(strcmp(argv[1], "alg2") == 0) { // Executing Algorithm 2: Better Enumeration
        printf("--- Algorithm 2 --- \n");
        printf("%d \n", arrayEnum2(numberArray, pos-1));
      } else if(strcmp(argv[1], "alg3") == 0) { // Executing Algorithm 3: Divide and Conquer
        printf("--- Algorithm 3 --- \n");
        printf("%d \n", divideConquer(numberArray, pos-1));
      } else if(strcmp(argv[1], "alg4") == 0) { // Executing Algorithm 4: Linear-time
        printf("--- Algorithm 4 --- \n");
        printf("%d \n", linearTime(numberArray, pos-1));
      }

      pos = 0;
    }

    fclose(output);
    fclose(input);

  }


}
