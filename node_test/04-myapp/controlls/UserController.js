const UserModel = require("../model/UserModal");
const UserService = require("../services/UserService");
const UserController = {
    addUser: async (req, res) => {
        // console.log(req.body)
        // 1.创建一个模型
        // user.create user.find user.update user.delete
        let {username, password, age} = req.body;
        await UserService.addUser(username, password, age);
        res.send({
            ok: 1,
        });
    },
    updateUser: async (req, res) => {
        // console.log(req.body, req.params)
        let {username, password, age} = req.body;
        await UserService.updateUser(req.params.id, username, password, age);
        res.send({
            ok: 1
        });
    },
    deleteUser: async (req, res) => {
        await UserService.deleteUser(req.params.id)
        res.send({
            ok: 1
        });
    },
    getUser: async (req, res) => {
        console.log(UserModel.schema.obj)
        let data = await UserService.getUser()
        res.send(data)
    }
};

module.exports = UserController;
