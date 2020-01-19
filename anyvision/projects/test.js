// const numbers = [-5, 6, 2, 0];
//
// const doubledPositives = numbers.reduce((accumulator, currentValue) => {
//   if (currentValue > 0) {
//     const doubled = currentValue * 2;
//     accumulator.push(doubled);
//   }
//   return accumulator;
// }, []);
//
// console.log(doubledPositives);

function* generatorFunction () { // Line 1
  console.log('This will be executed first.');
  yield 'Hello, ';   // Line 2
  console.log('I will be printed after the pause');
  yield 'World!';
}

// console.log(generatorFunction().next());
// console.log(generatorFunction().next());
// console.log(generatorFunction().next());
// console.log(generatorFunction().next());

// function highOrderFunc(lowerFunc) {
//   console.log(`${lowerFunc.name} has been called.`);
//   console.log(`returned value is ${lowerFunc}.`);
// }
//
// function someFunc(a) {
//   if (a % 2 === 0) {
//     return 'even';
//   }
//   else {
//     return 'odd';
//   }
// }
//
// highOrderFunc(someFunc(1));
// highOrderFunc(someFunc(2));
// highOrderFunc(someFunc(3));

// const a = (test) => console.log(test);
// const b = a;
//
// console.log(a.name);
// console.log(b.name);

// function tailFactorial (n, p = 1) {
//   if (n <= 1) {
//     return 1 * p;
//   }
//   const result = n * p;
//   // optimized
//   return tailFactorial(n - 1, result);
// }
//
// function factorial(n) {
//   if (n <= 1) {
//     return 1;
//   } else {
//     // not optimized - must multiply after returning
//     return n * factorial(n - 1);
//   }
// }
//
// console.log(tailFactorial(40));
// console.log(factorial(40));

// let a = 10;
// let b = 20;
//
// console.log(`[a, b] = ${[a, b]}`);
// console.log('switch!');
// [b, a] = [a, b];
// console.log(`[a, b] = ${[a, b]}`);

let colors = ["red", "green", "blue"];
const [firstColor, ...restColors] = colors;
// console.log(firstColor);
// console.log(restColors);

function restArgs (...args) {
};

console.log(restArgs.length);
