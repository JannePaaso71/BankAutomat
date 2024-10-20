const db = require('../database');
const bcrypt = require("bcryptjs");

const card = {
    deleteCard: (id_, callback) => {
        // CardsToAccounts entries are cascaded at DB-level.
        return db.query("DELETE FROM Cards WHERE id_cards=?", [id_], (err, result, fields) => {
            if (result === undefined) {
                console.log("DB ERROR: " + err);
                callback({error: "Database error."});
            } else {
                callback({success: 1, fields_affected: result.fieldsAffected})
            }
        });
    },

    getCard: (id, callback) => {
        return db.query(`
SELECT Cards.id_cards as card_id, A.id_accounts as account_id, A.saldo as saldo, A.credit_limit as credit_limit FROM
    Cards LEFT JOIN CardsToAccounts
        ON CardsToAccounts.id_cards = Cards.id_cards
    LEFT JOIN Accounts A
        ON CardsToAccounts.id_accounts = A.id_accounts
    WHERE Cards.id_cards=?;`, [id], (err, result, fields) => {
            if (result === undefined) {
                console.log("DB ERROR: " + err);
                callback({error: "Database error."});
            } else {
                const card_id = result[0]?.card_id;
                if (card_id) {
                    callback({
                        card_id: card_id,
                        accounts: result
                    });
                } else {
                    callback({error: "Invalid card id."});
                }
            }
        })
    },

    /**
     * Create a bank card.
     * @param pin
     * @param account_ids   An object having members `first` and `second` with bank account ids as
     *                      values. Second param is optional.
     * @param owner_id      Owner of the card.
     * @param callback      Gets either {success: bool, card_id: id} or {error: "reason"} -object as an argument.
     * @returns {Query}
     */
    createCard: (pin, owner_id, account_ids, callback) => {
        let account_id0 = account_ids.first;
        let account_id1 = account_ids.second ? account_ids.second : null;
        return db.query(`CALL createCard(?, ?, ?, ?, @success, @card_id); SELECT @success as success, @card_id as card_id;`,
            [bcrypt.hashSync(pin, bcrypt.genSaltSync(12)), owner_id, account_id0, account_id1],
            (err, result, fields) => {
                if (result === undefined) {
                    console.log("DB ERROR:" + err);
                    callback({error: "Database error."});
                } else {
                    callback(result[1][0]);
                }
            });
    },

    /**
     * Update a card
     *
     * @param id_
     * @param owner_id      New owner id.
     * @param newPin        New hash for the pin.
     * @param account_ids   An object having members `first` and `second` with bank account ids as
     *                      values. Second param is optional.
     * @callback cb         Gets a response object or {error: "reason"} -object as an argument.
     *
     * @returns {Query}
     */
    updateCard: (id_, owner_id, newPin, account_ids, callback) => {
        let account_id0 = account_ids.first;
        let account_id1 = account_ids.second ? account_ids.second : null;

        console.log({
            id_: id_,
            owner_id: owner_id,
            newPin: newPin,
            account_ids: account_ids
        })

        return db.query(`CALL updateCard(?, ?, ?, ?, ?, @success); SELECT @success as success;`,
            [id_, owner_id, bcrypt.hashSync(newPin, bcrypt.genSaltSync(12)), account_id0, account_id1],
            (err, result, fields) => {
                if (result === undefined) {
                    console.log("DB ERROR:" + err);
                    callback({error: "Database error."});
                } else {
                    console.log(result[1][0])
                    callback(result[1][0]);
                }
            });
    },
}

module.exports = card;