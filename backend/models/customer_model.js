const db = require('../database');

const customer = {
    createCustomer: (firstname, lastname, callback) => {
        return db.query("INSERT INTO Customers(firstname, lastname) VALUES (?, ?);", [firstname, lastname], (err, result, fields) => {
            if (result === undefined) {
                console.log("DB ERROR: " + err);
                callback({error: "Database error."});
            } else {
                callback(result);
            }
        });
    },

    /** 
     * Created by Janne Paaso
    */
    updateCustomer: (id, firstname, lastname, callback) => {
        console.log("jep");
        return db.query("UPDATE Customers SET firstname=?, lastname=? WHERE id_customers=?;", [firstname, lastname, id], (err, result, fields) => {
            if (result === undefined) {
                callback({error: "Database error."});
            } else {
                callback(result);
            }
        })
    },
    
    getCustomersByName: (firstname, lastname, callback) => {
        return db.query("SELECT * FROM Customers WHERE firstname=? AND lastname=?;"), [firstname, lastname], (err,  result, fields) => {
            if (result === undefined) {
                callback({error: "Database error."});
            } else {
                callback(result);
            }
        }
    },
    getCustomerById: (id, callback) => {
        return db.query("SELECT * FROM Customers WHERE id_customers=?;", [id], (err, result, fields) => {
            if (result === undefined) {
                callback({error: "Database error."});
            } else {
                callback(result);
            }
        })

    },

    

    deleteCustomer: (id, callback) => {
        return db.query("DELETE FROM Customers WHERE id_customers=?", [id], (err, result, fields) => {
            if (err) {
                callback({error: err});
            } else {
                callback(result);
            }
        })
    },
}

module.exports = customer;