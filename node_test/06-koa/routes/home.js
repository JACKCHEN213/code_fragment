const Router = require("koa-router");
const router = new Router();

router.get('/', (ctx, next) => {
    ctx.body = "<b>Hello World</b>";
});

module.exports = router;
