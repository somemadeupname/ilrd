function rangeIterator(startValue = 0, endValue = Infinity, step = 1) {
  let nextElement = startValue - step;
  return {
    next: function () {
      return nextElement < endValue ?
          { value: nextElement += step, done: false } :
          { done: true };
    },
  };
}

let ri = rangeIterator(4, 30, 7);

console.log(ri.next().value);
console.log(ri.next().value);
console.log(ri.next().value);
console.log(ri.next().value);

let defaultRangeIterator = rangeIterator(1, Infinity, 1000);

while (true) { console.log(defaultRangeIterator.next()); }

