const { Pool } = require('pg');
const pool = new Pool({
  host: 'localhost',
  port: 5432,
  user: 'student',
  password: 'ct,h kvmkhj',
  database: 'users'
});
pool.connect();
const username = 'john123';
const password = 'smith';
const query = pool.query(`SELECT username, password FROM users WHERE
                                  username='${username}' AND password='${password}'`)
    .then((result) => {
      if (result.rowCount === 0) {
        console.log('Incorrect username or password.');
        console.log('FAILED.\n');
        console.log(result);
      } else {
        console.log(result.rows);
      }
    })
    .catch((e) => {
      console.log(e.stack);
    })
    .then(() => pool.end());
// client.query('SELECT $1::text as message', ['Hello world!'], (err, res) => {
//   console.log(err ? err.stack : res.rows[0].message); // Hello World!
//   client.end();
// });
