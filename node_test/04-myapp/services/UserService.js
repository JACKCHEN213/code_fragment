const UserModel = require("../model/UserModal");
const UserService = {
    addUser: (username, password, age) => {
        return UserModel.create({
            username, password, age
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
    getUser: () => {
        return UserModel.find({}, ['username', 'password', 'age', '_id'])
            .sort({age: 1});
    }
};

module.exports = UserService;