class FibObject() {
  constructor(endPoint) {
  this.endPoint = endPoint;
}

let endPoint;

FibObject.prototype[Symbol.iterator] = function () {
  let fn1 = 0;
  let fn2 = 1;
  let current = fn1;
  return {
    next() {
      while (current < this.endPoint) {
        current = fn1;
        fn1 = fn2;
        fn2 = current + fn1;
      }

      return { value: current, done: false };
    }
  };
};

let fo = new FibObject(40);

for (const element of FibObject) {
  console.log(element);
}
