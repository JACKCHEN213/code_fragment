var express = require('express');
var router = express.Router();
const LoginController = require('../controlls/LoginController');

router.post('/', LoginController.login);
router.delete('/', LoginController.logout);

module.exports = router;
