const mongoose = require('mongoose');

const BlackType = {
    username: String,
    token: String,
    forbid_time: Date,
    expire: Date,
};
const UserBlackModel = mongoose.model('user_black', new mongoose.Schema(BlackType));

UserBlackModel.createIndexes({expire: 1}, {expireAfterSeconds: 0});

module.exports = UserBlackModel;