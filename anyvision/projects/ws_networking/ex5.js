const http = require('http');
const fs = require('fs');
const path = require('path');

http.createServer(function (req, res) {
  console.log('Processing request...');
  let filePath = '.' + req.url;
  if (filePath === './') {
    filePath = './fileServer.html';
  }
  const extname = path.extname(filePath);
  let contentType = 'text/html';
  if (extname === '.js') {
    contentType = 'text/javascript';
  }

  console.log(`filePath is ${filePath.substr(2, filePath.length)}`);

  fs.readFile(filePath, function (error, content) {
    if (error) {
      res.writeHead(500, 'Unable to return file');
      res.write('Error, Will Robinson!');
      res.end();
    } else {
      res.writeHead(200, { contentType });
      res.end(content, 'utf-8');
    }
  });
}).listen(3000);
console.log('server running at http://127.0.0.1:3000');
