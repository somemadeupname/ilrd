// const util = require('util');

// logging middleware
/*function logit(req, res, next) {
  util.log(util.format('Request recieved: %s, %s', req.method, req.url));
  next();
}*/

function echo (req, res, next) {
  req.pipe(res);
}

const connect = require('connect');

// const app = connect().use(logit).listen(3000);
const app = connect()
                .use('/echo', echo)
                .use(function (req, res, next) { res.end('default my dude!'); })
                .listen(3000);
console.log('server running on port 3000');
