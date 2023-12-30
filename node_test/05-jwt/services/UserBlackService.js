const UserBlackModel = require("../model/UserBlackModel");
const JWT = require("../utils/JWT");
const UserBlackService = {
    add: (token) => {
        let data = JWT.verify(token);
        return UserBlackModel.create({
            username: data.username,
            token,
            forbid_time: new Date(),
            expire: data.expire,
        });
    },
    get: (token) => {
        return UserBlackModel.find({token}, ['username', 'token', 'forbid_time', '_id']);
    },
};

module.exports = UserBlackService;