const db = require('../database');

    
const createAccount = {
    /** 
     * Created by Janne Paaso
    */
    updateAccount: (id_customers, credit_limit, callback) => {
        console.log("jep");
        return db.query("UPDATE Accounts SET credit_limit=? WHERE id_customers=?;", [credit_limit, id_customers], (err, result, fields) => {
            if (result === undefined) {
                callback({error: "Database error."});
            } else {
                callback(result);
            }
        })
    },

    /**
     * Created by Janne Paaso
     */
    createAccount: (id_customers, amount, credit_limit,  callback) => {
        console.log("atm_account_models: createaccount", id_customers, amount, credit_limit)
        return db.query("CALL createAccount(?, ?, ?, @success, @customer_id); SELECT @success AS success, @account_id AS account_id; ", [id_customers, amount, credit_limit], (err, result, fields) => {
            if (result === undefined) {
                console.log("DB ERROR: " + err);
                callback({error: "Database error."});
            } else {
                console.log(result)
                const reply = {
                    customer_id:id_customers,
                    success:result[1][0].success,
                    id_account:result[1][0].account_id
                }
                callback(reply);                
            }
        });
    },
    
    /** 
     * Created by Janne Paaso
     * miten tarkistaa etta tili on tyhja?
    */

    deleteAccount: (id_account, callback) => {
        console.log("atm_account_model: deleteaccount");
        return db.query("DELETE FROM Accounts WHERE id_accounts=?;", [id_account], (err, result, fields) => {
            if (result === undefined) {
                callback({error: "Database error."});
            } else {
                callback(result);
            }
        })
    }
}
module.exports = createAccount;