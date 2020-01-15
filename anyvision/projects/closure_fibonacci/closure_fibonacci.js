function fibonacci (index) {
  if (fibonacci.fib === undefined) {
    fibonacci.fib = [0, 1];
  }
  if (fibonacci.greatestIndex === undefined) {
    fibonacci.greatestIndex = 1;
  }

  if (index <= fibonacci.greatestIndex) {
    return fibonacci.fib[index];
  }
  return (function () {
    let prev = fibonacci.fib[fibonacci.greatestIndex - 1];
    let cur = fibonacci.fib[fibonacci.greatestIndex];
    let temp;
    let num = index;
    while (num >= fibonacci.greatestIndex) {
      temp = cur;
      fibonacci.fib[index - num + 1] = cur;
      // console.log(`fib[${index - num + 1}] = cur:${cur}`);
      cur += prev;
      prev = temp;
      num -= 1;
    }
    fibonacci.greatestIndex = index;

    return fibonacci.fib[fibonacci.greatestIndex];
  })();
}

console.log(fibonacci(14));

console.log(fibonacci(11));
