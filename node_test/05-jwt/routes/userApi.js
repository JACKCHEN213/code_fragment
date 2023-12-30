var express = require('express');
const multer = require('multer');
var router = express.Router();
const UserController = require("../controlls/UserController");
const upload = multer({dest: 'public/uploads/'})

// upload.array
router.post('/', upload.single('file'), UserController.addUser);

router.put('/:id', UserController.updateUser);

router.delete('/:id', UserController.deleteUser);

router.get('/', UserController.getUser);

module.exports = router;
