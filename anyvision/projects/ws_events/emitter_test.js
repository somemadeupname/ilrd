const EventEmitter = require('events');
const myEE = new EventEmitter();

myEE.on('event_name', function() {
  console.log('first listener');
});
myEE.on('event_name', function () {
  console.log('second listener');
});

// console.log(myEE.eventNames());
// Prints: [ 'foo', 'bar', Symbol(symbol) ]
console.log(myEE.listeners('event_name'));
