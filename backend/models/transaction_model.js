const db = require('../database');

const transactions= {

    getTransactions: (skip, getN, card_id, credit_or_debit, callback) => {
        console.log("skip: ", skip);
        console.log("getN: ", getN);
        console.log("card_id: ", card_id);
        const stmt =
            `SELECT T.amount as amount, DATE_FORMAT(T.date, "%d.%m.%y, %H.%i") as datetime
            FROM Transactions T JOIN Accounts A
                ON A.id_accounts = T.id_account
            WHERE T.id_account = getAccount(?, ?)
            ORDER BY T.date DESC
            LIMIT ?, ?;`;
        db.query(stmt, [card_id, credit_or_debit, skip, getN], (err, result, fields) => {
            if (result === undefined) {
                callback({error: "Database error."});
            } else {
                callback(result);
            }
        });
    },

};

module.exports = transactions;