const express = require("express");
const router = express.Router();
const customerModel = require('../models/customer_model');


/**
 * Create new Customer.
 */
router.post("/", (request, response) => {
    customerModel.createCustomer(request.body.firstname, request.body.lastname, (result) => {
        console.log(result);
        response.status(201).send({id: result.insertId, msg: "Created"});
    });
});

router.get("/:id", (request, response) => {
    customerModel.getCustomerById(request.params.id, (result) => {
        response.send(result);
    });
});

/* TODO: Broken.
router.get("/_by_name/:firstname/:lastname", (request, response) => {
    customerModel.getCustomersByName(request.params.firstname, request.params.lastname, (result) => {
        response.send(result);
    });
});*/

router.delete("/:id", (request, response) => {
    customerModel.deleteCustomer(request.params.id, (result) => {
        response.send(result);
    });
});

/**
 * Created by Janne Paaso
 */
router.put("/:id", (request, response) => {
    customerModel.updateCustomer(request.params.id, request.body.firstname, request.body.lastname, (result) => {
        response.send(result);
    });
});
module.exports = router;