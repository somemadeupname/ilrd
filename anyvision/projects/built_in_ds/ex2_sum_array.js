function sumOfArray(array) {
  let sum = 0;

  for (const element of array) {
    sum += element;
  }

  return sum;
}

let arr = [1, 2, 3, 4, 54, 56];
let arr2 = ['a', 'b', 'c'];

console.log(sumOfArray(arr));
console.log(sumOfArray(arr2));

