const UserService = require("../services/UserService");
const JWT = require("../utils/JWT");
const UserBlackService = require("../services/UserBlackService");
const LoginController = {
    login: async (req, res) => {
        console.log(req.body)
        let data = await UserService.login(req.body.username, req.body.password);
        if (!data.length) {
            res.send({
                ok: 0,
            })
        } else {
            const token = JWT.generate({
                _id: data[0]._id,
                username: data[0].username,
                expire: new Date(Date.now() + 100),
            }, '1h');
            res.header('Authorization', token);
            res.send({
                ok: 1,
            })
        }
    },
    logout: async (req, res) => {
        // 加入黑名单
        let token = req.headers['authorization']?.split(' ')[1];
        await UserBlackService.add(token)
        res.send({ok: 1});
    }
}

module.exports = LoginController;