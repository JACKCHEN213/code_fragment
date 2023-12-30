var express = require('express');
var router = express.Router();
const LoginController = require('../controlls/LoginController');

/**
 * @api {post} /api/login 登录
 * @apiName 登录
 * @apiGroup 登录
 * @apiVersion 1.0.0
 *
 * @apiBody {String} username 用户名
 * @apiBody {String} password 密码
 *
 * @apiParamExample {json} Request-Example:
 * {"username": "JackC", "password"}
 *
 * @apiSuccess {Number} ok 是否成功
 *
 * @apiSuccessExample {json} Success-Response:
 * HTTP/1.1 200 OK
 * {"ok": 1}
 */
router.post('/', LoginController.login);

/**
 * @api {delete} /api/login 退出登录
 * @apiName 退出登录
 * @apiGroup 登录
 * @apiVersion 1.0.0
 *
 * @apiHeader {String} Authorization token
 *
 * @apiHeaderExample {json} Header-Example:
 * {"Authorization": "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI2NTkwMjNiMWE0MjVlY2JhOGJjNDNmYjQiLCJ1c2VybmFtZSI6IjEiLCJleHBpcmUiOiIyMDIzLTEyLTMwVDE2OjAxOjQ4Ljk2NloiLCJpYXQiOjE3MDM5NTIxMDgsImV4cCI6MTcwMzk1NTcwOH0.tZhWo-h9dgbV1p4RXpsl87j99IJFajNmylabEhGoZQc"}
 *
 * @apiSuccess {Number} ok 是否成功
 *
 * @apiSuccessExample {json} Success-Response:
 * HTTP/1.1 200 OK
 * {"ok": 1}
 */
router.delete('/', LoginController.logout);

module.exports = router;
