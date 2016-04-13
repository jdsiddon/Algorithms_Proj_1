// Algorithm 1: Enumeration. Loop over each pair of indices i, j and compute the sum.
// Keep the best sum you have found so far.
//
// Loop over
//
// Arrays
test1 = [1, 2, 3, 4, 5, 6, 7, 8, 9];         // Should equal 45
test2 = [-1, 1, 1, 1, -1];           // Should equal 3
test3 = [-1, 2, 2, 2, -1];                       // Should equal 6
test4 = [-1, 2, -1];                       // Should equal 2
test5 = [10, -2, -1];                       // Should equal 10
test6 = [1, 2];                       // Should equal 3


function arrayEnum1(array) {
  var maxSoFar = 0;
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
function arrayEnum2(array) {
  var maxSoFar = 0;
  var subLen;                     // Starts at 1 because 1 is the smallest subarray we can have.
  var subSum = 0;

  // Loop over all possible sub array sizes.
  for(subLen = 0; subLen < array.length; subLen++) {
    subSum = 0;       // Reset our temporary sum container.

    // Loop over each possible position the sub array can occupy.
    for(var i = subLen; i < array.length; i++) {

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
function divideConquer(array, len) {
  var sumLeft = 0;
  var sumRight = 0;
  var maxSoFar = 0;
  var middle = 0;
  var sum = 0;

  console.log("len: " + len);


  if(len === 1) {       // Length is 1 so just return the first element.
    console.log(array);
    return array[0];
  }

  // Split array in half.
  middle = Math.round((len/2));      // Subtract by 1 to get array index.
  console.log("middle: " + middle);

  var leftMax = divideConquer(array.slice(0, middle), middle);
  var rightMax = divideConquer(array.slice(middle, array.length), len-middle);
  console.log("leftMax: " + leftMax);
  console.log("rightMax: " + rightMax);


  // Search right half.
  for(var i = middle; i < len; i++) {
    sum += array[i];
    sumRight = Math.max(sum, sumRight);
  }

  sum = 0;

  // Search left half.
  for(i = 0; i < middle; i++) {
    sum += array[i];
    sumLeft = Math.max(sum, sumLeft);
  }

  var singleSubArray = Math.max(leftMax, rightMax);

  console.log("singleSubArray: " + singleSubArray);
  console.log("leftMax: " + leftMax);
  console.log("rightMax: " + rightMax);
  return Math.max(singleSubArray, sumLeft+sumRight);
}

console.log("--- Algorithm 1 ---");
console.log(arrayEnum1(test1));
console.log(arrayEnum1(test2));
console.log(arrayEnum1(test3));
console.log(arrayEnum1(test4));
console.log(arrayEnum1(test5));

console.log("--- Algorithm 2 ---");
console.log(arrayEnum2(test1));
console.log(arrayEnum2(test2));
console.log(arrayEnum2(test3));
console.log(arrayEnum2(test4));
console.log(arrayEnum2(test5));

console.log("--- Algorithm 3 ---");
console.log(divideConquer(test6, test6.length));
// console.log(divideConquer(test1, test1.length));
// console.log(divideConquer(test2, test2.length));
// console.log(divideConquer(test3, test3.length));
// console.log(divideConquer(test4, test4.length));
// console.log(divideConquer(test5, test5.length));
