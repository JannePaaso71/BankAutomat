var express = require('express');
var router = express.Router();
const card_model = require('../models/card_model');
const {request} = require("express");


/**
 * Create new card.
 * Example body:
 * {
 *     "pin": "1234",
 *     "account_ids": {
 *         "first": 1,
 *         "second": 2
 *     },
 *     "owner_id": 1
 * }
 *
 * The second member of account_ids is optional.
 */
router.post('/', function (
    request,
    response) {
    if (request.body.pin && request.body.account_ids?.first) {
        card_model.createCard(request.body.pin, request.body.owner_id, request.body.account_ids, (arg) => {
            if (arg.error !== undefined) {
                response.status(500).send(arg);
            } else {
                response.status(201).send(arg);
            }
        })
    } else {
        response.status(400).send(
            "Bad request. Endpoint expects JSON object with members pin and account_ids."
            + " The account_ids is an object consisting of members first and second. Second member is optional.");
    }
});


/**
 * Delete card
 *
 * Delete card by id.
 */
router.delete('/:id', function (
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


/**
 * Update card.
 *
 * Update card by id.
 * Example body:
 * {
 *     pin: "1234",
 *     account_ids: {
 *         first: 1,
 *         second: 2
 *     },
 *     owner_id: 1
 * }
 *
 * Second account id is optional.
 */
router.put('/:id', (request, response) => {
    if (request.body.pin && request.body.account_ids?.first && request.body.owner_id) {
        const result = card_model.updateCard(request.params.id, request.body.owner_id, request.body.pin, request.body.account_ids, (arg) => {
            card_model.updateCard(request.params.id, request.body.owner_id, request.body.pin, request.body.account_ids, (arg) => {
                response.send(arg);
            });
        })
    } else {
        response.status(400).send("Bad request.")
    }
});


        /**
         * Get card by id
         *
         * Example response:
         * {
         *   "card_id": 1,
         *   "accounts": [
         *     {
         *       "card_id": 1,
         *       "account_id": 1,
         *       "saldo": "500.00",
         *       "credit_limit": null
         *     },
         *     {
         *       "card_id": 1,
         *       "account_id": 2,
         *       "saldo": "0.00",
         *       "credit_limit": "500.00"
         *     }
         *   ]
         * }
         */
        router.get('/:id', (request, response) => {
            const result = card_model.getCard(request.params.id, (arg) => {
                if (arg.error) {
                    if (arg.error === "Invalid card id.") {
                        response.status(400).send(arg);
                    } else {
                        response.status(500).send(arg);
                    }
                } else {
                    response.status(200).send(arg);
                }
            });
        });

        module.exports = router;
