const { Client } = require('pg');
const client = new Client({
  host: 'localhost',
  port: 5432,
  user: 'student',
  password: 'ct,h kvmkhj',
  database: 'computer_firm'
});
client.connect();
const query = client.query('SELECT * FROM laptop')
    .then((result) => {
      console.log(result.rows);
    })
    .catch((e) => {
      console.log(e.stack);
    })
    .then(() => client.end());
// client.query('SELECT $1::text as message', ['Hello world!'], (err, res) => {
//   console.log(err ? err.stack : res.rows[0].message); // Hello World!
//   client.end();
// });
