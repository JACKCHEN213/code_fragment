const UserService = require("../services/UserService");
const LoginController = {
    login: async (req, res) => {
        console.log(req.body)
        let data = await UserService.login(req.body.username, req.body.password);
        if (!data.length) {
            res.send({
                ok: 0,
            })
        } else {
            req.session.user = data[0];
            res.send({
                ok: 1,
            })
        }
    },
    logout: (req, res) => {
        req.session.destroy(() => {
            res.send({ok: 1});
        })
    }
}

module.exports = LoginController;