const { spawn } = require('child_process');
const ls = spawn('ls', ['-lh', '..']);

// console.log(ls.valueOf());

ls.stdout.on('data', (data) => {
  console.log(`${data}`);
});

ls.stderr.on('data', (data) => {
  console.error(`stderr: ${data}`);
});

ls.on('close', (code) => {
  console.log(`child process exited with code ${code}`);
});
