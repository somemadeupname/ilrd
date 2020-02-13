/* static server */
const express = require('express');
// const serveStatic = require('serve-static');
const serveIndex = require('serve-index');

console.log(__dirname);

const app = express()
.use(express.static(__dirname + '/public'))
.use(serveIndex(__dirname + '/public'))
.listen(3000);
