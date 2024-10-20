const db = require('../database');

const login={

    /* Return password hash which needs to be verified. */
    getPin: function(cardId, callback) {
        return db.query("SELECT pin FROM Cards WHERE id_cards = ?",[cardId], callback);
    }
};

module.exports = login;