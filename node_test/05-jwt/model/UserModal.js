const mongoose = require('mongoose');

const UserType = {
    username: String,
    password: String,
    age: Number,
    filepath: String,
};
const UserModel = mongoose.model('user', new mongoose.Schema(UserType));


module.exports = UserModel;