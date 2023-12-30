var express = require('express');
var router = express.Router();
const UserController = require("../controlls/UserController");

router.post('/', UserController.addUser);

router.put('/:id', UserController.updateUser);

router.delete('/:id', UserController.deleteUser);

router.get('/', UserController.getUser);

module.exports = router;
