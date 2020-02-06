const http = require('http');
const fs = require('fs');
const path = require('path');
const zlib = require('zlib');

http.createServer(function (req, res) {
  console.log('Processing request...');
  let filePath = '.' + req.url;
  if (filePath === './') {
    filePath = './fileServer.html';
  }
  const raw = fs.createReadStream(filePath);
  res.setHeader('Vary', 'Accept-Encoding');
  let acceptEncoding = req.headers['accept-encoding'];
  if (!acceptEncoding) {
    acceptEncoding = '';
  }
  if (/\bgzip\b/.test(acceptEncoding)) {
    res.writeHead(200, { 'Content-Encoding': 'gzip' });
    raw.pipe(zlib.createGzip()).pipe(res);
  }
}).listen(3000);
console.log('server running at http://127.0.0.1:3000');
