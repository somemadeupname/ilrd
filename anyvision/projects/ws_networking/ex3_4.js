const http = require('http');
const fs = require('fs');
const index = fs.readFileSync('index.html');

const server = http.createServer(function (request, response) {
  const reqMethod = request.method;
  const requestedURL = request.url;
  if (reqMethod !== 'GET' || requestedURL !== '/') {
    response.writeHead(404, { 'Content-Type': 'text/plain' }); // ERROR
    response.write('404 Not Found\n');
    response.end();
  } else {
    response.writeHead(200, { 'Content-Type': 'text/plain' }); // SUCCESS
    response.write('success my dude!\n');
    response.end(index);
  }
});

server.listen(3000);
