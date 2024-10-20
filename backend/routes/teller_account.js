var express = require('express');
var router = express.Router();
const accountModel = require('../models/teller_account_model');
const {request} = require("express");

/**
 * For use-case create account
 * Created by Janne Paaso
 */
router.post("/createaccount/:id_customers", (request, response) => {
    console.log("hottomolo")
    accountModel.createAccount(request.params.id_customers, request.body.saldo, request.body.credit_limit, (result) => {
        response.send(result);
    });
});

/**
   * For use-case modify account
   * Created by Janne Paaso
   */
  router.put("/updateaccount/:id_accounts", (request, response) => {
    accountModel.updateAccount(request.params.id_accounts, request.body.saldo, request.body.credit_limit, (result) => {
        response.send(result);
    });   
});

/**
 * For use-case delete account
 * Created by Janne Paaso
 */
/**
 * router.delete('/:id', function (
    request,
    response) {
    if (request.params.id) {
        const result = card_model.deleteCard(request.params.id, (arg) => {
            if (arg.error) {
                response.status(500).send(arg);
            } else {
                response.send(arg);
            }
        });
    }
});
 */
module.exports = router;