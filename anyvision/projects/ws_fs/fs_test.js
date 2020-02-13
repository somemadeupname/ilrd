const fs = require('fs');

function dirent () {
  fs.readdir('.', (err, files) => {
    if (err) {
      throw (err);
    } else {
      console.log(files);
      // console.log(fs.statSync(files[0]));
    }
  });
}

function asyncFunc (func, param) {
  return func(...param, (err) => {
    if (err) {
      throw (err);
    }
  });
}

// dirent();
fs.rmdir('new_directory', (err) => {
  if (err) throw err;
});
// dirent();
fs.mkdir('new_directory', (err) => {
  if (err) throw err;
});
// dirent();
console.log((fs.open, ['new_file', 'w']));

// fs.rename('old_directory', 'new_directory', ((err) => {
//   if (err) {
//     console.error(err.message);
//   } else {
//     console.log('rename complete!');
//   }
// }));
