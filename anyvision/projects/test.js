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

function highOrderFunc(lowerFunc) {
  console.log(`${lowerFunc.name} has been called.`);
  console.log(`returned value is ${lowerFunc}.`);
}

function someFunc(a) {
  if (a % 2 === 0) {
    return 'even';
  }
  else {
    return 'odd';
  }
};

highOrderFunc(someFunc(1));
highOrderFunc(someFunc(2));
highOrderFunc(someFunc(3));
