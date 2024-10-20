
const mysql = require('mysql2');

console.log("Creating connection pool with the following settings:")
console.log(`host: ${process.env.DATABASE_HOST}`)
console.log(`port: ${process.env.DATABASE_PORT}`)
console.log(`user: ${process.env.DATABASE_USERNAME}`)
// console.log(`password: ${process.env.DATABASE_PASSWORD}`)
console.log(`database: ${process.env.DATABASE}`)

const connection = mysql.createPool({
    host: process.env.DATABASE_HOST,
    port: parseInt(process.env.DATABASE_PORT),
    user: process.env.DATABASE_USERNAME,
    password: process.env.DATABASE_PASSWORD,
    database: process.env.DATABASE,

    multipleStatements: true
});

module.exports = connection;