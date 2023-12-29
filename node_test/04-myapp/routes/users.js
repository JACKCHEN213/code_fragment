var express = require('express');
var router = express.Router();
const UserController = require("../controlls/UserController");

/* GET users listing. */
router.get('/', function (req, res, next) {
    console.log(req.cookies)
    res.cookie('age', 'male')
    res.send('respond with a resource');
});

router.post('/user', UserController.addUser);

router.put('/user/:id', UserController.updateUser);

router.delete('/user/:id', UserController.deleteUser);

router.get('/user', UserController.getUser);

module.exports = router;
