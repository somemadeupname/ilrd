function myMathMax(...theArgs) {
  function cmp(a, b) {
    if (a < b) {
      return -1;
    } else if (a > b) {
      return 1;
    } else {
      return 0;
    }
  }

  return theArgs.sort(cmp)[theArgs.length - 1];
}

console.log(myMathMax(4, 5, 6, 1, 11, 66, 4, 334, -1, 3458345, 345.345345235667));

