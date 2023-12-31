const Router = require("koa-router");
const router = new Router();

const userRouter = require('./user');
const homeRouter = require('./home');

router.use('/home', homeRouter.routes(), homeRouter.allowedMethods());
router.use('/user', userRouter.routes(), userRouter.allowedMethods());

router.redirect('/', '/home');

module.exports = router;
