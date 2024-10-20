var express = require('express');
var router = express.Router();
const accountModel = require('../models/atm_account_model');
const {request} = require("express");


/**
 * For use-case 'Choose account'.
 */
router.get("/query_accounts", (request, response) => {
    const account_id = response.locals.jwtSub;
    accountModel.getAccountTypesOnCard(account_id, (result) => {
        response.send(result);
    })
});


/**
 * For use-case 'Check balance'.
 */
router.get("/check_balance/:credit_or_debit", (request, response) => {
    const card_id = response.locals.jwtSub;
    if (request.params.credit_or_debit === "debit" || request.params.credit_or_debit === "credit") {
        accountModel.checkBalance(card_id, request.params.credit_or_debit, (result) => {
            response.send(result);
        });
    } else {
        response.status(400).send({error: "Bad request."})
    }
});

/**
 * For use-case 'Withdrawal'.
 */

router.post("/withdrawal", 
function(request, response) {
  accountModel.withdrawal(response.locals.jwtSub, request.body.accountType, request.body.amount, function(err, result) {
    if (err) {
      response.json(err);
    } else {
      response.json(result);
    }
  });
});

module.exports = router;