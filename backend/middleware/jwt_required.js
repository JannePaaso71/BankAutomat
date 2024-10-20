jwt = require("jsonwebtoken");

const jwt_middleware = {
    /**
     * Checks ownership of resource being accessed matches that of client identity.
     *
     * This middleware depends on jwt_required -middleware being registered prior to registering this.
     * @param request
     * @param response
     * @param next
     */
    resource_owner_checker: (request, response, next) => {
        const hasBodyId = request.body.hasOwnProperty("id");
        const path_param_id = request.params.hasOwnProperty("id");
        if (!(hasBodyId ^ path_param_id)) {
            if (hasBodyId) {
                response.status(400).send("Can't have id as path parameter and in message body, both.");
            } else {
                response.status(401).send("Unauthorized.");
            }
        }
        if (hasBodyId && request.body.id === response.locals.jwtSub) {
            next();
        } else if (request.params.id === response.locals.jwtSub) {
            next();
        } else if (response.locals.jwtIsOperator) {
            next();
        } else {
            response.status(500).send("Unknown server error occurred.");
        }
    },
    jwt_required: (request, response, next) => {
        let authorization = request.header("Authorization");
        if (authorization === undefined) {
            response.sendStatus(401);
        } else if (authorization.startsWith("Bearer ")) {
            const token = authorization.slice(7).trim();
            jwt.verify(token, process.env.JWT_SECRET_KEY, function (err, decoded) {
                if (decoded === undefined) {
                    console.log(err);
                    response.sendStatus(403);
                } else {
                    // Only check for the jwt to be valid, and delegate checking the resource ownership to another
                    // middleware or endpoint. jwtSub contains card id.
                    response.locals.jwtSub = decoded.sub;
                    response.locals.jwtIsOperator = decoded.is_operator
                    next();
                }
            });
        } else {
            response.send("Invalid Authorization header. Expected: Authorization: Bearer <token>");
        }
    },
    operator_jwt_required: (request, response, next) => {
        let authorization = request.header("Authorization");
        if (authorization === undefined) {
            response.sendStatus(401);
        } else if (authorization.startsWith("Bearer ")) {
            const token = authorization.slice(7).trim();
            jwt.verify(token, process.env.JWT_SECRET_KEY, function (err, decoded) {
                if (decoded === undefined) {
                    console.log(err);
                    response.sendStatus(403);
                } else {
                    if (decoded.is_operator === true) {
                        next();
                    } else {
                        response.sendStatus(403);
                    }
                }
            });
        } else {
            response.send("Invalid Authorization header. Expected: Authorization: Bearer <token>");
        }
    }
}

module.exports = jwt_middleware;