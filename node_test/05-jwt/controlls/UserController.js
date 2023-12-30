const fs = require('fs')
const UserModel = require("../model/UserModal");
const UserService = require("../services/UserService");
const Path = require("path");
const UserController = {
    addUser: async (req, res) => {
        // console.log(req.body)
        // 1.创建一个模型
        // user.create user.find user.update user.delete
        let {username, password, age} = req.body;
        let filepath = '/images/default.png';
        if (req.file) {
            filepath = `/uploads/${req.file.filename}`;
        }
        await UserService.addUser(username, password, age, filepath);
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
        let data = await UserService.getUser({_id: req.params.id});
        if (data.length) {
            let filepath = data[0].filepath;
            if (filepath && filepath !== '/images/default.png') {
                filepath = Path.join(__dirname, '../public', filepath)
                if (fs.existsSync(filepath)) {
                    fs.unlinkSync(filepath);
                }
            }
        }
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
