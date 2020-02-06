// Get process.stdin as the standard input object.
const standardInput = process.stdin;
let userData;

// Set input character encoding.
standardInput.setEncoding('utf-8');

// Prompt user to input data in console.
console.log('Please input text to hash.');

// When user input data and click enter key.
standardInput.on('data', function (data) {
  // User input exit.
  if (data !== 'exit\n') {
    // Print user input in console.
    console.log('User Input Data : ' + data);
    userData = data;
  }
});

const hash = require('crypto')
    .createHash('sha256')
    .update(userData.toString())
    .digest('hex');

console.log(hash);
