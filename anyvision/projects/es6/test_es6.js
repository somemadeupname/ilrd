const { logSuccess } = require('../utils');

function Person (name) {
  if (!new.target) {
    throw new Error('must use new operator with Person');
  }
  this.name = name;
}

try {
  const person = Person('John');
} catch (e) {
  console.error(e.message);
}


try {
  const person2 = new Person('John');
  logSuccess('success');
} catch (e) {
  console.error(e.message);
}
console.log('test');
