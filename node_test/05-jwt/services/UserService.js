const UserModel = require("../model/UserModal");
const UserService = {
    addUser: (username, password, age, filepath) => {
        return UserModel.create({
            username, password, age, filepath
        });
    },
    updateUser: (id, username, password, age) => {
        return UserModel.updateOne({
            _id: id
        }, {
            username, password, age
        });
    },
    deleteUser: (id) => {
        return UserModel.deleteOne({_id: id});
    },
    getUser: (condition = {}) => {
        return UserModel.find(condition, ['username', 'password', 'age', '_id', 'filepath'])
            .sort({age: 1});
    },
    login: (username, password) => {
        return UserModel.find({username, password});
    }
};

module.exports = UserService;