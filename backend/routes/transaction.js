const express = require("express");
const router = express.Router();
const transactionModel = require('../models/transaction_model');


router.get("/:credit_or_debit/:page", (req, res) => {
    transactionModel.getTransactions(
        (req.params.page - 1) * 5, 5, res.locals.jwtSub, req.params.credit_or_debit, (arg) => {
        if (arg === "Database error.") {
            res.status(500).send("Database error.");
        } else {
            res.send(arg);
        }
    })
});


module.exports = router;