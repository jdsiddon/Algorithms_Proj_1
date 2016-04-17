#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>

// This is to prevent compile error "invalid in C99"
// We are just defining our own max macro.
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif


/*
  Algorithm 1: Enumeration. Loop over each pair of indices i, j and compute the sum.
  Keep the best sum you have found so far.
*/
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

/*
  Algorithm 2: Better Enumeration. Notice that in the previous algorithm the same sum is computed
  Write a new version of the first algorithm that takes advantage of this
  observation.
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
  Code based off examples as described here: https://www.youtube.com/watch?v=ohHWQf1HDfU
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


/*
  Algorithm 4: Linear-time. Use the following ideas to develop a nonrecursive linear time algorithm. Start
  at the left end of the array and progress towards the right, keeping track of the maximum subarray sum
  seen so far. Knowing a maximum subarray of A[1 . . j], extend the answer to find a maximum subarray
  ending at index j+1 by using the following observation:
  a maximum subarray of A[1 . . j+1] is either a maximum subarray of A[1 . . j]
  or a subarray A[i . . j+1], for some 1 ≤ i ≤ j+1. Determine a maximum
  subarray of the form A[i . . j+1] in constant time based on knowing a maximum subarray ending at
  index j.
  Code based off examples and discussion here: https://en.wikipedia.org/wiki/Maximum_subarray_problem
*/
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

/*
  This function calulates the sum of each array listed in the 'input' file.
  The arrays must follow the following format:
    [ 1, 2, 3, 4, 1 ]
    [ 1, 32, 33, 4, 1 ]
    ...
*/
void calculateSum(FILE *input) {
  char inputBuffer[100000];
  int numberArray[100000];
  int pos = 0;
  int i = 0;

  // Open output file to write results to.
  FILE *output;
  output = fopen("MSS_Results.txt", "w");        // Open totally new output file.

  while(fgets(inputBuffer, 100000, input)) {       // Get array line.
    // Write array to output file.
    fputs(inputBuffer, output); // Write array to file.

    char *number = strtok(inputBuffer, " ,][");

    // Convert input array line to an array of numbers.
    while (number != NULL)
    {
      numberArray[pos] = atoi(number);
      number = strtok (NULL, " ,][");
      pos++;
    }

    int highestSum = 0;
    clock_t timer;
    int time_elapsed;
    char secondsChar[50];
    char sumChar[50];

    fputs("--- Algorithm 1 ---\n", output);
    timer = clock();                 // Get current time.
    highestSum = arrayEnum1(numberArray, pos-1);
    time_elapsed = clock() - timer;
    snprintf(secondsChar, 50, "%d", time_elapsed);  // Convert time to string.
    snprintf(sumChar, 50, "%d", highestSum);  // Convert integer to string.

    fputs("Time: ", output);
    printf("%s\n", secondsChar);
    fputs(secondsChar, output);
    fputs("\nSum: ", output);
    fputs(sumChar, output); // Write result to file.
    fputs("\n\n", output);
    time_elapsed = 0;


    fputs("--- Algorithm 2 ---\n", output);
    timer = clock();                 // Get current time.
    highestSum = arrayEnum2(numberArray, pos-1);
    time_elapsed = clock() - timer;
    snprintf(secondsChar, 50, "%d", time_elapsed);  // Convert time to string.
    snprintf(sumChar, 50, "%d", highestSum);  // Convert integer to string.

    fputs("Time: ", output);
    fputs(secondsChar, output);
    fputs("\nSum: ", output);
    fputs(sumChar, output); // Write result to file.
    fputs("\n\n", output);
    time_elapsed = 0;


    fputs("--- Algorithm 3 ---\n", output);
    timer = clock();                 // Get current time.
    highestSum = divideConquer(numberArray, pos-1); // Write array to file.
    time_elapsed = clock() - timer;
    snprintf(secondsChar, 50, "%d", time_elapsed);  // Convert time to string.
    snprintf(sumChar, 50, "%d", highestSum);  // Convert integer to string.

    fputs("Time: ", output);
    fputs(secondsChar, output);
    fputs("\nSum: ", output);
    fputs(sumChar, output); // Write result to file.
    fputs("\n\n", output);
    time_elapsed = 0;


    fputs("--- Algorithm 4 ---\n", output);
    timer = clock();                 // Get current time.
    highestSum = linearTime(numberArray, pos-1); // Write array to file.
    time_elapsed = clock() - timer;
    snprintf(secondsChar, 50, "%d", time_elapsed);  // Convert time to string.
    snprintf(sumChar, 50, "%d", highestSum);  // Convert integer to string.

    fputs("Time: ", output);
    fputs(secondsChar, output);
    fputs("\nSum: ", output);
    fputs(sumChar, output); // Write result to file.
    fputs("\n\n", output);
    time_elapsed = 0;

    // Reset for next line.
    bzero((char *) &inputBuffer, sizeof(inputBuffer));      // Clear out input buffer.
    pos = 0;
  }

  fclose(output);

}


/*
  This function generates a set of random inputs.
  It uses the maxSize to determine how big an array can be and totalCount to determine
  how many arrays to generate.
  The generated input file will be in the following format:
    [ 1, 2, 3, 4, 1 ]
    [ 1, 32, 33, 4, 1 ]
    ...
*/
FILE* generateRandom(int maxSize, int totalCount){
  FILE *randomFile;
  randomFile = fopen("MSS_RandomInput.txt", "w+");
  int i = 0;
  int j = 0;
  char writeBuff[10];
  int arraySize = 0;

  // Create random input.
  for(i = 0; i < totalCount; i++) {

    arraySize = (rand() % maxSize) + 10;             // Generate random from 10 - max.
    int *array = malloc(arraySize * sizeof(int));   // Allocate space for array.

    // Create array.
    for(j = 0; j < arraySize; j++) {
      array[j] = rand() % (101 - -101) + -101;
    }

    // Write array containing characters to text file.
    fputs("[ ", randomFile);

    // Write array to file.
    for(j = 0; j < arraySize; j++) {
      // printf("%d\n", array[j]);
      snprintf(writeBuff, 10, "%d", array[j]);
      fputs(writeBuff, randomFile);

      if(j+1 != arraySize)      // Only add the trailing comma if we aren't on the last one.
        fputs(", ", randomFile);
    }

    fputs(" ]\n", randomFile);

    free(array);
    array = 0;
  }

  rewind(randomFile);     // Start back at the beginning of our file to read from it now.
  return randomFile;
}

// Main function.
int main(int argc, char *argv[]) {
  FILE *input;

  srand(time(NULL));  // Rand seed.

  // Make sure they provided an algorithm and file to test.
  if(argc < 3) {
    printf("Usage: ./enum -r [MAX] [COUNT] \n");
    printf("Usage: ./enum -s [FILENAME] \n");
    return 0;
  }

  if(strcmp(argv[1], "-r") == 0) {            // Generate random input file.
    if(argc < 4) {
      printf("Usage: ./enum -r [MAX] [COUNT]\n");
      return 0;
    }
    input = generateRandom(atoi(argv[2]), atoi(argv[3]));

  } else if(strcmp(argv[1], "-s") == 0) {     // Use static file.
    // Make sure input file is readable.
    input = fopen(argv[2], "r");
    if (input == NULL) {
      printf("ERROR: File not readable.");
      return 0;
    }
  }

  calculateSum(input);
  fclose(input);
}
