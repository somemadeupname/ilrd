const fs = require('fs');
const fs2 = require('fs');

console.log(fs2 === fs);

fs.watch('somedir.json', (eventType, filename) => {
  console.log(`event type is: ${eventType}`);
  if (filename) {
    console.log(`filename provided: ${filename}`);
  } else {
    console.log('filename not provided');
  }
});