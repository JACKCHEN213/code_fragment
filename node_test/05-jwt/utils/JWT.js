const jwt = require('jsonwebtoken');
const secret = '1312312312';
const JWT = {
    generate: (value, expire) => {
        return jwt.sign(value, secret, {expiresIn: expire.toString()});
    },
    
    verify: (token) => {
        try {
            return jwt.verify(token, secret);
        } catch (error) {
            return false;
        }
    }
};

module.exports = JWT;