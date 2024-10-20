const db = require('../database');

const account = {
    getAccountTypesOnCard: (id, callback) => {
        db.query(`CALL getAccountTypes(?, @c1_type, @c2_type, @success);
         SELECT @c1_type as account1_type, @c2_type as account2_type, @success as success;`, [id], (err, result, fields) => {
            if (result === undefined) {
                callback(err.message);
            } else {
                callback(result[1][0]);
            }
        })
    },
    checkBalance(cardId, accountType, callback) {
        db.query(`CALL getBalance(?, ?, @balance, @credit_limit);
         SELECT @balance as balance, @credit_limit as credit_limit;`, [cardId, accountType], (err, result, fields) => {
            if (result === undefined) {
                console.log(err);
                callback({error: "DB error."});
            } else {
                callback(result[1][0]);
            }
        })
    },
    withdrawal(cardId, accountType, amount, callback) {
        db.query(`CALL withdrawal(?, ?, ?, @_success);
         SELECT @_success as success;`, [cardId, accountType, amount], (err, result, fields) => {
            if (result === undefined) {
                console.log(err);
                callback({error: "DB error."});
            } else {
                callback(result[1][0]);
            }
        })
    },
};


module.exports = account;