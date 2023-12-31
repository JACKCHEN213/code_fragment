const Router = require("koa-router");
const router = new Router();

router.get('/', (ctx, next) => {
    console.log(ctx.query)
    ctx.body = [
        'aaa', 'bbb', 'ccc',
    ];
});

router.post('/', (ctx, next) => {
    console.log(ctx.request.body);
    ctx.body = {
        ok: 1,
        msg: "add user success"
    }
});

router.put('/:id', (ctx, next) => {
    ctx.body = {
        ok: 1,
        msg: "put user success"
    }
});

router.del('/:id', (ctx, next) => {
    ctx.body = {
        ok: 1,
        msg: "del user success"
    }
});

module.exports = router;
