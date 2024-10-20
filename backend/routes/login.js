const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const jwt = require("jsonwebtoken");
const login_card_model = require('../models/login_card_model');
const login_operator_model = require('../models/login_operator_model');

function login_handler(is_operator, model, request, response) {
    if (request.body.pin && request.body.id && (is_operator !== undefined)) {
        const id_ = request.body.id;
        const pin = request.body.pin;
        model.getPin(id_, function (dbError, dbResult) {
                if (dbError) {
                    response.json(dbError);
                } else {
                    if (dbResult.length > 0) {
                        bcrypt.compare(pin, dbResult[0].pin, function (err, compareResult) {
                                if (compareResult) {
                                    console.log("success");
                                    response.send({
                                        access_token: jwt.sign({
                                            sub: id_,
                                            is_operator: is_operator
                                        }, process.env.JWT_SECRET_KEY, {
                                            expiresIn: "10m",
                                        })
                                    });
                                } else {
                                    console.log("wrong pin");
                                    response.send(false);
                                }
                            }
                        );
                    } else {
                        console.log("card or operator does not exist");
                        response.send(false);
                    }
                }
            }
        );
    } else {
        console.log("id or pin missing");
        response.send(false);
    }
}
router.post('/login_card',
    (request, response) => {
        return login_handler(false, login_card_model, request, response);
    }
);

router.post('/login_operator',
    (request, response) => {
        return login_handler(true, login_operator_model, request, response);
    }
);


module.exports = router;