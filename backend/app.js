var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var app = express();

let createTables = require('./models/create_tables');
createTables();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));



// app.use(cookieParser());
// app.use(express.static(path.join(__dirname, 'public')));
var indexRouter = require('./routes/index');
let loginRouter = require('./routes/login');
let cardRouter = require('./routes/card');
let customerRouter = require('./routes/customer');
let transactionRouter = require("./routes/transaction");
let accountTypeCheck = require('./routes/atm_account');
let accountRouter = require('./routes/teller_account')

app.use('/login', loginRouter);

const jwt = require('./middleware/jwt_required');
app.use(jwt.jwt_required);
// app.use(jwt.resource_owner_checker);
app.use('/atm/account', accountTypeCheck);
app.use('/atm/transactions', transactionRouter);


//app.use(jwt.operator_jwt_required);
app.use('/teller/card', cardRouter);
app.use('/teller/customer', customerRouter);
app.use('/teller/teller_account', accountRouter);
///teller/teller_account/createaccount/

/*
app.use(jwt.jwt_required);
app.use(jwt.resource_owner_checker);

 */
//app.use('/atm/card', cardRouter);

app.use('/', indexRouter);


module.exports = app;
