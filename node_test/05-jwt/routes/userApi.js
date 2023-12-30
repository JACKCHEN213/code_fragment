var express = require('express');
const multer = require('multer');
var router = express.Router();
const UserController = require("../controlls/UserController");
const upload = multer({dest: 'public/uploads/'})

/**
 * @api {post} /api/user 添加用户
 * @apiName 添加用户
 * @apiGroup 用户
 * @apiVersion 1.0.0
 *
 * @apiHeader {String} Authorization token
 *
 * @apiHeaderExample {json} Header-Example:
 * {"Authorization": "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI2NTkwMjNiMWE0MjVlY2JhOGJjNDNmYjQiLCJ1c2VybmFtZSI6IjEiLCJleHBpcmUiOiIyMDIzLTEyLTMwVDE2OjAxOjQ4Ljk2NloiLCJpYXQiOjE3MDM5NTIxMDgsImV4cCI6MTcwMzk1NTcwOH0.tZhWo-h9dgbV1p4RXpsl87j99IJFajNmylabEhGoZQc"}
 *
 * @apiBody {String} username 用户名
 * @apiBody {String} password 密码
 * @apiBody {Number} age 年龄
 * @apiBody {File} [file] 头像
 *
 * @apiParamExample {multipart/form-data} Request-Example:
 * {"username": "JackC", "password": "123", "age": 18}
 *
 * @apiSuccess {Number} ok 是否成功
 *
 * @apiSuccessExample {json} Success-Response:
 * HTTP/1.1 200 OK
 * {"ok": 1}
 */
// upload.array
router.post('/', upload.single('file'), UserController.addUser);

/**
 * @api {put} /api/user/:id 修改用户
 * @apiName 修改用户
 * @apiGroup 用户
 * @apiVersion 1.0.0
 *
 * @apiHeader {String} Authorization token
 *
 * @apiHeaderExample {json} Header-Example:
 * {"Authorization": "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI2NTkwMjNiMWE0MjVlY2JhOGJjNDNmYjQiLCJ1c2VybmFtZSI6IjEiLCJleHBpcmUiOiIyMDIzLTEyLTMwVDE2OjAxOjQ4Ljk2NloiLCJpYXQiOjE3MDM5NTIxMDgsImV4cCI6MTcwMzk1NTcwOH0.tZhWo-h9dgbV1p4RXpsl87j99IJFajNmylabEhGoZQc"}
 *
 * @apiParam {String} id id
 * @apiBody {String} username 用户名
 * @apiBody {String} password 密码
 * @apiBody {Number} age 年龄
 *
 * @apiParamExample {json} Request-Example:
 * {"username": "JackC", "password": "123", "age": 18}
 *
 * @apiSuccess {Number} ok 是否成功
 *
 * @apiSuccessExample {json} Success-Response:
 * HTTP/1.1 200 OK
 * {"ok": 1}
 */
router.put('/:id', UserController.updateUser);

/**
 * @api {delete} /api/user/:id 删除用户
 * @apiName 删除用户
 * @apiGroup 用户
 * @apiVersion 1.0.0
 *
 * @apiHeader {String} Authorization token
 *
 * @apiHeaderExample {json} Header-Example:
 * {"Authorization": "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI2NTkwMjNiMWE0MjVlY2JhOGJjNDNmYjQiLCJ1c2VybmFtZSI6IjEiLCJleHBpcmUiOiIyMDIzLTEyLTMwVDE2OjAxOjQ4Ljk2NloiLCJpYXQiOjE3MDM5NTIxMDgsImV4cCI6MTcwMzk1NTcwOH0.tZhWo-h9dgbV1p4RXpsl87j99IJFajNmylabEhGoZQc"}
 *
 * @apiParam {String} id id
 *
 * @apiSuccess {Number} ok 是否成功
 *
 * @apiSuccessExample {json} Success-Response:
 * HTTP/1.1 200 OK
 * {"ok": 1}
 */
router.delete('/:id', UserController.deleteUser);

/**
 * @api {get} /api/user 获取用户
 * @apiName 获取用户
 * @apiGroup 用户
 * @apiVersion 1.0.0
 *
 * @apiHeader {String} Authorization token
 *
 * @apiHeaderExample {json} Header-Example:
 * {"Authorization": "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI2NTkwMjNiMWE0MjVlY2JhOGJjNDNmYjQiLCJ1c2VybmFtZSI6IjEiLCJleHBpcmUiOiIyMDIzLTEyLTMwVDE2OjAxOjQ4Ljk2NloiLCJpYXQiOjE3MDM5NTIxMDgsImV4cCI6MTcwMzk1NTcwOH0.tZhWo-h9dgbV1p4RXpsl87j99IJFajNmylabEhGoZQc"}
 *
 * @apiSuccess {Object[]} ret 返回数据
 * @apiSuccess {String} ret._id id
 * @apiSuccess {String} ret.username 用户名
 * @apiSuccess {String} ret.password 密码
 * @apiSuccess {Number} ret.age 年龄
 * @apiSuccess {String} ret.filepath 头像路径
 *
 * @apiSuccessExample {json} Success-Response:
 * HTTP/1.1 200 OK
 * [
 *   {
 *     "_id": "659023b1a425ecba8bc43fb4",
 *     "username": "1",
 *     "password": "1",
 *     "age": 1,
 *     "filepath": "/images/default.png"
 *   },
 *   {
 *     "_id": "65902eeadb21a04657e21b75",
 *     "username": "22",
 *     "password": "22",
 *     "age": 22,
 *     "filepath": "/uploads/dd809bf1c154ab3117290188571e4c70"
 *   }
 * ]
 */
router.get('/', UserController.getUser);

module.exports = router;
