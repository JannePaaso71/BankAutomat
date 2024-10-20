const db = require('../database');

const login={

    /* Return password hash which needs to be verified. */
    getPin: function(username, callback) {
        return db.query("SELECT password AS pin FROM Operators WHERE username = ?",[username], callback);
    }
};

module.exports = login;