// Algorithm 1: Enumeration. Loop over each pair of indices i, j and compute the sum.
// Keep the best sum you have found so far.
//
// Loop over
//
// Arrays
test1 = [1, 2, 3, 4, 5, 6, 7, 8, 9];         // Should equal 45
test2 = [-1, 1, 1, 1, -1];           // Should equal 3
test3 = [-1, 2, 2, 2, -1];                       // Should equal 6


function arrayEnum(array) {
  var maxSoFar = 0;
  var maxEnd = 0;
  var subLen;                     // Starts at 1 because 1 is the smallest subarray we can have.
  var subSum = 0;

  // Loop over all possible sub array sizes.
  for(subLen = 0; subLen < array.length; subLen++) {

    // Loop over each possible position the sub array can occupy.
    for(var subStart = 0; subStart < array.length-subLen; subStart++) {

      // Sum the sub array.
      for(var i = subStart; i <= (subStart+subLen); i++) {
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


console.log(arrayEnum(test1));
