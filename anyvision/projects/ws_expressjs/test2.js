const express = require('express');
const bodyParser = require('body-parser');

const app = express()
    .use(bodyParser())
    .use (function(req, res) {
      if (req.body.somePropertyfs ) {
        res.end(`Body parsed! value of someProperty : ${req.body.someProperty}`);
      }
      else {
        res.end(`body does not have someProperty!`);
      }
    })
    .use(function(err, req, res, next) {
      res.end(`invalid body!`);
    })
    .listen(3000);