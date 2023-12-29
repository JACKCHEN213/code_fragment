var express = require('express');
var router = express.Router();
var UserModel = require('../model/UserModal');

/* GET users listing. */
router.get('/', function (req, res, next) {
    console.log(req.cookies)
    res.cookie('age', 'male')
    res.send('respond with a resource');
});

router.post('/user/add', (req, res) => {
    // console.log(req.body)
    // 1.创建一个模型
    // user.create user.find user.update user.delete
    let {username, password, age} = req.body;
    UserModel.create({
        username, password, age
    }).then(data => console.log(data))
    res.send({
        ok: 1,
    });
});

router.put('/user/update/:id', (req, res) => {
    // console.log(req.body, req.params)
    let {username, password, age} = req.body;
    UserModel.updateMany({
        _id: req.params.id
    }, {
        username, password, age
    }).then(data => console.log(data))
    res.send({
        ok: 1
    });
});

router.delete('/user/delete/:id', (req, res) => {
    UserModel.deleteOne({_id: req.params.id}).then(data => console.log(data))
    res.send({
        ok: 1
    });
});

router.get('/user/list', (req, res) => {
    console.log(UserModel.schema.obj)
    UserModel.find({}, ['username', 'password', 'age', '_id'])
        .sort({age: 1})
        .then(data => {
            res.send(data);
        })
});

module.exports = router;
