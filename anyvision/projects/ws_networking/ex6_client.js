const zlib = require('zlib');
const http = require('http');
const fs = require('fs');

const request = http.get({
  host: '127.0.0.1',
  path: '/',
  port: 3000,
  headers: { 'Accept-Encoding': 'gzip' }
});
request.on('response', (response) => {
  const output = fs.createWriteStream('127.0.0.1_example.js');
  response.pipe(zlib.createGunzip()).pipe(output);
});
